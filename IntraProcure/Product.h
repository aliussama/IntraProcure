#pragma once
using namespace System;

namespace IntraProcure {
	public ref class Product sealed
	{
	public:
		property int Id;
		property String^ Name;
		property String^ Category;
		property double Price;
		property int Stock;           // matches dbo.Products.Stock
		property String^ ImagePath;

		Product()
		{
			Id = 0;
			Name = "";
			Category = "";
			Price = 0.0;
			Stock = 0;
			ImagePath = "";
		}
	};
}