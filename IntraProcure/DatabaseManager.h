#pragma once
#include "Config.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	public ref class DatabaseManager abstract sealed
	{
	public:

		// Create a connection object (caller should Open/Close)
		static SqlConnection^ CreateConnection()
		{
			String^ cs = Config::GetConnectionString();
			return gcnew SqlConnection(cs);
		}

		// Simple test helper - returns true on success, optionally set error
		static bool TestConnection([System::Runtime::InteropServices::Out] String^% error)
		{
			error = nullptr;
			SqlConnection^ conn = CreateConnection();
			try
			{
				conn->Open();
				conn->Close();
				return true;
			}
			catch (Exception^ ex)
			{
				error = ex->Message;
				try { if (conn->State == ConnectionState::Open) conn->Close(); }
				catch (...) {}
				return false;
			}
		}
	};
}
