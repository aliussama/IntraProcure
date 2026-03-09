#pragma once
using namespace System;

namespace IntraProcure {
	public ref class Supplier sealed
	{
	public:
		property int Id;
		property String^ Name;
		property String^ ContactName;
		property String^ Email;
		property String^ Phone;
		property String^ Address;
		property String^ Currency;
		property String^ PaymentTerms;
		property String^ Notes;
		property Nullable<DateTime> CreatedAt;

		Supplier()
		{
			Id = 0;
			Name = "";
			ContactName = "";
			Email = "";
			Phone = "";
			Address = "";
			Currency = "";
			PaymentTerms = "";
			Notes = "";
			CreatedAt = Nullable<DateTime>();
		}
	};
}
