#pragma once

#include "HomeForm.h"
#include "UiStyler.h"
#include "ProductCardControl.h"
#include "DatabaseManager.h"
#include "CartManager.h"
#include "ProductManager.h"
#include "Session.h"
#include "CartManager.h"      // required for server-backed cart functions (if present)

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for HomeForm
	/// </summary>
	public ref class HomeForm : public System::Windows::Forms::Form
	{
	public:
		HomeForm(void)
		{
			InitializeComponent();

			_allProducts = gcnew List<ProductRow^>();

			// Load from DB
			LoadProductsFromDb();
			InitializeFilters();

			// Apply shared styling
			UiStyler::StyleFlowPanel(flowProducts);
			UiStyler::StyleTextBox(txtSearch);
			UiStyler::StylePrimaryButton(btnSearch);

			// Live filter on user input
			this->txtSearch->TextChanged += gcnew System::EventHandler(
				this, &HomeForm::txtSearch_TextChanged);

			this->cmbCategory->SelectedIndexChanged += gcnew System::EventHandler(
				this, &HomeForm::cmbCategory_SelectedIndexChanged);

			// Enter key triggers filter
			this->KeyPreview = true;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(
				this, &HomeForm::HomeForm_KeyDown);
		}

	protected:
		~HomeForm()
		{
			if (components)
				delete components;
		}

	private:
		System::ComponentModel::Container^ components;

		// UI
		System::Windows::Forms::Label^ lblTitle;
		SiticoneNetFrameworkUI::SiticoneTextBox^ txtSearch;
		SiticoneNetFrameworkUI::SiticoneButton^ btnSearch;
		System::Windows::Forms::ComboBox^ cmbCategory;
		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
		SiticoneNetFrameworkUI::SiticoneFlowPanel^ flowProducts;
		System::Windows::Forms::Label^ lblStatus;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;

		   // Data structure representing a product row
		   ref struct ProductRow
		   {
			   int Id;
			   System::String^ Name;
			   System::String^ Category;
			   System::Decimal Price;            // use System::Decimal to match DB Decimal
			   System::String^ ImagePath;
			   System::String^ StockText;
		   };

		   List<ProductRow^>^ _allProducts;

#pragma region Helpers

		   void InitializeFilters()
		   {
			   // Build distinct category list
			   System::Collections::Generic::HashSet<String^>^ cats =
				   gcnew System::Collections::Generic::HashSet<String^>();

			   for each (ProductRow ^ p in _allProducts)
			   {
				   if (!System::String::IsNullOrWhiteSpace(p->Category))
					   cats->Add(p->Category);
			   }

			   cmbCategory->Items->Clear();
			   cmbCategory->Items->Add(L"All");

			   for each (String ^ cat in cats)
				   cmbCategory->Items->Add(cat);

			   if (cmbCategory->Items->Count > 0)
				   cmbCategory->SelectedIndex = 0; // All
		   }

		   void UpdateStatusLabel(int visibleCount)
		   {
			   int total = _allProducts != nullptr ? _allProducts->Count : 0;

			   lblStatus->Text = String::Format(
				   L"Showing {0} of {1} products",
				   visibleCount, total);
		   }

		   void ApplyFilters()
		   {
			   String^ search = txtSearch->Text->Trim()->ToLower();
			   String^ selectedCategory = nullptr;

			   if (cmbCategory->SelectedIndex > 0) // index 0 = "All"
				   selectedCategory = cmbCategory->SelectedItem->ToString();

			   List<ProductRow^>^ filtered = gcnew List<ProductRow^>();

			   for each (ProductRow ^ p in _allProducts)
			   {
				   bool matchCategory = (selectedCategory == nullptr ||
					   p->Category == selectedCategory);

				   bool matchSearch = (search->Length == 0 ||
					   p->Name->ToLower()->Contains(search));

				   if (matchCategory && matchSearch)
					   filtered->Add(p);
			   }

			   PopulateProductCards(filtered);
			   UpdateStatusLabel(filtered->Count);
		   }

	private:
		void PopulateProductCards(List<ProductRow^>^ products)
		{
			if (products == nullptr)
			{
				flowProducts->Controls->Clear();
				return;
			}

			flowProducts->SuspendLayout();
			flowProducts->Controls->Clear();

			for each (ProductRow ^ p in products)
			{
				ProductCardControl^ card = gcnew ProductCardControl();

				// sizes chosen to fit your panelCard (adjust if you want)
				card->Width = 260;    // wider card to fit image-left / text-right style
				card->Height = 150;
				card->Margin = System::Windows::Forms::Padding(8);
				card->BackColor = Color::Transparent;

				// call SetData - signature expected: (int id, string name, category, price, stockText, imagePath)
				card->SetData(
					p->Id,
					p->Name,
					p->Category,
					Convert::ToDouble(p->Price),
					p->StockText,
					p->ImagePath
				);

				// Subscribe to AddToCart — use safe + correct event syntax
				card->AddToCartClicked += gcnew System::EventHandler(this, &HomeForm::OnProductCardAddClicked);

				flowProducts->Controls->Add(card);
			}

			flowProducts->ResumeLayout();
		}

	private:
		// Lightweight local fallback cart if the real CartManager::AddToCart isn't available
		// Keeps the UI interactive even when CartManager calls fail for any reason.
		static System::Collections::Generic::Dictionary<int, int>^ _localCart = nullptr;

	private: System::Void OnProductCardAddClicked(System::Object^ sender, System::EventArgs^ e)
	{
		// defensive casting
		ProductCardControl^ card = nullptr;
		try {
			card = dynamic_cast<ProductCardControl^>(sender);
		}
		catch (...) {
			card = nullptr;
		}

		if (card == nullptr)
		{
			MessageBox::Show(L"Unable to determine product. Try again.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		int productId = card->ProductId;
		if (productId <= 0)
		{
			MessageBox::Show(L"Invalid product id.", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		// default quantity (you can later expose quantity selection in the card)
		int quantity = 1;
		String^ productName = card->ProductName;
		Decimal unitPrice = card->UnitPrice;

		// Try calling the project's CartManager Add method (most likely signature)
		bool added = false;
		String^ err = nullptr;

		try
		{
			// Most projects implement: CartManager::AddToCart(int userId, int productId, int qty, String% error)
			// We'll attempt that common signature first:
			int userId = Session::UserId; // make sure Session is included at top of HomeForm.h

			// Defensive: check for valid logged in user
			if (userId <= 0)
			{
				// fallback: store locally
				goto LOCAL_FALLBACK;
			}

			try
			{
				// This call will succeed if CartManager implements AddToCart as assumed
				CartManager::AddItem(userId, productId, productName, unitPrice, quantity);
				if (String::IsNullOrEmpty(err))
					added = true;
			}
			catch (System::Exception^ exAdd)
			{
				// If the signature differs or throws, we fall back
				err = exAdd->Message;
			}
		}
		catch (...) { /* ignore and fallback below */ }

	LOCAL_FALLBACK:
		if (!added)
		{
			// Initialize local cart dictionary if needed
			if (_localCart == nullptr)
				_localCart = gcnew System::Collections::Generic::Dictionary<int, int>();

			int prevQty = 0;
			if (_localCart->ContainsKey(productId))
			{
				prevQty = _localCart[productId];
				_localCart[productId] = prevQty + quantity;
			}
			else
			{
				_localCart->Add(productId, quantity);
			}

			added = true;
		}

		// Update cart UI if a label exists (lblCartCount) — optional but convenient
		try
		{
			if (this->Controls->ContainsKey(L"lblCartCount"))
			{
				System::Windows::Forms::Label^ lbl = safe_cast<System::Windows::Forms::Label^>(this->Controls[L"lblCartCount"]);
				int totalItems = 0;
				// Prefer real cart count if CartManager::GetCart exists
				try
				{
					List<CartItem^>^ cart = nullptr;
					try { cart = CartManager::GetCart(Session::UserId); }
					catch (...) { cart = nullptr; }
					if (cart != nullptr)
					{
						for each (CartItem ^ it in cart) totalItems += it->Quantity;
					}
					else if (_localCart != nullptr)
					{
						for each (int q in _localCart->Values) totalItems += q;
					}
				}
				catch (...)
				{
					// fallback to local
					if (_localCart != nullptr)
					{
						for each (int q in _localCart->Values) totalItems += q;
					}
				}

				lbl->Text = totalItems.ToString();
			}
		}
		catch (...) { /* ignore UI update errors */ }

		// Friendly confirmation
		if (added)
		{
			MessageBox::Show(String::Format(L"Added to cart: {0}", card->ProductName), L"Cart", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			String^ msg = L"Failed to add to cart.";
			if (!String::IsNullOrEmpty(err)) msg += L" Details: " + err;
			MessageBox::Show(msg, L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private:
		void LoadCategories()
		{
			try
			{
				System::Collections::Generic::HashSet<String^>^ cats =
					gcnew System::Collections::Generic::HashSet<String^>();

				for each (ProductRow ^ p in _allProducts)
				{
					if (!System::String::IsNullOrWhiteSpace(p->Category))
						cats->Add(p->Category);
				}

				cmbCategory->Items->Clear();
				cmbCategory->Items->Add(L"All");

				for each (String ^ cat in cats)
					cmbCategory->Items->Add(cat);

				if (cmbCategory->Items->Count > 0)
					cmbCategory->SelectedIndex = 0;
			}
			catch (Exception^)
			{
				// ignore silently — keep previous categories if any
			}
		}

		// Load products from DB using ProductManager and populate _allProducts
		void LoadProductsFromDb()
		{
			_allProducts = gcnew List<ProductRow^>();

			try
			{
				String^ err = nullptr;
				List<Product^>^ products = ProductManager::GetAll(err);
				if (products == nullptr)
				{
					if (!String::IsNullOrEmpty(err))
						lblStatus->Text = L"Products load error: " + err;
					else
						lblStatus->Text = L"No products found.";
					return;
				}

				for each (Product ^ p in products)
				{
					ProductRow^ row = gcnew ProductRow();
					row->Id = p->Id;
					row->Name = p->Name;
					row->Category = p->Category;
					// Product.Price is System::Decimal in Product class — safe assign
					row->Price = safe_cast<System::Decimal>(Convert::ToDecimal(p->Price));
					row->ImagePath = p->ImagePath;
					// Stock text friendly
					row->StockText = (p->Stock > 0) ? L"In stock" : L"Out of stock";
					_allProducts->Add(row);
				}

				// Populate category combo and display
				LoadCategories();
				ApplyFilters(); // initial display
			}
			catch (Exception^ ex)
			{
				lblStatus->Text = L"Error loading products: " + ex->Message;
			}
		}

#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->txtSearch = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->btnSearch = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->cmbCategory = (gcnew System::Windows::Forms::ComboBox());
			this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			this->flowProducts = (gcnew SiticoneNetFrameworkUI::SiticoneFlowPanel());
			this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->panelHeader->SuspendLayout();
			this->siticonePanel1->SuspendLayout();
			this->SuspendLayout();
			//
			// lblTitle
			//
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblTitle->Location = System::Drawing::Point(15, 18);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(92, 25);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Products";
			//
			// txtSearch
			//
			this->txtSearch->AccessibleDescription = L"A customizable text input field.";
			this->txtSearch->AccessibleName = L"Text Box";
			this->txtSearch->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtSearch->BackColor = System::Drawing::Color::Transparent;
			this->txtSearch->BlinkCount = 3;
			this->txtSearch->BlinkShadow = false;
			this->txtSearch->BorderColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->txtSearch->BorderColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->txtSearch->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->txtSearch->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->txtSearch->CanShake = true;
			this->txtSearch->ContinuousBlink = false;
			this->txtSearch->CornerRadiusBottomLeft = 6;
			this->txtSearch->CornerRadiusBottomRight = 6;
			this->txtSearch->CornerRadiusTopLeft = 6;
			this->txtSearch->CornerRadiusTopRight = 6;
			this->txtSearch->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtSearch->CursorBlinkRate = 500;
			this->txtSearch->CursorColor = System::Drawing::Color::Black;
			this->txtSearch->CursorHeight = 26;
			this->txtSearch->CursorOffset = 0;
			this->txtSearch->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtSearch->CursorWidth = 1;
			this->txtSearch->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtSearch->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtSearch->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtSearch->EnableDropShadow = false;
			this->txtSearch->FillColor1 = System::Drawing::Color::White;
			this->txtSearch->FillColor2 = System::Drawing::Color::White;
			this->txtSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.5F));
			this->txtSearch->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->txtSearch->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtSearch->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtSearch->IsEnabled = true;
			this->txtSearch->Location = System::Drawing::Point(180, 18);
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->txtSearch->PlaceholderText = L"Search products by name…";
			this->txtSearch->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtSearch->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtSearch->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtSearch->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtSearch->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtSearch->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtSearch->ShadowAnimationDuration = 1;
			this->txtSearch->ShadowBlur = 10;
			this->txtSearch->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtSearch->Size = System::Drawing::Size(260, 26);
			this->txtSearch->SolidBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->txtSearch->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->txtSearch->SolidBorderHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->txtSearch->SolidFillColor = System::Drawing::Color::White;
			this->txtSearch->TabIndex = 1;
			this->txtSearch->TextPadding = System::Windows::Forms::Padding(12, 0, 6, 0);
			this->txtSearch->ValidationErrorMessage = L"Invalid input.";
			this->txtSearch->ValidationFunction = nullptr;
			//
			// btnSearch
			//
			this->btnSearch->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnSearch->AccessibleName = L"Search";
			this->btnSearch->AutoSizeBasedOnText = false;
			this->btnSearch->BackColor = System::Drawing::Color::Transparent;
			this->btnSearch->BadgeBackColor = System::Drawing::Color::Black;
			this->btnSearch->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnSearch->BadgeValue = 0;
			this->btnSearch->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnSearch->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnSearch->BorderWidth = 1;
			this->btnSearch->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnSearch->ButtonImage = nullptr;
			this->btnSearch->ButtonTextLeftPadding = 0;
			this->btnSearch->CanBeep = true;
			this->btnSearch->CanGlow = false;
			this->btnSearch->CanShake = true;
			this->btnSearch->ContextMenuStripEx = nullptr;
			this->btnSearch->CornerRadiusBottomLeft = 6;
			this->btnSearch->CornerRadiusBottomRight = 6;
			this->btnSearch->CornerRadiusTopLeft = 6;
			this->btnSearch->CornerRadiusTopRight = 6;
			this->btnSearch->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnSearch->CustomCursor = System::Windows::Forms::Cursors::Default;
			this->btnSearch->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnSearch->EnableLongPress = false;
			this->btnSearch->EnableRippleEffect = true;
			this->btnSearch->EnableShadow = false;
			this->btnSearch->EnableTextWrapping = false;
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.5F));
			this->btnSearch->ForeColor = System::Drawing::Color::White;
			this->btnSearch->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnSearch->GlowIntensity = 100;
			this->btnSearch->GlowRadius = 20;
			this->btnSearch->GradientBackground = false;
			this->btnSearch->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnSearch->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnSearch->HintText = nullptr;
			this->btnSearch->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnSearch->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSearch->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSearch->HoverTransitionDuration = 250;
			this->btnSearch->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnSearch->ImagePadding = 5;
			this->btnSearch->ImageSize = System::Drawing::Size(16, 16);
			this->btnSearch->IsRadial = false;
			this->btnSearch->IsReadOnly = false;
			this->btnSearch->IsToggleButton = false;
			this->btnSearch->IsToggled = false;
			this->btnSearch->Location = System::Drawing::Point(450, 17);
			this->btnSearch->LongPressDurationMS = 1000;
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSearch->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnSearch->ParticleCount = 15;
			this->btnSearch->PressAnimationScale = 0.97F;
			this->btnSearch->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnSearch->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSearch->PressTransitionDuration = 150;
			this->btnSearch->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnSearch->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSearch->RippleRadiusMultiplier = 0.6F;
			this->btnSearch->ShadowBlur = 5;
			this->btnSearch->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSearch->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnSearch->ShakeDuration = 500;
			this->btnSearch->ShakeIntensity = 5;
			this->btnSearch->Size = System::Drawing::Size(80, 28);
			this->btnSearch->TabIndex = 2;
			this->btnSearch->Text = L"Search";
			this->btnSearch->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSearch->TextColor = System::Drawing::Color::White;
			this->btnSearch->TooltipText = nullptr;
			this->btnSearch->UseAdvancedRendering = true;
			this->btnSearch->UseParticles = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &HomeForm::btnSearch_Click);
			//
			// lblStatus
			//
			this->lblStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(130)), static_cast<System::Int32>(static_cast<System::Byte>(130)),
				static_cast<System::Int32>(static_cast<System::Byte>(130)));
			this->lblStatus->Location = System::Drawing::Point(16, 513);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(0, 15);
			this->lblStatus->TabIndex = 6;
			//
			// cmbCategory
			//
			this->cmbCategory->BackColor = System::Drawing::Color::White;
			this->cmbCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbCategory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->cmbCategory->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cmbCategory->FormattingEnabled = true;
			this->cmbCategory->Location = System::Drawing::Point(550, 18);
			this->cmbCategory->Name = L"cmbCategory";
			this->cmbCategory->Size = System::Drawing::Size(160, 25);
			this->cmbCategory->TabIndex = 3;
			//
			// panelHeader
			//
			this->panelHeader->BackColor = System::Drawing::Color::White;
			this->panelHeader->Controls->Add(this->lblTitle);
			this->panelHeader->Controls->Add(this->cmbCategory);
			this->panelHeader->Controls->Add(this->btnSearch);
			this->panelHeader->Controls->Add(this->txtSearch);
			this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelHeader->Location = System::Drawing::Point(0, 0);
			this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			this->panelHeader->Name = L"panelHeader";
			this->panelHeader->Size = System::Drawing::Size(916, 60);
			this->panelHeader->TabIndex = 4;
			//
			// flowProducts
			//
			this->flowProducts->AutoScroll = true;
			this->flowProducts->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->flowProducts->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowProducts->EnableAnimations = true;
			this->flowProducts->EnableAutoScale = true;
			this->flowProducts->EnableDragDrop = false;
			this->flowProducts->EnableLayoutCaching = true;
			this->flowProducts->EnableSmoothScrolling = true;
			this->flowProducts->EnableSnapToGrid = false;
			this->flowProducts->EnableTransparency = false;
			this->flowProducts->EnableVirtualization = false;
			this->flowProducts->EnableWrapping = true;
			this->flowProducts->GridSize = 8;
			this->flowProducts->IsTrackingTheme = false;
			this->flowProducts->ItemSpacing = 5;
			this->flowProducts->Location = System::Drawing::Point(2, 2);
			this->flowProducts->Name = L"flowProducts";
			this->flowProducts->Padding = System::Windows::Forms::Padding(16);
			this->flowProducts->Size = System::Drawing::Size(911, 479);
			this->flowProducts->TabIndex = 5;
			this->flowProducts->VirtualizationThreshold = 100;
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
			this->siticonePanel1->Controls->Add(this->flowProducts);
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
			this->siticonePanel1->Location = System::Drawing::Point(0, 60);
			this->siticonePanel1->Name = L"siticonePanel1";
			this->siticonePanel1->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->siticonePanel1->RippleAlpha = 50;
			this->siticonePanel1->RippleAlphaDecrement = 3;
			this->siticonePanel1->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->siticonePanel1->RippleMaxSize = 600;
			this->siticonePanel1->RippleSpeed = 15;
			this->siticonePanel1->ShowBorder = true;
			this->siticonePanel1->Size = System::Drawing::Size(916, 483);
			this->siticonePanel1->TabIndex = 0;
			this->siticonePanel1->TabStop = true;
			this->siticonePanel1->TrackSystemTheme = false;
			this->siticonePanel1->UseBorderGradient = true;
			this->siticonePanel1->UseMultiGradient = false;
			this->siticonePanel1->UsePatternTexture = false;
			this->siticonePanel1->UseRadialGradient = false;
			//
			// HomeForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(916, 543);
			this->Controls->Add(this->siticonePanel1);
			this->Controls->Add(this->panelHeader);
			this->Controls->Add(this->lblStatus);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"HomeForm";
			this->Text = L"Products – EPRMS";
			this->Load += gcnew System::EventHandler(this, &HomeForm::HomeForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &HomeForm::HomeForm_KeyDown);
			this->panelHeader->ResumeLayout(false);
			this->panelHeader->PerformLayout();
			this->siticonePanel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private:
		System::Void HomeForm_Load(System::Object^ sender, System::EventArgs^ e) {
			// Already loaded in constructor – nothing extra for now.
		}

		System::Void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			ApplyFilters();
		}

		System::Void cmbCategory_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			ApplyFilters();
		}

		System::Void HomeForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			if (e->KeyCode == System::Windows::Forms::Keys::Enter)
			{
				ApplyFilters();
				e->Handled = true;
			}
		}
		System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
		{
			ApplyFilters();
		}
	};
}
