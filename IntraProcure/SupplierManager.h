#pragma once
#include "DatabaseManager.h"
#include "Supplier.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	public ref class SupplierManager abstract sealed
	{
	public:
		// Get all suppliers (already had this)
		static List<Supplier^>^ GetAll([System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			List<Supplier^>^ out = gcnew List<Supplier^>();
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"SELECT Id, Name, Contact, Email, Phone, Address, CreatedAt "
					"FROM procure.Suppliers "
					"ORDER BY Name;";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					Supplier^ s = gcnew Supplier();
					s->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
					s->Name = r->IsDBNull(1) ? "" : r->GetString(1);
					s->ContactName = r->IsDBNull(2) ? "" : r->GetString(2);
					s->Email = r->IsDBNull(3) ? "" : r->GetString(3);
					s->Phone = r->IsDBNull(4) ? "" : r->GetString(4);
					s->Address = r->IsDBNull(5) ? "" : r->GetString(5);
					// CreatedAt in column 6 if you ever want to map it
					out->Add(s);
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

		// Optional helper: get one supplier by ID
		static Supplier^ GetById(int id, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (id <= 0) { error = "Invalid supplier Id."; return nullptr; }

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"SELECT Id, Name, Contact, Email, Phone, Address, CreatedAt "
					"FROM procure.Suppliers "
					"WHERE Id = @id;";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", id);
				SqlDataReader^ r = cmd->ExecuteReader();
				if (!r->Read())
				{
					r->Close();
					return nullptr;
				}

				Supplier^ s = gcnew Supplier();
				s->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
				s->Name = r->IsDBNull(1) ? "" : r->GetString(1);
				s->ContactName = r->IsDBNull(2) ? "" : r->GetString(2);
				s->Email = r->IsDBNull(3) ? "" : r->GetString(3);
				s->Phone = r->IsDBNull(4) ? "" : r->GetString(4);
				s->Address = r->IsDBNull(5) ? "" : r->GetString(5);

				r->Close();
				return s;
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

		// CREATE: insert new supplier, set s->Id from SCOPE_IDENTITY()
		static bool CreateSupplier(Supplier^ s, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (s == nullptr) { error = "Supplier is null."; return false; }
			if (String::IsNullOrWhiteSpace(s->Name))
			{
				error = "Supplier name is required.";
				return false;
			}

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"INSERT INTO procure.Suppliers (Name, Contact, Email, Phone, Address, CreatedAt) "
					"VALUES (@name, @contact, @email, @phone, @address, SYSUTCDATETIME()); "
					"SELECT SCOPE_IDENTITY();";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@name", s->Name);
				cmd->Parameters->AddWithValue("@contact",
					String::IsNullOrEmpty(s->ContactName) ? (Object^)DBNull::Value : (Object^)s->ContactName);
				cmd->Parameters->AddWithValue("@email",
					String::IsNullOrEmpty(s->Email) ? (Object^)DBNull::Value : (Object^)s->Email);
				cmd->Parameters->AddWithValue("@phone",
					String::IsNullOrEmpty(s->Phone) ? (Object^)DBNull::Value : (Object^)s->Phone);
				cmd->Parameters->AddWithValue("@address",
					String::IsNullOrEmpty(s->Address) ? (Object^)DBNull::Value : (Object^)s->Address);

				Object^ idObj = cmd->ExecuteScalar();
				if (idObj == nullptr || idObj == DBNull::Value)
				{
					error = "Failed to retrieve new supplier Id.";
					return false;
				}

				int newId = Convert::ToInt32(idObj);
				s->Id = newId;

				return true;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return false;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// UPDATE: modify existing supplier
		static bool UpdateSupplier(Supplier^ s, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (s == nullptr) { error = "Supplier is null."; return false; }
			if (s->Id <= 0) { error = "Supplier Id is invalid."; return false; }
			if (String::IsNullOrWhiteSpace(s->Name))
			{
				error = "Supplier name is required.";
				return false;
			}

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"UPDATE procure.Suppliers "
					"SET Name = @name, "
					"    Contact = @contact, "
					"    Email = @email, "
					"    Phone = @phone, "
					"    Address = @address "
					"WHERE Id = @id;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", s->Id);
				cmd->Parameters->AddWithValue("@name", s->Name);
				cmd->Parameters->AddWithValue("@contact",
					String::IsNullOrEmpty(s->ContactName) ? (Object^)DBNull::Value : (Object^)s->ContactName);
				cmd->Parameters->AddWithValue("@email",
					String::IsNullOrEmpty(s->Email) ? (Object^)DBNull::Value : (Object^)s->Email);
				cmd->Parameters->AddWithValue("@phone",
					String::IsNullOrEmpty(s->Phone) ? (Object^)DBNull::Value : (Object^)s->Phone);
				cmd->Parameters->AddWithValue("@address",
					String::IsNullOrEmpty(s->Address) ? (Object^)DBNull::Value : (Object^)s->Address);

				int rows = cmd->ExecuteNonQuery();
				if (rows <= 0)
				{
					error = "No rows were updated. The supplier may not exist.";
					return false;
				}

				return true;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return false;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// DELETE: remove supplier by Id
		static bool DeleteSupplier(int id, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (id <= 0) { error = "Invalid supplier Id."; return false; }

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"DELETE FROM procure.Suppliers "
					"WHERE Id = @id;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", id);
				int rows = cmd->ExecuteNonQuery();

				if (rows <= 0)
				{
					error = "No rows were deleted. The supplier may not exist.";
					return false;
				}

				return true;
			}
			catch (SqlException^ ex)
			{
				// Common case: FK constraint (supplier used in products, orders, etc.)
				error = ex->Message;
				return false;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return false;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// (You can add SearchByName, etc. later similarly.)
	};
}
