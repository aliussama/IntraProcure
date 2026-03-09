#pragma once
#include "RequestItem.h"   // uses RequestItem model: ProductId, Quantity, UnitPrice, Department maybe
#include "Product.h"
#include "Session.h"
#include "DatabaseManager.h"
#include <map>

using namespace System;
using namespace System::Collections::Generic;

namespace IntraProcure {
	public ref class CartItem sealed
	{
	public:
		int ProductId;
		String^ ProductName;
		System::Decimal UnitPrice;
		int Quantity;
		String^ Department;

		CartItem() { ProductId = 0; ProductName = ""; UnitPrice = System::Decimal::Zero; Quantity = 1; Department = ""; }
	};

	public ref class CartManager abstract sealed
	{
	private:
		// In-memory dictionary: userId -> List<CartItem^>
		static System::Collections::Generic::Dictionary<int, List<CartItem^>^>^ _carts = nullptr;

		static void EnsureInit()
		{
			if (_carts == nullptr)
				_carts = gcnew System::Collections::Generic::Dictionary<int, List<CartItem^>^>();
		}

	public:
		// Add or increase quantity
		static void AddItem(int userId, int productId, String^ productName, System::Decimal unitPrice, int quantity)
		{
			EnsureInit();
			if (!_carts->ContainsKey(userId))
				_carts[userId] = gcnew List<CartItem^>();

			List<CartItem^>^ list = _carts[userId];

			for each (CartItem ^ it in list)
			{
				if (it->ProductId == productId)
				{
					it->Quantity += quantity;
					return;
				}
			}

			CartItem^ newItem = gcnew CartItem();
			newItem->ProductId = productId;
			newItem->ProductName = productName;
			newItem->UnitPrice = unitPrice;
			newItem->Quantity = Math::Max(1, quantity);
			list->Add(newItem);
		}

		static List<CartItem^>^ GetCart(int userId)
		{
			EnsureInit();
			if (!_carts->ContainsKey(userId))
				return gcnew List<CartItem^>();
			return _carts[userId];
		}

		static void RemoveItem(int userId, int productId)
		{
			EnsureInit();
			if (!_carts->ContainsKey(userId)) return;
			List<CartItem^>^ list = _carts[userId];
			for (int i = list->Count - 1; i >= 0; --i)
			{
				if (list[i]->ProductId == productId)
					list->RemoveAt(i);
			}
		}

		static void ClearCart(int userId)
		{
			EnsureInit();
			if (!_carts->ContainsKey(userId)) return;
			_carts[userId]->Clear();
		}

		static System::Decimal GetTotal(int userId)
		{
			EnsureInit();
			System::Decimal total = System::Decimal::Zero;
			if (!_carts->ContainsKey(userId)) return total;
			for each (CartItem ^ it in _carts[userId])
			{
				total = System::Decimal::Add(total, System::Decimal::Multiply(it->UnitPrice, static_cast<System::Decimal>(it->Quantity)));
			}
			return total;
		}
	};
} // namespace
