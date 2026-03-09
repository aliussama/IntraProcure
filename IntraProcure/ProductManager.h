#pragma once
#include "DatabaseManager.h"
#include "Product.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	public ref class ProductManager abstract sealed
	{
	public:
		static List<Product^>^ GetAll([System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			List<Product^>^ out = gcnew List<Product^>();
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, Name, Category, Price, ImagePath, Stock FROM procure.Products ORDER BY Name";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					Product^ p = gcnew Product();
					p->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
					p->Name = r->IsDBNull(1) ? "" : r->GetString(1);
					p->Category = r->IsDBNull(2) ? "" : r->GetString(2);
					p->Price = r->IsDBNull(3) ? 0.0 : static_cast<double>(r->GetDecimal(3));
					p->ImagePath = r->IsDBNull(4) ? "" : r->GetString(4);
					p->Stock = r->IsDBNull(5) ? 0 : r->GetInt32(5);
					out->Add(p);
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

		static Product^ GetById(int id, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (id <= 0) { error = "Invalid id"; return nullptr; }
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, Name, Category, Price, ImagePath, Stock FROM procure.Products WHERE Id=@id";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", id);
				SqlDataReader^ r = cmd->ExecuteReader();
				if (!r->Read()) { r->Close(); error = "Not found"; return nullptr; }
				Product^ p = gcnew Product();
				p->Id = r->GetInt32(0);
				p->Name = r->IsDBNull(1) ? "" : r->GetString(1);
				p->Category = r->IsDBNull(2) ? "" : r->GetString(2);
				p->Price = r->IsDBNull(3) ? 0.0 : static_cast<double>(r->GetDecimal(3));
				p->ImagePath = r->IsDBNull(4) ? "" : r->GetString(4);
				p->Stock = r->IsDBNull(5) ? 0 : r->GetInt32(5);
				r->Close();
				return p;
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

		static List<Product^>^ Search(String^ q, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (String::IsNullOrEmpty(q)) return GetAll(error);

			List<Product^>^ out = gcnew List<Product^>();
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "SELECT Id, Name, Category, Price, ImagePath, Stock FROM procure.Products WHERE Name LIKE @q OR Category LIKE @q ORDER BY Name";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@q", "%" + q + "%");
				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					Product^ p = gcnew Product();
					p->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
					p->Name = r->IsDBNull(1) ? "" : r->GetString(1);
					p->Category = r->IsDBNull(2) ? "" : r->GetString(2);
					p->Price = r->IsDBNull(3) ? 0.0 : static_cast<double>(r->GetDecimal(3));
					p->ImagePath = r->IsDBNull(4) ? "" : r->GetString(4);
					p->Stock = r->IsDBNull(5) ? 0 : r->GetInt32(5);
					out->Add(p);
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
	};
}
