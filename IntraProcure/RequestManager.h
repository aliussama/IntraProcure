#pragma once
#include "DatabaseManager.h"
#include "Request.h"
#include "RequestItem.h"
#include "Product.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	public ref class RequestManager abstract sealed
	{
	public:
		// Create request and its items transactionally; returns new request id or -1 on error
		static int CreateRequest(int employeeId, List<RequestItem^>^ items, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (employeeId <= 0) { error = "Invalid employee"; return -1; }
			if (items == nullptr || items->Count == 0) { error = "No items"; return -1; }

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			SqlTransaction^ tx = nullptr;
			try
			{
				conn->Open();
				tx = conn->BeginTransaction();

				// compute total
				Decimal total = 0;
				for each(RequestItem ^ it in items)
				{
					Decimal itemTotal = Decimal::Multiply(Decimal(it->UnitPrice), Decimal(it->Quantity));
					total = Decimal::Add(total, itemTotal);
				}

				String^ sql = "INSERT INTO procure.Requests (EmployeeId, Department, Total, Status, Remarks, CreatedAt) " +
					"VALUES (@emp,@dept,@total,@status,@remarks,SYSUTCDATETIME()); SELECT SCOPE_IDENTITY();";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn, tx);
				cmd->Parameters->AddWithValue("@emp", employeeId);
				cmd->Parameters->AddWithValue("@dept", String::IsNullOrEmpty(items[0]->Department) ? DBNull::Value : (Object^)items[0]->Department);
				cmd->Parameters->AddWithValue("@total", total);
				cmd->Parameters->AddWithValue("@status", "Pending");
				cmd->Parameters->AddWithValue("@remarks", (Object^)DBNull::Value);
				Object^ idobj = cmd->ExecuteScalar();
				int requestId = Convert::ToInt32(idobj);

				// insert items
				for each(RequestItem ^ it in items)
				{
					String^ ins = "INSERT INTO procure.RequestItems (RequestId, ProductId, Quantity, UnitPrice) VALUES (@rid,@pid,@qty,@up)";
					SqlCommand^ icmd = gcnew SqlCommand(ins, conn, tx);
					icmd->Parameters->AddWithValue("@rid", requestId);
					icmd->Parameters->AddWithValue("@pid", it->ProductId);
					icmd->Parameters->AddWithValue("@qty", it->Quantity);
					icmd->Parameters->AddWithValue("@up", it->UnitPrice);
					icmd->ExecuteNonQuery();
				}

				tx->Commit();
				return requestId;
			}
			catch (Exception^ ex)
			{
				try { if (tx != nullptr) tx->Rollback(); }
				catch (...) {}
				error = ex->Message;
				return -1;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		static List<Request^>^ GetRequestsByUser(int employeeId, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			List<Request^>^ out = gcnew List<Request^>();
			if (employeeId <= 0) { error = "Invalid employee"; return nullptr; }

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, EmployeeId, Department, Total, Status, Remarks, CreatedAt, ApprovedBy, ApprovedAt FROM procure.Requests WHERE EmployeeId=@eid ORDER BY CreatedAt DESC";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@eid", employeeId);
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					Request^ req = gcnew Request();
					req->Id = r->GetInt32(0);
					req->EmployeeId = r->GetInt32(1);
					req->Department = r->IsDBNull(2) ? "" : r->GetString(2);
					req->Total = r->IsDBNull(3) ? 0.0 : static_cast<double>(r->GetDecimal(3));
					req->Status = r->IsDBNull(4) ? "" : r->GetString(4);
					req->Remarks = r->IsDBNull(5) ? "" : r->GetString(5);
					req->CreatedAt = r->IsDBNull(6) ? Nullable<DateTime>() : Nullable<DateTime>(r->GetDateTime(6));
					req->ApprovedBy = r->IsDBNull(7) ? 0 : r->GetInt32(7);
					req->ApprovedAt = r->IsDBNull(8) ? Nullable<DateTime>() : Nullable<DateTime>(r->GetDateTime(8));
					out->Add(req);
				}
				r->Close();
				return out;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return nullptr;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		static List<Request^>^ GetPendingRequests([System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			List<Request^>^ out = gcnew List<Request^>();
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, EmployeeId, Department, Total, Status, Remarks, CreatedAt, ApprovedBy, ApprovedAt FROM procure.Requests WHERE Status = @s ORDER BY CreatedAt ASC";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@s", "Pending");
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					Request^ req = gcnew Request();
					req->Id = r->GetInt32(0);
					req->EmployeeId = r->GetInt32(1);
					req->Department = r->IsDBNull(2) ? "" : r->GetString(2);
					req->Total = r->IsDBNull(3) ? 0.0 : static_cast<double>(r->GetDecimal(3));
					req->Status = r->IsDBNull(4) ? "" : r->GetString(4);
					req->Remarks = r->IsDBNull(5) ? "" : r->GetString(5);
					req->CreatedAt = r->IsDBNull(6) ? Nullable<DateTime>() : Nullable<DateTime>(r->GetDateTime(6));
					req->ApprovedBy = r->IsDBNull(7) ? 0 : r->GetInt32(7);
					req->ApprovedAt = r->IsDBNull(8) ? Nullable<DateTime>() : Nullable<DateTime>(r->GetDateTime(8));
					out->Add(req);
				}
				r->Close();
				return out;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return nullptr;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// Approve or Reject a request (set status and approved fields)
// Approve or Reject a request (set status and approved fields, and update Inventory on approval)
		static bool SetRequestStatus(
			int requestId,
			String^ status,
			int approverId,
			[System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;

			if (requestId <= 0)
			{
				error = "Invalid request id.";
				return false;
			}

			if (String::IsNullOrEmpty(status))
			{
				error = "Invalid status value.";
				return false;
			}

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			SqlTransaction^ tx = nullptr;

			try
			{
				conn->Open();
				tx = conn->BeginTransaction();

				// 1) Get current status
				String^ sqlGet =
					"SELECT Status "
					"FROM procure.Requests "
					"WHERE Id = @id;";

				SqlCommand^ cmdGet = gcnew SqlCommand(sqlGet, conn, tx);
				cmdGet->Parameters->AddWithValue("@id", requestId);

				Object^ curObj = cmdGet->ExecuteScalar();
				if (curObj == nullptr || curObj == DBNull::Value)
				{
					error = "Request not found.";
					tx->Rollback();
					return false;
				}

				String^ currentStatus = safe_cast<String^>(curObj);
				String^ currentLower = currentStatus->ToLower();
				String^ newLower = status->ToLower();

				// 2) If status is the same, nothing to change
				if (String::Compare(currentLower, newLower, true) == 0)
				{
					tx->Commit();
					return true;
				}

				// 3) Protect already-approved requests from being changed
				if (currentLower == "approved" && newLower != "approved")
				{
					error = "Request is already approved and cannot be changed to '" + status + "'.";
					tx->Rollback();
					return false;
				}

				// 4) If we are approving now (and it was NOT already approved), update Inventory
				if (newLower == "approved" && currentLower != "approved")
				{
					// 4.a) Load all items for this request
					String^ sqlItems =
						"SELECT ProductId, Quantity "
						"FROM procure.RequestItems "
						"WHERE RequestId = @rid;";

					SqlCommand^ cmdItems = gcnew SqlCommand(sqlItems, conn, tx);
					cmdItems->Parameters->AddWithValue("@rid", requestId);

					SqlDataReader^ r = cmdItems->ExecuteReader();

					System::Collections::Generic::List<int>^ prodIds =
						gcnew System::Collections::Generic::List<int>();
					System::Collections::Generic::List<int>^ qtys =
						gcnew System::Collections::Generic::List<int>();

					while (r->Read())
					{
						int pid = r->GetInt32(0);
						int q = r->GetInt32(1);
						prodIds->Add(pid);
						qtys->Add(q);
					}
					r->Close();

					// 4.b) For each product, increase Inventory (UPDATE; if no row, INSERT)
					for (int i = 0; i < prodIds->Count; ++i)
					{
						int pid = prodIds[i];
						int addQty = qtys[i];

						// First try to update an existing row
						String^ sqlUpdInv =
							"UPDATE procure.Inventory "
							"SET Quantity = Quantity + @q, "
							"    LastUpdated = SYSUTCDATETIME() "
							"WHERE ProductId = @pid;";

						SqlCommand^ cmdUpdInv = gcnew SqlCommand(sqlUpdInv, conn, tx);
						cmdUpdInv->Parameters->AddWithValue("@q", addQty);
						cmdUpdInv->Parameters->AddWithValue("@pid", pid);

						int rows = cmdUpdInv->ExecuteNonQuery();

						// If no row updated, create a new inventory record
						if (rows == 0)
						{
							String^ sqlInsInv =
								"INSERT INTO procure.Inventory (ProductId, Location, Quantity, LastUpdated) "
								"VALUES (@pid, @loc, @q, SYSUTCDATETIME());";

							SqlCommand^ cmdInsInv = gcnew SqlCommand(sqlInsInv, conn, tx);
							cmdInsInv->Parameters->AddWithValue("@pid", pid);
							// Use a sensible default location; adjust if you have multiple warehouses
							cmdInsInv->Parameters->AddWithValue("@loc", "Main Store");
							cmdInsInv->Parameters->AddWithValue("@q", addQty);

							int insRows = cmdInsInv->ExecuteNonQuery();
							if (insRows <= 0)
							{
								error = "Failed to insert inventory record for product Id " + pid.ToString() + ".";
								tx->Rollback();
								return false;
							}
						}
					}
				}

				// 5) Update request status, approver and timestamp
				String^ sqlUpdReq =
					"UPDATE procure.Requests "
					"SET Status     = @status, "
					"    ApprovedBy = @ap, "
					"    ApprovedAt = SYSUTCDATETIME() "
					"WHERE Id = @id;";

				SqlCommand^ cmdUpdReq = gcnew SqlCommand(sqlUpdReq, conn, tx);
				cmdUpdReq->Parameters->AddWithValue("@status", status);

				if (approverId > 0)
					cmdUpdReq->Parameters->AddWithValue("@ap", approverId);
				else
					cmdUpdReq->Parameters->AddWithValue("@ap", DBNull::Value);

				cmdUpdReq->Parameters->AddWithValue("@id", requestId);

				int updRows = cmdUpdReq->ExecuteNonQuery();
				if (updRows <= 0)
				{
					error = "Failed to update request status.";
					tx->Rollback();
					return false;
				}

				// 6) Commit everything
				tx->Commit();
				return true;
			}
			catch (Exception^ ex)
			{
				if (tx != nullptr)
				{
					try { tx->Rollback(); }
					catch (...) {}
				}
				error = ex->Message;
				return false;
			}
			finally
			{
				if (conn != nullptr && conn->State == ConnectionState::Open)
				{
					try { conn->Close(); }
					catch (...) {}
				}
			}
		}
	};
}
