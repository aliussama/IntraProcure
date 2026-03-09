#pragma once

#include "UiStyler.h"
#include "CartManager.h"
#include "RequestManager.h"
#include "Session.h"
#include "EmployeeManager.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for RequestCartForm
	/// </summary>
	public ref class RequestCartForm : public System::Windows::Forms::Form
	{
	public:
		RequestCartForm(void)
		{
			InitializeComponent();
			LoadCart();

			UiStyler::StyleGrid(gridCart);
			UiStyler::StylePrimaryButton(btnProceed);
			UiStyler::StyleSecondaryButton(btnClear);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RequestCartForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
	private: System::Windows::Forms::Label^ lblTitle;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Panel^ panelGrid;
	private: System::Windows::Forms::DataGridView^ gridCart;
	private: SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelFooter;

	private: System::Windows::Forms::Label^ lblTotal;

	private: SiticoneNetFrameworkUI::SiticoneButton^ btnClear;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnProceed;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;

	private:
		// Represents a row in the cart for now
		ref struct CartRow
		{
			int Id;
			String^ Name;
			int Quantity;
			double UnitPrice;
		};

		// runtime temp
		List<CartItem^>^ _cartItems;   // uses CartManager::CartItem

	private:

	private:
		// Load cart items from CartManager and show in grid
		void LoadCart()
		{
			try
			{
				int uid = Session::UserId;
				_cartItems = CartManager::GetCart(uid);

				PopulateCartGrid();
				UpdateTotals();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(L"Failed to load cart: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		// Replace the PopulateCartGrid and UpdateTotals methods with these updated implementations:

		void PopulateCartGrid()
		{
			// Clear existing rows
			gridCart->Rows->Clear();
			gridCart->Columns->Clear();

			// Create columns if they don't exist (Id hidden, ProductName, UnitPrice, Qty, Subtotal, Remove button)
			DataGridViewTextBoxColumn^ colProdId = gcnew DataGridViewTextBoxColumn();
			colProdId->Name = L"ProductId";
			colProdId->HeaderText = L"ProductId";
			colProdId->Visible = false;
			gridCart->Columns->Add(colProdId);

			DataGridViewTextBoxColumn^ colName = gcnew DataGridViewTextBoxColumn();
			colName->Name = L"ProductName";
			colName->HeaderText = L"Product";
			colName->ReadOnly = true;
			colName->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			gridCart->Columns->Add(colName);

			DataGridViewTextBoxColumn^ colUnit = gcnew DataGridViewTextBoxColumn();
			colUnit->Name = L"UnitPrice";
			colUnit->HeaderText = L"Unit Price";
			colUnit->ReadOnly = true;
			colUnit->ValueType = System::Decimal::typeid;
			colUnit->Width = 100;
			gridCart->Columns->Add(colUnit);

			DataGridViewTextBoxColumn^ colQty = gcnew DataGridViewTextBoxColumn();
			colQty->Name = L"Quantity";
			colQty->HeaderText = L"Qty";
			colQty->Width = 60;
			colQty->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			gridCart->Columns->Add(colQty);

			DataGridViewTextBoxColumn^ colSub = gcnew DataGridViewTextBoxColumn();
			colSub->Name = L"Subtotal";
			colSub->HeaderText = L"Subtotal";
			colSub->ReadOnly = true;
			colSub->ValueType = System::Decimal::typeid;
			colSub->Width = 110;
			gridCart->Columns->Add(colSub);

			DataGridViewButtonColumn^ colRemove = gcnew DataGridViewButtonColumn();
			colRemove->Name = L"Remove";
			colRemove->HeaderText = L"";
			colRemove->Text = L"Remove";
			colRemove->UseColumnTextForButtonValue = true;
			colRemove->Width = 80;
			gridCart->Columns->Add(colRemove);

			// Fill rows
			for each(CartItem ^ it in _cartItems)
			{
				array<Object^>^ row = gcnew array<Object^>(6);
				row[0] = it->ProductId;
				row[1] = it->ProductName;
				row[2] = String::Format("{0:N2} EGP", it->UnitPrice);
				row[3] = it->Quantity;
				row[4] = String::Format("{0:N2} EGP", System::Decimal::Multiply(it->UnitPrice, safe_cast<System::Decimal>(it->Quantity)));
				row[5] = L"Remove";
				gridCart->Rows->Add(row);
			}

			// Make quantity column editable
			gridCart->Columns[L"Quantity"]->ReadOnly = false;
		}

		void UpdateTotals()
		{
			try
			{
				System::Decimal total = System::Decimal::Zero;
				for each(CartItem ^ it in _cartItems)
					total = System::Decimal::Add(total, System::Decimal::Multiply(it->UnitPrice, safe_cast<System::Decimal>(it->Quantity)));

				// Format total with two decimals and explicit "EGP" suffix
				lblTotal->Text = String::Format("{0:N2} EGP", total);
			}
			catch (Exception^)
			{
				lblTotal->Text = L"--";
			}
		}

		// Remove button clicked in grid (button column)
	private: System::Void gridCart_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex < 0) return;

		try
		{
			if (gridCart->Columns[e->ColumnIndex]->Name == L"Remove")
			{
				int pid = Convert::ToInt32(gridCart->Rows[e->RowIndex]->Cells[L"ProductId"]->Value);
				CartManager::RemoveItem(Session::UserId, pid);

				// Reload cart and UI
				LoadCart();
			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(L"Error removing item: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		   // Quantity cell changed - update cart
	private: System::Void gridCart_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex < 0) return;

		try
		{
			if (gridCart->Columns[e->ColumnIndex]->Name == L"Quantity")
			{
				int pid = Convert::ToInt32(gridCart->Rows[e->RowIndex]->Cells[L"ProductId"]->Value);
				Object^ val = gridCart->Rows[e->RowIndex]->Cells[L"Quantity"]->Value;
				int qty = 1;
				try { qty = System::Convert::ToInt32(val); }
				catch (...) { qty = 1; }
				if (qty <= 0) qty = 1;

				// update in CartManager
				// remove and re-add with quantity
				CartManager::RemoveItem(Session::UserId, pid);

				String^ prodName = gridCart->Rows[e->RowIndex]->Cells[L"ProductName"]->Value->ToString();
				System::Decimal unit = safe_cast<System::Decimal>(gridCart->Rows[e->RowIndex]->Cells[L"UnitPrice"]->Value);

				CartManager::AddItem(Session::UserId, pid, prodName, unit, qty);

				// reload
				LoadCart();
			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(L"Error updating quantity: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

		   // Clear button
	private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto res = MessageBox::Show(L"Clear all items from the cart?", L"Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (res != System::Windows::Forms::DialogResult::Yes) return;
		CartManager::ClearCart(Session::UserId);
		LoadCart();
	}

		   // Proceed / Submit
	private: System::Void btnProceed_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			if (_cartItems == nullptr || _cartItems->Count == 0)
			{
				MessageBox::Show(L"Cart is empty.", L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			String^ error;

			// Build RequestItem list for RequestManager
			List<RequestItem^>^ items = gcnew List<RequestItem^>();
			for each(CartItem ^ it in _cartItems)
			{
				RequestItem^ ri = gcnew RequestItem();
				ri->ProductId = it->ProductId;
				ri->Quantity = it->Quantity;
				ri->UnitPrice = safe_cast<System::Double>(it->UnitPrice);
				ri->Department = EmployeeManager::GetById(Session::UserId, error)->Department;
				items->Add(ri);
			}

			String^ err = nullptr;
			int newId = RequestManager::CreateRequest(Session::UserId, items, err);
			if (newId <= 0)
			{
				MessageBox::Show(L"Failed to submit request: " + (err == nullptr ? L"Unknown" : err), L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			MessageBox::Show(L"Request submitted successfully. Request Id: " + newId.ToString(), L"Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Clear cart after successful submission
			CartManager::ClearCart(Session::UserId);
			LoadCart();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(L"Error submitting request: " + ex->Message, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->panelGrid = (gcnew System::Windows::Forms::Panel());
			   this->gridCart = (gcnew System::Windows::Forms::DataGridView());
			   this->panelFooter = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->lblTotal = (gcnew System::Windows::Forms::Label());
			   this->btnClear = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnProceed = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			   this->panelHeader->SuspendLayout();
			   this->panelGrid->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->BeginInit();
			   this->panelFooter->SuspendLayout();
			   this->siticonePanel1->SuspendLayout();
			   this->SuspendLayout();
			   //
			   // panelHeader
			   //
			   this->panelHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelHeader->Controls->Add(this->lblTitle);
			   this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			   this->panelHeader->Location = System::Drawing::Point(0, 0);
			   this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelHeader->Name = L"panelHeader";
			   this->panelHeader->Padding = System::Windows::Forms::Padding(16);
			   this->panelHeader->Size = System::Drawing::Size(916, 72);
			   this->panelHeader->TabIndex = 1;
			   //
			   // lblTitle
			   //
			   this->lblTitle->AutoSize = true;
			   this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			   this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->lblTitle->Location = System::Drawing::Point(16, 20);
			   this->lblTitle->Name = L"lblTitle";
			   this->lblTitle->Size = System::Drawing::Size(126, 25);
			   this->lblTitle->TabIndex = 0;
			   this->lblTitle->Text = L"Request Cart";
			   //
			   // panelGrid
			   //
			   this->panelGrid->BackColor = System::Drawing::Color::Transparent;
			   this->panelGrid->Controls->Add(this->gridCart);
			   this->panelGrid->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panelGrid->Location = System::Drawing::Point(2, 2);
			   this->panelGrid->Name = L"panelGrid";
			   this->panelGrid->Padding = System::Windows::Forms::Padding(16);
			   this->panelGrid->Size = System::Drawing::Size(911, 375);
			   this->panelGrid->TabIndex = 0;
			   //
			   // gridCart
			   //
			   this->gridCart->AllowUserToAddRows = false;
			   this->gridCart->AllowUserToDeleteRows = false;
			   this->gridCart->AllowUserToResizeRows = false;
			   this->gridCart->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			   this->gridCart->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->gridCart->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->gridCart->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			   this->gridCart->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->gridCart->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->gridCart->Location = System::Drawing::Point(16, 16);
			   this->gridCart->Name = L"gridCart";
			   this->gridCart->ReadOnly = true;
			   this->gridCart->RowHeadersVisible = false;
			   this->gridCart->RowTemplate->Height = 44;
			   this->gridCart->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			   this->gridCart->Size = System::Drawing::Size(879, 343);
			   this->gridCart->TabIndex = 0;
			   this->gridCart->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RequestCartForm::gridCart_CellContentClick);
			   this->gridCart->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RequestCartForm::gridCart_CellEndEdit);
			   //
			   // panelFooter
			   //
			   this->panelFooter->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelFooter->Controls->Add(this->lblTotal);
			   this->panelFooter->Controls->Add(this->btnClear);
			   this->panelFooter->Controls->Add(this->btnProceed);
			   this->panelFooter->Dock = System::Windows::Forms::DockStyle::Bottom;
			   this->panelFooter->Location = System::Drawing::Point(2, 377);
			   this->panelFooter->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelFooter->Name = L"panelFooter";
			   this->panelFooter->Padding = System::Windows::Forms::Padding(16);
			   this->panelFooter->Size = System::Drawing::Size(911, 92);
			   this->panelFooter->TabIndex = 2;
			   //
			   // lblTotal
			   //
			   this->lblTotal->AutoSize = true;
			   this->lblTotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			   this->lblTotal->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->lblTotal->Location = System::Drawing::Point(18, 35);
			   this->lblTotal->Name = L"lblTotal";
			   this->lblTotal->Size = System::Drawing::Size(144, 25);
			   this->lblTotal->TabIndex = 0;
			   this->lblTotal->Text = L"Total: 0.00 EGP";
			   //
			   // btnClear
			   //
			   this->btnClear->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnClear->AccessibleName = L"Clear Cart";
			   this->btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnClear->AutoSizeBasedOnText = false;
			   this->btnClear->BackColor = System::Drawing::Color::Transparent;
			   this->btnClear->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnClear->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnClear->BadgeValue = 0;
			   this->btnClear->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnClear->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnClear->BorderWidth = 1;
			   this->btnClear->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnClear->ButtonImage = nullptr;
			   this->btnClear->ButtonTextLeftPadding = 0;
			   this->btnClear->CanBeep = true;
			   this->btnClear->CanGlow = false;
			   this->btnClear->CanShake = true;
			   this->btnClear->ContextMenuStripEx = nullptr;
			   this->btnClear->CornerRadiusBottomLeft = 6;
			   this->btnClear->CornerRadiusBottomRight = 6;
			   this->btnClear->CornerRadiusTopLeft = 6;
			   this->btnClear->CornerRadiusTopRight = 6;
			   this->btnClear->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnClear->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnClear->EnableLongPress = false;
			   this->btnClear->EnableRippleEffect = true;
			   this->btnClear->EnableShadow = false;
			   this->btnClear->EnableTextWrapping = false;
			   this->btnClear->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnClear->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnClear->GlowIntensity = 100;
			   this->btnClear->GlowRadius = 20;
			   this->btnClear->GradientBackground = false;
			   this->btnClear->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnClear->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnClear->HintText = nullptr;
			   this->btnClear->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnClear->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClear->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClear->HoverTransitionDuration = 250;
			   this->btnClear->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnClear->ImagePadding = 5;
			   this->btnClear->ImageSize = System::Drawing::Size(16, 16);
			   this->btnClear->IsRadial = false;
			   this->btnClear->IsReadOnly = false;
			   this->btnClear->IsToggleButton = false;
			   this->btnClear->IsToggled = false;
			   this->btnClear->Location = System::Drawing::Point(606, 31);
			   this->btnClear->LongPressDurationMS = 1000;
			   this->btnClear->Name = L"btnClear";
			   this->btnClear->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClear->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnClear->ParticleCount = 15;
			   this->btnClear->PressAnimationScale = 0.97F;
			   this->btnClear->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnClear->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClear->PressTransitionDuration = 150;
			   this->btnClear->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnClear->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClear->RippleRadiusMultiplier = 0.6F;
			   this->btnClear->ShadowBlur = 5;
			   this->btnClear->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClear->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnClear->ShakeDuration = 500;
			   this->btnClear->ShakeIntensity = 5;
			   this->btnClear->Size = System::Drawing::Size(110, 40);
			   this->btnClear->TabIndex = 2;
			   this->btnClear->Text = L"Clear Cart";
			   this->btnClear->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnClear->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClear->TooltipText = nullptr;
			   this->btnClear->UseAdvancedRendering = true;
			   this->btnClear->UseParticles = false;
			   this->btnClear->Click += gcnew System::EventHandler(this, &RequestCartForm::btnClear_Click);
			   //
			   // btnProceed
			   //
			   this->btnProceed->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnProceed->AccessibleName = L"Proceed to Submit";
			   this->btnProceed->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnProceed->AutoSizeBasedOnText = false;
			   this->btnProceed->BackColor = System::Drawing::Color::Transparent;
			   this->btnProceed->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnProceed->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnProceed->BadgeValue = 0;
			   this->btnProceed->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnProceed->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnProceed->BorderWidth = 1;
			   this->btnProceed->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnProceed->ButtonImage = nullptr;
			   this->btnProceed->ButtonTextLeftPadding = 0;
			   this->btnProceed->CanBeep = true;
			   this->btnProceed->CanGlow = false;
			   this->btnProceed->CanShake = true;
			   this->btnProceed->ContextMenuStripEx = nullptr;
			   this->btnProceed->CornerRadiusBottomLeft = 6;
			   this->btnProceed->CornerRadiusBottomRight = 6;
			   this->btnProceed->CornerRadiusTopLeft = 6;
			   this->btnProceed->CornerRadiusTopRight = 6;
			   this->btnProceed->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnProceed->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnProceed->EnableLongPress = false;
			   this->btnProceed->EnableRippleEffect = true;
			   this->btnProceed->EnableShadow = false;
			   this->btnProceed->EnableTextWrapping = false;
			   this->btnProceed->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnProceed->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnProceed->GlowIntensity = 100;
			   this->btnProceed->GlowRadius = 20;
			   this->btnProceed->GradientBackground = false;
			   this->btnProceed->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnProceed->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnProceed->HintText = nullptr;
			   this->btnProceed->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnProceed->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProceed->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnProceed->HoverTransitionDuration = 250;
			   this->btnProceed->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnProceed->ImagePadding = 5;
			   this->btnProceed->ImageSize = System::Drawing::Size(16, 16);
			   this->btnProceed->IsRadial = false;
			   this->btnProceed->IsReadOnly = false;
			   this->btnProceed->IsToggleButton = false;
			   this->btnProceed->IsToggled = false;
			   this->btnProceed->Location = System::Drawing::Point(726, 31);
			   this->btnProceed->LongPressDurationMS = 1000;
			   this->btnProceed->Name = L"btnProceed";
			   this->btnProceed->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProceed->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnProceed->ParticleCount = 15;
			   this->btnProceed->PressAnimationScale = 0.97F;
			   this->btnProceed->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnProceed->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProceed->PressTransitionDuration = 150;
			   this->btnProceed->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnProceed->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnProceed->RippleRadiusMultiplier = 0.6F;
			   this->btnProceed->ShadowBlur = 5;
			   this->btnProceed->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnProceed->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnProceed->ShakeDuration = 500;
			   this->btnProceed->ShakeIntensity = 5;
			   this->btnProceed->Size = System::Drawing::Size(160, 40);
			   this->btnProceed->TabIndex = 3;
			   this->btnProceed->Text = L"Proceed to Submit";
			   this->btnProceed->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnProceed->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnProceed->TooltipText = nullptr;
			   this->btnProceed->UseAdvancedRendering = true;
			   this->btnProceed->UseParticles = false;
			   this->btnProceed->Click += gcnew System::EventHandler(this, &RequestCartForm::btnProceed_Click);
			   //
			   // siticonePanel1
			   //
			   this->siticonePanel1->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel1->BackColor = System::Drawing::Color::Transparent;
			   this->siticonePanel1->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			   this->siticonePanel1->BorderDashPattern = nullptr;
			   this->siticonePanel1->BorderGradientEndColor = System::Drawing::Color::Gray;
			   this->siticonePanel1->BorderGradientStartColor = System::Drawing::Color::Gray;
			   this->siticonePanel1->BorderThickness = 2;
			   this->siticonePanel1->Controls->Add(this->panelGrid);
			   this->siticonePanel1->Controls->Add(this->panelFooter);
			   this->siticonePanel1->CornerRadiusBottomLeft = 5;
			   this->siticonePanel1->CornerRadiusBottomRight = 5;
			   this->siticonePanel1->CornerRadiusTopLeft = 5;
			   this->siticonePanel1->CornerRadiusTopRight = 5;
			   this->siticonePanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->siticonePanel1->EnableAcrylicEffect = false;
			   this->siticonePanel1->EnableMicaEffect = false;
			   this->siticonePanel1->EnableRippleEffect = false;
			   this->siticonePanel1->FillColor = System::Drawing::Color::White;
			   this->siticonePanel1->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				   System::Drawing::Color::White, System::Drawing::Color::LightGray,
					   System::Drawing::Color::Gray
			   };
			   this->siticonePanel1->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			   this->siticonePanel1->Location = System::Drawing::Point(0, 72);
			   this->siticonePanel1->Name = L"siticonePanel1";
			   this->siticonePanel1->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			   this->siticonePanel1->RippleAlpha = 50;
			   this->siticonePanel1->RippleAlphaDecrement = 3;
			   this->siticonePanel1->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel1->RippleMaxSize = 600;
			   this->siticonePanel1->RippleSpeed = 15;
			   this->siticonePanel1->ShowBorder = true;
			   this->siticonePanel1->Size = System::Drawing::Size(916, 471);
			   this->siticonePanel1->TabIndex = 1;
			   this->siticonePanel1->TabStop = true;
			   this->siticonePanel1->TrackSystemTheme = false;
			   this->siticonePanel1->UseBorderGradient = true;
			   this->siticonePanel1->UseMultiGradient = false;
			   this->siticonePanel1->UsePatternTexture = false;
			   this->siticonePanel1->UseRadialGradient = false;
			   //
			   // RequestCartForm
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->ClientSize = System::Drawing::Size(916, 543);
			   this->Controls->Add(this->siticonePanel1);
			   this->Controls->Add(this->panelHeader);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"RequestCartForm";
			   this->Text = L"Request Cart";
			   this->panelHeader->ResumeLayout(false);
			   this->panelHeader->PerformLayout();
			   this->panelGrid->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->EndInit();
			   this->panelFooter->ResumeLayout(false);
			   this->panelFooter->PerformLayout();
			   this->siticonePanel1->ResumeLayout(false);
			   this->ResumeLayout(false);
		   }
#pragma endregion
	};
}