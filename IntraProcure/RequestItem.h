#pragma once
using namespace System;

namespace IntraProcure {
	public ref class RequestItem sealed
	{
	public:
		property int Id;
		property int RequestId;
		property int ProductId;
		property int Quantity;
		property double UnitPrice;
		property String^ Department;

		RequestItem()
		{
			Id = 0;
			RequestId = 0;
			ProductId = 0;
			Quantity = 0;
			UnitPrice = 0.0;
			Department = "";
		}

		double LineTotal()
		{
			return (double)Quantity * UnitPrice;
		}
	};
}
