#pragma once
using namespace System;

namespace IntraProcure {
	public ref class Employee sealed
	{
	public:
		property int Id;
		property String^ Username;
		property String^ FullName;
		property String^ Email;
		property bool IsManager;
		property bool IsAdministrator;
		property String^ PasswordHash; // stored but not exposed in UI
		property String^ PasswordSalt;

		// extended profile
		property String^ Department;
		property String^ Title;
		property String^ Phone;
		property String^ Country;
		property String^ City;
		property String^ Address;
		property String^ PicturePath;          // (legacy) path to profile picture
		property array<System::Byte>^ ProfileImage; // NEW: image bytes from DB

		Employee()
		{
			Id = 0;
			Username = "";
			FullName = "";
			Email = "";
			IsManager = false;
			IsAdministrator = false;
			PasswordHash = "";
			PasswordSalt = "";
			Department = "";
			Title = "";
			Phone = "";
			Country = "";
			City = "";
			Address = "";
			PicturePath = "";
			ProfileImage = nullptr;
		}
	};
}