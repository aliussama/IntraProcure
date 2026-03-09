#pragma once
#include "RequestItem.h"
using namespace System;
using namespace System::Collections::Generic;

namespace IntraProcure {
	public ref class Request sealed
	{
	public:
		property int Id;
		property int EmployeeId;
		property String^ Department;
		property double Total;
		property String^ Status; // Pending / Approved / Rejected
		property String^ Remarks;
		property Nullable<DateTime> CreatedAt;
		property Nullable<DateTime> ApprovedAt;
		property Nullable<int> ApprovedBy;

		property List<RequestItem^>^ Items;

		Request()
		{
			Id = 0;
			EmployeeId = 0;
			Department = "";
			Total = 0.0;
			Status = "Pending";
			Remarks = "";
			CreatedAt = Nullable<DateTime>();
			ApprovedAt = Nullable<DateTime>();
			ApprovedBy = Nullable<int>();
			Items = gcnew List<RequestItem^>();
		}

		void RecalculateTotal()
		{
			double sum = 0.0;
			for each (RequestItem ^ it in Items)
				sum += it->LineTotal();
			Total = sum;
		}
	};
}
