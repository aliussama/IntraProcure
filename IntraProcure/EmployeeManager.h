#pragma once
#include "DatabaseManager.h"
#include "Employee.h"

using namespace System;
using namespace System::Text;
using namespace System::Security::Cryptography;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Collections::Generic;

namespace IntraProcure {
	public ref class EmployeeManager abstract sealed
	{
	private:
		static String^ HashPassword(String^ password, String^ salt)
		{
			if (password == nullptr) password = "";
			if (salt == nullptr) salt = "";

			array<unsigned char>^ passBytes = Encoding::UTF8->GetBytes(password + salt);
			SHA256^ sha = SHA256::Create();
			array<unsigned char>^ hash = sha->ComputeHash(passBytes);
			StringBuilder^ sb = gcnew StringBuilder();
			for each(unsigned char b in hash)
				sb->AppendFormat("{0:x2}", b);
			delete sha;
			return sb->ToString();
		}

		static String^ GenerateSalt(int length)
		{
			if (length <= 0) length = 16;
			array<unsigned char>^ bytes = gcnew array<unsigned char>(length);
			RNGCryptoServiceProvider^ rng = gcnew RNGCryptoServiceProvider();
			rng->GetBytes(bytes);
			StringBuilder^ sb = gcnew StringBuilder(length * 2);
			for each(unsigned char b in bytes)
				sb->AppendFormat("{0:x2}", b);
			delete rng;
			return sb->ToString();
		}

	public:

		// Authenticate user (returns Employee or nullptr, sets error)
		static Employee^ Authenticate(String^ username, String^ password, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (String::IsNullOrWhiteSpace(username) || String::IsNullOrEmpty(password))
			{
				error = "Username and password are required.";
				return nullptr;
			}

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"SELECT Id, Username, FullName, Email, IsManager, IsAdministrator, "
					"       PasswordHash, PasswordSalt, "
					"       Department, Title, Phone, Country, City, Address, PicturePath, ProfileImage "
					"FROM procure.Employees "
					"WHERE Username=@u";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@u", username->Trim());
				SqlDataReader^ r = cmd->ExecuteReader();
				if (!r->Read()) { r->Close(); error = "Incorrect username or password."; return nullptr; }

				String^ storedHash = r->IsDBNull(6) ? "" : r->GetString(6);
				String^ storedSalt = r->IsDBNull(7) ? "" : r->GetString(7);

				// If previous seed used 'TEMP' sentinel (legacy), treat as mismatch - app should bootstrap admin differently
				if (String::IsNullOrEmpty(storedHash) || String::Equals(storedHash, "TEMP", StringComparison::OrdinalIgnoreCase))
				{
					r->Close();
					error = "Account not initialized. Contact administrator.";
					return nullptr;
				}

				String^ computed = HashPassword(password, storedSalt);
				if (!String::Equals(computed, storedHash, StringComparison::OrdinalIgnoreCase))
				{
					r->Close();
					error = "Incorrect username or password.";
					return nullptr;
				}

				Employee^ e = gcnew Employee();
				e->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
				e->Username = r->IsDBNull(1) ? "" : r->GetString(1);
				e->FullName = r->IsDBNull(2) ? "" : r->GetString(2);
				e->Email = r->IsDBNull(3) ? "" : r->GetString(3);
				e->IsManager = r->IsDBNull(4) ? false : r->GetBoolean(4);
				e->IsAdministrator = r->IsDBNull(5) ? false : r->GetBoolean(5);
				e->PasswordHash = storedHash;
				e->PasswordSalt = storedSalt;
				e->Department = r->IsDBNull(8) ? "" : r->GetString(8);
				e->Title = r->IsDBNull(9) ? "" : r->GetString(9);
				e->Phone = r->IsDBNull(10) ? "" : r->GetString(10);
				e->Country = r->IsDBNull(11) ? "" : r->GetString(11);
				e->City = r->IsDBNull(12) ? "" : r->GetString(12);
				e->Address = r->IsDBNull(13) ? "" : r->GetString(13);
				int idxProfileImage = r->GetOrdinal("ProfileImage");
				if (!r->IsDBNull(idxProfileImage))
				{
					long len = (long)r->GetBytes(idxProfileImage, 0, nullptr, 0, 0);
					array<System::Byte>^ buf = gcnew array<System::Byte>(len);
					r->GetBytes(idxProfileImage, 0, buf, 0, len);
					e->ProfileImage = buf;
				}
				else
				{
					e->ProfileImage = nullptr;
				}
				r->Close();
				return e;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				try { if (conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
				return nullptr;
			}
			finally
			{
				try { if (conn != nullptr && conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
			}
		}

		// Create employee (returns true on success)
		static bool CreateEmployee(Employee^ e, String^ password, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (e == nullptr || String::IsNullOrWhiteSpace(e->Username) || String::IsNullOrWhiteSpace(password))
			{
				error = "Username and password are required.";
				return false;
			}

			String^ salt = GenerateSalt(16);
			String^ hash = HashPassword(password, salt);

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql = "INSERT INTO procure.Employees (Username, FullName, Email, IsManager, IsAdministrator, PasswordHash, PasswordSalt, Department, Title, Phone, Country, City, Address, PicturePath) "
					"VALUES (@u,@fn,@em,@isM,@isA,@hash,@salt,@dept,@title,@phone,@country,@city,@addr,@pic); SELECT SCOPE_IDENTITY();";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@u", e->Username);
				cmd->Parameters->AddWithValue("@fn", String::IsNullOrEmpty(e->FullName) ? DBNull::Value : static_cast<Object^>(e->FullName));
				cmd->Parameters->AddWithValue("@em", String::IsNullOrEmpty(e->Email) ? DBNull::Value : static_cast<Object^>(e->Email));
				cmd->Parameters->AddWithValue("@isM", e->IsManager);
				cmd->Parameters->AddWithValue("@isA", e->IsAdministrator);
				cmd->Parameters->AddWithValue("@hash", hash);
				cmd->Parameters->AddWithValue("@salt", salt);
				cmd->Parameters->AddWithValue("@dept", String::IsNullOrEmpty(e->Department) ? DBNull::Value : static_cast<Object^>(e->Department));
				cmd->Parameters->AddWithValue("@title", String::IsNullOrEmpty(e->Title) ? DBNull::Value : static_cast<Object^>(e->Title));
				cmd->Parameters->AddWithValue("@phone", String::IsNullOrEmpty(e->Phone) ? DBNull::Value : static_cast<Object^>(e->Phone));
				cmd->Parameters->AddWithValue("@country", String::IsNullOrEmpty(e->Country) ? DBNull::Value : static_cast<Object^>(e->Country));
				cmd->Parameters->AddWithValue("@city", String::IsNullOrEmpty(e->Country) ? DBNull::Value : static_cast<Object^>(e->City));
				cmd->Parameters->AddWithValue("@addr", String::IsNullOrEmpty(e->Address) ? DBNull::Value : static_cast<Object^>(e->Address));
				cmd->Parameters->AddWithValue("@pic", String::IsNullOrEmpty(e->PicturePath) ? DBNull::Value : static_cast<Object^>(e->PicturePath));

				Object^ idobj = cmd->ExecuteScalar();
				e->Id = Convert::ToInt32(idobj);
				e->PasswordHash = hash;
				e->PasswordSalt = salt;
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

		// Get employee by id
		static Employee^ GetById(int id, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (id <= 0) { error = "Invalid id"; return nullptr; }
			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();
				String^ sql =
					"SELECT Id, Username, FullName, Email, IsManager, IsAdministrator, "
					"       Department, Title, Phone, Country, City, Address, PicturePath, ProfileImage "
					"FROM procure.Employees WHERE Id=@id";
				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", id);
				SqlDataReader^ r = cmd->ExecuteReader();
				if (!r->Read()) { r->Close(); error = "Not found"; return nullptr; }
				Employee^ e = gcnew Employee();
				e->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);
				e->Username = r->IsDBNull(1) ? "" : r->GetString(1);
				e->FullName = r->IsDBNull(2) ? "" : r->GetString(2);
				e->Email = r->IsDBNull(3) ? "" : r->GetString(3);
				e->IsManager = r->IsDBNull(4) ? false : r->GetBoolean(4);
				e->IsAdministrator = r->IsDBNull(5) ? false : r->GetBoolean(5);
				e->Department = r->IsDBNull(6) ? "" : r->GetString(6);
				e->Title = r->IsDBNull(7) ? "" : r->GetString(7);
				e->Phone = r->IsDBNull(8) ? "" : r->GetString(8);
				e->Country = r->IsDBNull(9) ? "" : r->GetString(9);
				e->City = r->IsDBNull(10) ? "" : r->GetString(10);
				e->Address = r->IsDBNull(11) ? "" : r->GetString(11);
				e->PicturePath = r->IsDBNull(12) ? "" : r->GetString(12);
				if (!r->IsDBNull(13))
				{
					long len = (long)r->GetBytes(13, 0, nullptr, 0, 0);
					array<System::Byte>^ buf = gcnew array<System::Byte>(len);
					r->GetBytes(13, 0, buf, 0, len);
					e->ProfileImage = buf;
				}
				else
				{
					e->ProfileImage = nullptr;
				}
				r->Close();
				return e;
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

		// Update basic profile data + profile image
		static bool UpdateProfile(Employee^ e, [System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			if (e == nullptr || e->Id <= 0)
			{
				error = "Invalid employee.";
				return false;
			}

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();

				String^ sql =
					"UPDATE procure.Employees "
					"SET FullName   = @fn, "
					"    Email      = @em, "
					"    Department = @dept, "
					"    Title      = @title, "
					"    Phone      = @phone, "
					"    Country    = @country, "
					"    City       = @city, "
					"    Address    = @addr, "
					"    ProfileImage = @img "
					"WHERE Id = @id;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@id", e->Id);
				cmd->Parameters->AddWithValue("@fn",
					String::IsNullOrEmpty(e->FullName) ? DBNull::Value : static_cast<Object^>(e->FullName));
				cmd->Parameters->AddWithValue("@em",
					String::IsNullOrEmpty(e->Email) ? DBNull::Value : static_cast<Object^>(e->Email));
				cmd->Parameters->AddWithValue("@dept",
					String::IsNullOrEmpty(e->Department) ? DBNull::Value : static_cast<Object^>(e->Department));
				cmd->Parameters->AddWithValue("@title",
					String::IsNullOrEmpty(e->Title) ? DBNull::Value : static_cast<Object^>(e->Title));
				cmd->Parameters->AddWithValue("@phone",
					String::IsNullOrEmpty(e->Phone) ? DBNull::Value : static_cast<Object^>(e->Phone));
				cmd->Parameters->AddWithValue("@country",
					String::IsNullOrEmpty(e->Country) ? DBNull::Value : static_cast<Object^>(e->Country));
				cmd->Parameters->AddWithValue("@city",
					String::IsNullOrEmpty(e->City) ? DBNull::Value : static_cast<Object^>(e->City));
				cmd->Parameters->AddWithValue("@addr",
					String::IsNullOrEmpty(e->Address) ? DBNull::Value : static_cast<Object^>(e->Address));

				if (e->ProfileImage != nullptr && e->ProfileImage->Length > 0)
				{
					cmd->Parameters->Add("@img", SqlDbType::VarBinary)->Value = e->ProfileImage;
				}
				else
				{
					cmd->Parameters->AddWithValue("@img", DBNull::Value);
				}

				int rows = cmd->ExecuteNonQuery();
				return (rows > 0);
			}
			catch (Exception^ ex)
			{
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
