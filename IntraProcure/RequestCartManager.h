#pragma once
#include "Session.h"

using namespace System;
using namespace System::Collections::Generic;

namespace IntraProcure {
	public ref class RequestCartManager abstract sealed
	{
	public:
		// Add product to cart (increase quantity if exists)
		static void AddToCart(int productId, int qty)
		{
			if (productId <= 0 || qty <= 0) return;
			if (Session::Cart->ContainsKey(productId))
			{
				int current = Session::Cart[productId];
				Session::Cart[productId] = current + qty;
			}
			else
			{
				Session::Cart->Add(productId, qty);
			}
		}

		static void SetQuantity(int productId, int qty)
		{
			if (productId <= 0) return;
			if (qty <= 0)
			{
				if (Session::Cart->ContainsKey(productId)) Session::Cart->Remove(productId);
				return;
			}
			Session::Cart[productId] = qty;
		}

		static void RemoveFromCart(int productId)
		{
			if (productId <= 0) return;
			if (Session::Cart->ContainsKey(productId)) Session::Cart->Remove(productId);
		}

		static void ClearCart()
		{
			Session::Cart->Clear();
		}

		static Dictionary<int, int>^ GetCart()
		{
			// return the actual cart reference; UI should clone if it needs edits without affecting session
			return Session::Cart;
		}

		// Simple total items count
		static int TotalItems()
		{
			int total = 0;
			for each (KeyValuePair<int, int> kv in Session::Cart)
				total += kv.Value;
			return total;
		}
	};
}
