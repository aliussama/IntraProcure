#pragma once

using namespace System;

namespace IntraProcure {
	public ref class Config abstract sealed
	{
	private:
		// Backing fields (safe for managed static data)
		static String^ _connectionString = nullptr;
		static String^ _appName = nullptr;

	public:

		// Static constructor — initialize defaults
		static Config()
		{
			// CHANGE THIS TO YOUR SQL SERVER INSTANCE
			_connectionString =
				L"Server=tcp:main-sqldb-server.database.windows.net,1433;"
				"Initial Catalog=IntraProcure;Persist Security Info=False;"
				"User ID=intra_user;Password=Db7!xQ_29Lm#;"
				"MultipleActiveResultSets=False;Encrypt=True;"
				"TrustServerCertificate=False;Connection Timeout=30;";

			_appName = L"IntraProcure";
		}

		// ----------------------------------------------------------------------
		//  PUBLIC PROPERTIES
		// ----------------------------------------------------------------------
		static property String^ ConnectionString
		{
			String ^ get() { return _connectionString; }
			void set(String ^ value)
			{
				if (!String::IsNullOrWhiteSpace(value))
					_connectionString = value;
			}
		}

			static property String^ AppName
		{
			String ^ get() { return _appName; }
			void set(String ^ value)
			{
				if (!String::IsNullOrWhiteSpace(value))
					_appName = value;
			}
		}

			// ----------------------------------------------------------------------
			//  PUBLIC METHODS — THIS IS WHAT YOUR MANAGERS CALL
			// ----------------------------------------------------------------------

			/// <summary>
			/// Returns the SQL connection string used by all managers.
			/// </summary>
			static String^ GetConnectionString()
		{
			return _connectionString;
		}

		/// <summary>
		/// Allows updating the connection string dynamically.
		/// </summary>
		static void SetConnectionString(String^ conn)
		{
			if (!String::IsNullOrWhiteSpace(conn))
				_connectionString = conn;
		}
	};
}
