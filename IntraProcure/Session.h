#pragma once

#include "Employee.h"

using namespace System;
using namespace System::Collections::Generic;

namespace IntraProcure {
	public ref class Session abstract sealed
	{
	private:
		static int _userId = 0;
		static String^ _username = nullptr;
		static String^ _fullName = nullptr;
		static bool _isManager = false;
		static bool _isAdministrator = false;

		// Profile extras that we care about for UI
		static String^ _department = nullptr;
		static String^ _email = nullptr;
		static array<Byte>^ _photo = nullptr;     // employee profile picture (from DB)

		// Fired whenever the current user data changes
	public:
		static Action^ CurrentUserChanged;

	public:
		// ───── Properties (safe, assignable everywhere) ───────────────

		static property int UserId {
			int get() { return _userId; }
			void set(int v) { _userId = v; }
		}

		static property String^ Username {
			String^ get() { return _username; }
			void set(String^ v) { _username = v; }
		}

		static property String^ FullName {
			String^ get() { return _fullName; }
			void set(String^ v) { _fullName = v; }
		}

		static property bool IsManager {
			bool get() { return _isManager; }
			void set(bool v) { _isManager = v; }
		}

		static property bool IsAdministrator {
			bool get() { return _isAdministrator; }
			void set(bool v) { _isAdministrator = v; }
		}

		static property String^ Department {
			String^ get() { return _department; }
			void set(String^ v) { _department = v; }
		}

		static property String^ Email {
			String^ get() { return _email; }
			void set(String^ v) { _email = v; }
		}

		static property array<Byte>^ Photo {
			array<Byte>^ get() { return _photo; }
			void set(array<Byte>^ v) { _photo = v; }
		}

		// --------------------------------------------------
		//  Convenience: return the current user as Employee^
		// --------------------------------------------------
		static Employee^ CurrentUser()
		{
			if (_userId <= 0) return nullptr;

			Employee^ e = gcnew Employee();
			e->Id = _userId;
			e->Username = _username;
			e->FullName = _fullName;
			e->IsManager = _isManager;
			e->IsAdministrator = _isAdministrator;
			e->Department = _department;
			e->Email = _email;
			e->ProfileImage = _photo;
			return e;
		}

		static void InitializeFromLogin(
			int userId,
			String^ username,
			String^ fullName,
			bool isManager,
			bool isAdministrator,
			String^ department,
			String^ email,
			array<Byte>^ photoBytes
		)
		{
			_userId = userId;
			_username = username;
			_fullName = fullName;
			_isManager = isManager;
			_isAdministrator = isAdministrator;
			_department = department;
			_email = email;
			_photo = photoBytes;

			RaiseCurrentUserChanged();
		}

		static void UpdateProfile(String^ fullName, String^ department,
			String^ email, array<Byte>^ photoBytes)
		{
			if (!String::IsNullOrEmpty(fullName))
				_fullName = fullName;

			_department = department;
			_email = email;
			_photo = photoBytes;

			RaiseCurrentUserChanged();
		}

		static property bool IsLoggedIn
		{
			bool get()
			{
				return _userId > 0;
			}
		}

		// ───── Clear session ───────────────────────────────────────────

		static void Clear()
		{
			_userId = 0;
			_username = nullptr;
			_fullName = nullptr;
			_isManager = false;
			_isAdministrator = false;
			_department = nullptr;
			_email = nullptr;
			_photo = nullptr;

			RaiseCurrentUserChanged();
		}

	private:
		static void RaiseCurrentUserChanged()
		{
			if (CurrentUserChanged != nullptr)
			{
				CurrentUserChanged();
			}
		}
	};
}