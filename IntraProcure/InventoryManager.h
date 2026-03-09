#pragma once
#include "DatabaseManager.h"
#include "Product.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	public ref class InventoryRecord sealed
	{
	public:
		property int Id;
		property int ProductId;
		property String^ Location;
		property int Quantity;
		property Nullable<DateTime> LastUpdated;

		InventoryRecord() { Id = 0; ProductId = 0; Location = ""; Quantity = 0; LastUpdated = Nullable<DateTime>(); }
	};

	public ref class InventoryManager abstract sealed
	{
	public:
		static List<InventoryRecord^>^ GetInventoryForProduct(int productId, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (productId <= 0) { error = "Invalid product id"; return nullptr; }
			List<InventoryRecord^>^ out = gcnew List<InventoryRecord^>();
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, ProductId, Location, Quantity, LastUpdated FROM procure.Inventory WHERE ProductId=@pid ORDER BY Location";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@pid", productId);
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					InventoryRecord^ rec = gcnew InventoryRecord();
					rec->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
					rec->ProductId = r->IsDBNull(1) ? 0 : r->GetInt32(1);
					rec->Location = r->IsDBNull(2) ? "" : r->GetString(2);
					rec->Quantity = r->IsDBNull(3) ? 0 : r->GetInt32(3);
					rec->LastUpdated = r->IsDBNull(4) ? Nullable<DateTime>() : Nullable<DateTime>(r->GetDateTime(4));
					out->Add(rec);
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

		static int GetTotalStock(int productId, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (productId <= 0) { error = "Invalid product"; return -1; }
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT ISNULL(SUM(Quantity),0) FROM procure.Inventory WHERE ProductId=@pid";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@pid", productId);
				Object^ obj = cmd->ExecuteScalar();
				return Convert::ToInt32(obj);
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				return -1;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// AdjustStock and TransferStock can be implemented as in the earlier version but use procure.Inventory.
	};
}
