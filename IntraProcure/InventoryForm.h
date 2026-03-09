#pragma once

#include "UiStyler.h"
#include "Session.h"
#include "DatabaseManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace IntraProcure {
	/// <summary>
	/// InventoryForm - products / stock management
	/// </summary>
	public ref class InventoryForm : public System::Windows::Forms::Form
	{
	public:
		InventoryForm(void)
		{
			InitializeComponent();

			// Apply styling helpers
			UiStyler::StyleTextBox(txtSearch);
			UiStyler::StyleButton(btnRefresh);
			UiStyler::StylePrimaryButton(btnAdd);
			UiStyler::StyleSecondaryButton(btnEdit);
			UiStyler::StyleDangerButton(btnDelete);

			UiStyler::StyleGrid(gridInventory);
			AddGridColumns();

			InitializeInventory(); // sample data
			ApplyFilters();

			// Only Admins can manage users & suppliers
			if (Session::IsAdministrator) {
				btnAdd->Enabled = true;
				btnDelete->Enabled = true;
				btnEdit->Enabled = true;
				lblStatus->Text = "";
				lblStatus->Visible = false;
			}
			else {
				btnAdd->Enabled = false;
				btnDelete->Enabled = false;
				btnEdit->Enabled = false;
				lblStatus->Text = "Only Admins Can Edit Inventory Products.";
				lblStatus->Visible = true;
			}
		}

	protected:
		~InventoryForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		// Header
		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
		System::Windows::Forms::Label^ lblTitle;
		SiticoneNetFrameworkUI::SiticoneTextBox^ txtSearch;
		System::Windows::Forms::ComboBox^ cmbCategory;
		SiticoneNetFrameworkUI::SiticoneButton^ btnRefresh;

		// Card + main layout
		SiticoneNetFrameworkUI::SiticoneAdvancedPanel^ panelCard;
		System::Windows::Forms::SplitContainer^ splitMain;

		// Left: grid inventory
		System::Windows::Forms::DataGridView^ gridInventory;

		// Right: details / editor
		System::Windows::Forms::Panel^ detailsPanel;
		System::Windows::Forms::Label^ lblDetailsTitle;
		System::Windows::Forms::PictureBox^ picProduct;
		System::Windows::Forms::Label^ lblName;

		System::Windows::Forms::Label^ lblCategory;

		System::Windows::Forms::Label^ lblPrice;

		System::Windows::Forms::Label^ lblStock;

		System::Windows::Forms::Label^ lblSKU;

		// buttons
		SiticoneNetFrameworkUI::SiticoneButton^ btnAdd;
		SiticoneNetFrameworkUI::SiticoneButton^ btnEdit;
		SiticoneNetFrameworkUI::SiticoneButton^ btnDelete;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtSKU;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtStock;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtPrice;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtCategory;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtName;
	private: System::Windows::Forms::Label^ lblStatus;

		   // runtime model – one row in grid = one Inventory row joined with Products
		   ref struct ProductRow
		   {
			   int Id;             // Inventory.Id
			   int ProductId;      // Inventory.ProductId
			   String^ SKU;        // mapped to Location (for UI compatibility)
			   String^ Location;   // same as SKU, but clearer name for logic
			   String^ Name;       // Products.Name
			   String^ Category;   // Products.Category
			   double Price;       // Products.Price
			   int Stock;          // Inventory.Quantity
			   String^ ImagePath;  // optional from Products.ImagePath (if you add it later)
			   String^ Notes;
		   };

		   List<ProductRow^>^ _allProducts;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InventoryForm::typeid));
			   this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->txtSearch = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			   this->cmbCategory = (gcnew System::Windows::Forms::ComboBox());
			   this->btnRefresh = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelCard = (gcnew SiticoneNetFrameworkUI::SiticoneAdvancedPanel());
			   this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			   this->gridInventory = (gcnew System::Windows::Forms::DataGridView());
			   this->detailsPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblStatus = (gcnew System::Windows::Forms::Label());
			   this->txtPrice = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->txtStock = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblDetailsTitle = (gcnew System::Windows::Forms::Label());
			   this->picProduct = (gcnew System::Windows::Forms::PictureBox());
			   this->txtCategory = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblSKU = (gcnew System::Windows::Forms::Label());
			   this->txtName = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblName = (gcnew System::Windows::Forms::Label());
			   this->txtSKU = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblCategory = (gcnew System::Windows::Forms::Label());
			   this->lblPrice = (gcnew System::Windows::Forms::Label());
			   this->lblStock = (gcnew System::Windows::Forms::Label());
			   this->btnAdd = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnEdit = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnDelete = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelHeader->SuspendLayout();
			   this->panelCard->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->BeginInit();
			   this->splitMain->Panel1->SuspendLayout();
			   this->splitMain->Panel2->SuspendLayout();
			   this->splitMain->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridInventory))->BeginInit();
			   this->detailsPanel->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picProduct))->BeginInit();
			   this->SuspendLayout();
			   //
			   // panelHeader
			   //
			   this->panelHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelHeader->Controls->Add(this->lblTitle);
			   this->panelHeader->Controls->Add(this->txtSearch);
			   this->panelHeader->Controls->Add(this->cmbCategory);
			   this->panelHeader->Controls->Add(this->btnRefresh);
			   this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			   this->panelHeader->Location = System::Drawing::Point(0, 0);
			   this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelHeader->Name = L"panelHeader";
			   this->panelHeader->Padding = System::Windows::Forms::Padding(12);
			   this->panelHeader->Size = System::Drawing::Size(916, 72);
			   this->panelHeader->TabIndex = 1;
			   //
			   // lblTitle
			   //
			   this->lblTitle->AutoSize = true;
			   this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			   this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->lblTitle->Location = System::Drawing::Point(12, 18);
			   this->lblTitle->Name = L"lblTitle";
			   this->lblTitle->Size = System::Drawing::Size(100, 25);
			   this->lblTitle->TabIndex = 0;
			   this->lblTitle->Text = L"Inventory";
			   //
			   // txtSearch
			   //
			   this->txtSearch->AccessibleDescription = L"A customizable text input field.";
			   this->txtSearch->AccessibleName = L"Text Box";
			   this->txtSearch->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			   this->txtSearch->BackColor = System::Drawing::Color::Transparent;
			   this->txtSearch->BlinkCount = 3;
			   this->txtSearch->BlinkShadow = false;
			   this->txtSearch->BorderColor1 = System::Drawing::Color::LightSlateGray;
			   this->txtSearch->BorderColor2 = System::Drawing::Color::LightSlateGray;
			   this->txtSearch->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtSearch->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
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
			   this->txtSearch->ForeColor = System::Drawing::Color::DimGray;
			   this->txtSearch->HoverBorderColor1 = System::Drawing::Color::Gray;
			   this->txtSearch->HoverBorderColor2 = System::Drawing::Color::Gray;
			   this->txtSearch->IsEnabled = true;
			   this->txtSearch->Location = System::Drawing::Point(180, 18);
			   this->txtSearch->Name = L"txtSearch";
			   this->txtSearch->PlaceholderColor = System::Drawing::Color::Gray;
			   this->txtSearch->PlaceholderText = L"Search by name, SKU or category...";
			   this->txtSearch->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			   this->txtSearch->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			   this->txtSearch->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			   this->txtSearch->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			   this->txtSearch->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			   this->txtSearch->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtSearch->ShadowAnimationDuration = 1;
			   this->txtSearch->ShadowBlur = 10;
			   this->txtSearch->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->txtSearch->Size = System::Drawing::Size(320, 32);
			   this->txtSearch->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			   this->txtSearch->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtSearch->SolidBorderHoverColor = System::Drawing::Color::Gray;
			   this->txtSearch->SolidFillColor = System::Drawing::Color::White;
			   this->txtSearch->TabIndex = 0;
			   this->txtSearch->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			   this->txtSearch->ValidationErrorMessage = L"Invalid input.";
			   this->txtSearch->ValidationFunction = nullptr;
			   this->txtSearch->TextChanged += gcnew System::EventHandler(this, &InventoryForm::txtSearch_TextChanged);
			   //
			   // cmbCategory
			   //
			   this->cmbCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->cmbCategory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->cmbCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->cmbCategory->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"All", L"Displays" });
			   this->cmbCategory->Location = System::Drawing::Point(512, 18);
			   this->cmbCategory->Name = L"cmbCategory";
			   this->cmbCategory->Size = System::Drawing::Size(160, 23);
			   this->cmbCategory->TabIndex = 1;
			   this->cmbCategory->SelectedIndexChanged += gcnew System::EventHandler(this, &InventoryForm::cmbCategory_SelectedIndexChanged);
			   //
			   // btnRefresh
			   //
			   this->btnRefresh->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnRefresh->AccessibleName = L"Refresh";
			   this->btnRefresh->AutoSizeBasedOnText = false;
			   this->btnRefresh->BackColor = System::Drawing::Color::Transparent;
			   this->btnRefresh->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnRefresh->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnRefresh->BadgeValue = 0;
			   this->btnRefresh->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnRefresh->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnRefresh->BorderWidth = 1;
			   this->btnRefresh->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnRefresh->ButtonImage = nullptr;
			   this->btnRefresh->ButtonTextLeftPadding = 0;
			   this->btnRefresh->CanBeep = true;
			   this->btnRefresh->CanGlow = false;
			   this->btnRefresh->CanShake = true;
			   this->btnRefresh->ContextMenuStripEx = nullptr;
			   this->btnRefresh->CornerRadiusBottomLeft = 6;
			   this->btnRefresh->CornerRadiusBottomRight = 6;
			   this->btnRefresh->CornerRadiusTopLeft = 6;
			   this->btnRefresh->CornerRadiusTopRight = 6;
			   this->btnRefresh->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnRefresh->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnRefresh->EnableLongPress = false;
			   this->btnRefresh->EnableRippleEffect = true;
			   this->btnRefresh->EnableShadow = false;
			   this->btnRefresh->EnableTextWrapping = false;
			   this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnRefresh->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnRefresh->GlowIntensity = 100;
			   this->btnRefresh->GlowRadius = 20;
			   this->btnRefresh->GradientBackground = false;
			   this->btnRefresh->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnRefresh->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnRefresh->HintText = nullptr;
			   this->btnRefresh->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnRefresh->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRefresh->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnRefresh->HoverTransitionDuration = 250;
			   this->btnRefresh->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnRefresh->ImagePadding = 5;
			   this->btnRefresh->ImageSize = System::Drawing::Size(16, 16);
			   this->btnRefresh->IsRadial = false;
			   this->btnRefresh->IsReadOnly = false;
			   this->btnRefresh->IsToggleButton = false;
			   this->btnRefresh->IsToggled = false;
			   this->btnRefresh->Location = System::Drawing::Point(684, 18);
			   this->btnRefresh->LongPressDurationMS = 1000;
			   this->btnRefresh->Name = L"btnRefresh";
			   this->btnRefresh->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRefresh->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnRefresh->ParticleCount = 15;
			   this->btnRefresh->PressAnimationScale = 0.97F;
			   this->btnRefresh->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnRefresh->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRefresh->PressTransitionDuration = 150;
			   this->btnRefresh->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnRefresh->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnRefresh->RippleRadiusMultiplier = 0.6F;
			   this->btnRefresh->ShadowBlur = 5;
			   this->btnRefresh->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnRefresh->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnRefresh->ShakeDuration = 500;
			   this->btnRefresh->ShakeIntensity = 5;
			   this->btnRefresh->Size = System::Drawing::Size(88, 32);
			   this->btnRefresh->TabIndex = 2;
			   this->btnRefresh->Text = L"Refresh";
			   this->btnRefresh->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnRefresh->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnRefresh->TooltipText = nullptr;
			   this->btnRefresh->UseAdvancedRendering = true;
			   this->btnRefresh->UseParticles = false;
			   this->btnRefresh->Click += gcnew System::EventHandler(this, &InventoryForm::btnRefresh_Click);
			   //
			   // panelCard
			   //
			   this->panelCard->ActiveBackColor = System::Drawing::Color::Empty;
			   this->panelCard->ActiveBorderColor = System::Drawing::Color::Empty;
			   this->panelCard->AdvancedBorderStyle = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::BorderStyleEx::Solid;
			   this->panelCard->AnimationDuration = 500;
			   this->panelCard->AnimationType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::AnimationTypeEx::Fade;
			   this->panelCard->BackColor = System::Drawing::Color::White;
			   this->panelCard->BackgroundImageCustom = nullptr;
			   this->panelCard->BackgroundImageOpacity = 1;
			   this->panelCard->BackgroundImageSizeMode = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::ImageSizeModeEx::Stretch;
			   this->panelCard->BackgroundOverlayColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->panelCard->BorderColor = System::Drawing::Color::Gray;
			   this->panelCard->BorderDashPattern = nullptr;
			   this->panelCard->BorderGlowColor = System::Drawing::Color::Cyan;
			   this->panelCard->BorderGlowSize = 3;
			   this->panelCard->BorderWidth = 2;
			   this->panelCard->BottomLeftRadius = 5;
			   this->panelCard->BottomRightRadius = 5;
			   this->panelCard->ContentAlignmentCustom = System::Drawing::ContentAlignment::MiddleCenter;
			   this->panelCard->Controls->Add(this->splitMain);
			   this->panelCard->CornerPadding = System::Windows::Forms::Padding(5);
			   this->panelCard->DisabledBackColor = System::Drawing::Color::Empty;
			   this->panelCard->DisabledBorderColor = System::Drawing::Color::Empty;
			   this->panelCard->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panelCard->DoubleBorderSpacing = 2;
			   this->panelCard->EasingType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::EasingTypeEx::Linear;
			   this->panelCard->EnableAnimation = false;
			   this->panelCard->EnableBackgroundImage = false;
			   this->panelCard->EnableBorderGlow = false;
			   this->panelCard->EnableDoubleBorder = false;
			   this->panelCard->EnableGradient = false;
			   this->panelCard->EnableInnerShadow = false;
			   this->panelCard->EnableShadow = false;
			   this->panelCard->EnableSmartPadding = true;
			   this->panelCard->EnableStateStyles = false;
			   this->panelCard->FlowDirectionCustom = System::Windows::Forms::FlowDirection::LeftToRight;
			   this->panelCard->GradientAngle = 90;
			   this->panelCard->GradientEndColor = System::Drawing::Color::LightGray;
			   this->panelCard->GradientStartColor = System::Drawing::Color::White;
			   this->panelCard->GradientType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::GradientTypeEx::Linear;
			   this->panelCard->HoverBackColor = System::Drawing::Color::Empty;
			   this->panelCard->HoverBorderColor = System::Drawing::Color::Empty;
			   this->panelCard->InnerShadowColor = System::Drawing::Color::Black;
			   this->panelCard->InnerShadowDepth = 3;
			   this->panelCard->InnerShadowOpacity = 0.2F;
			   this->panelCard->Location = System::Drawing::Point(0, 72);
			   this->panelCard->Name = L"panelCard";
			   this->panelCard->Padding = System::Windows::Forms::Padding(12);
			   this->panelCard->RadialGradientCenter = (cli::safe_cast<System::Drawing::PointF>(resources->GetObject(L"panelCard.RadialGradientCenter")));
			   this->panelCard->RadialGradientRadius = 1;
			   this->panelCard->ScaleRatio = 0.8F;
			   this->panelCard->SecondaryBorderColor = System::Drawing::Color::DarkGray;
			   this->panelCard->ShadowBlur = 10;
			   this->panelCard->ShadowColor = System::Drawing::Color::Black;
			   this->panelCard->ShadowDepth = 5;
			   this->panelCard->ShadowOffset = System::Drawing::Point(2, 2);
			   this->panelCard->ShadowOpacity = 0.3F;
			   this->panelCard->Size = System::Drawing::Size(916, 471);
			   this->panelCard->SlideDirection = System::Drawing::Point(0, -30);
			   this->panelCard->TabIndex = 0;
			   this->panelCard->TopLeftRadius = 5;
			   this->panelCard->TopRightRadius = 5;
			   //
			   // splitMain
			   //
			   this->splitMain->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->splitMain->Location = System::Drawing::Point(12, 12);
			   this->splitMain->Name = L"splitMain";
			   //
			   // splitMain.Panel1
			   //
			   this->splitMain->Panel1->Controls->Add(this->gridInventory);
			   //
			   // splitMain.Panel2
			   //
			   this->splitMain->Panel2->Controls->Add(this->detailsPanel);
			   this->splitMain->Size = System::Drawing::Size(892, 447);
			   this->splitMain->SplitterDistance = 620;
			   this->splitMain->TabIndex = 1;
			   //
			   // gridInventory
			   //
			   this->gridInventory->AllowUserToAddRows = false;
			   this->gridInventory->AllowUserToDeleteRows = false;
			   this->gridInventory->AllowUserToResizeRows = false;
			   this->gridInventory->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			   this->gridInventory->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->gridInventory->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->gridInventory->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			   this->gridInventory->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->gridInventory->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->gridInventory->Location = System::Drawing::Point(0, 0);
			   this->gridInventory->Name = L"gridInventory";
			   this->gridInventory->ReadOnly = true;
			   this->gridInventory->RowHeadersVisible = false;
			   this->gridInventory->RowTemplate->Height = 56;
			   this->gridInventory->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			   this->gridInventory->Size = System::Drawing::Size(620, 447);
			   this->gridInventory->TabIndex = 0;
			   this->gridInventory->SelectionChanged += gcnew System::EventHandler(this, &InventoryForm::gridInventory_SelectionChanged);
			   //
			   // detailsPanel
			   //
			   this->detailsPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->detailsPanel->Controls->Add(this->lblStatus);
			   this->detailsPanel->Controls->Add(this->txtPrice);
			   this->detailsPanel->Controls->Add(this->txtStock);
			   this->detailsPanel->Controls->Add(this->lblDetailsTitle);
			   this->detailsPanel->Controls->Add(this->picProduct);
			   this->detailsPanel->Controls->Add(this->txtCategory);
			   this->detailsPanel->Controls->Add(this->lblSKU);
			   this->detailsPanel->Controls->Add(this->txtName);
			   this->detailsPanel->Controls->Add(this->lblName);
			   this->detailsPanel->Controls->Add(this->txtSKU);
			   this->detailsPanel->Controls->Add(this->lblCategory);
			   this->detailsPanel->Controls->Add(this->lblPrice);
			   this->detailsPanel->Controls->Add(this->lblStock);
			   this->detailsPanel->Controls->Add(this->btnAdd);
			   this->detailsPanel->Controls->Add(this->btnEdit);
			   this->detailsPanel->Controls->Add(this->btnDelete);
			   this->detailsPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->detailsPanel->Location = System::Drawing::Point(0, 0);
			   this->detailsPanel->Name = L"detailsPanel";
			   this->detailsPanel->Padding = System::Windows::Forms::Padding(10);
			   this->detailsPanel->Size = System::Drawing::Size(268, 447);
			   this->detailsPanel->TabIndex = 0;
			   //
			   // lblStatus
			   //
			   this->lblStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->lblStatus->AutoSize = true;
			   this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->lblStatus->ForeColor = System::Drawing::Color::Firebrick;
			   this->lblStatus->Location = System::Drawing::Point(21, 361);
			   this->lblStatus->Name = L"lblStatus";
			   this->lblStatus->Size = System::Drawing::Size(0, 15);
			   this->lblStatus->TabIndex = 15;
			   this->lblStatus->Visible = false;
			   //
			   // txtPrice
			   //
			   this->txtPrice->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtPrice->BackColor = System::Drawing::Color::Transparent;
			   this->txtPrice->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtPrice->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtPrice->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtPrice->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtPrice->FocusImage = nullptr;
			   this->txtPrice->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtPrice->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtPrice->HoverImage = nullptr;
			   this->txtPrice->IdleImage = nullptr;
			   this->txtPrice->Location = System::Drawing::Point(15, 248);
			   this->txtPrice->Name = L"txtPrice";
			   this->txtPrice->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtPrice->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtPrice->PlaceholderText = L"";
			   this->txtPrice->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtPrice->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtPrice->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtPrice->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtPrice->Size = System::Drawing::Size(116, 25);
			   this->txtPrice->TabIndex = 7;
			   this->txtPrice->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtPrice->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtPrice->TextContent = L"";
			   this->txtPrice->ValidationPattern = L"";
			   //
			   // txtStock
			   //
			   this->txtStock->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtStock->BackColor = System::Drawing::Color::Transparent;
			   this->txtStock->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtStock->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtStock->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtStock->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtStock->FocusImage = nullptr;
			   this->txtStock->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtStock->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtStock->HoverImage = nullptr;
			   this->txtStock->IdleImage = nullptr;
			   this->txtStock->Location = System::Drawing::Point(147, 248);
			   this->txtStock->Name = L"txtStock";
			   this->txtStock->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtStock->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtStock->PlaceholderText = L"";
			   this->txtStock->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtStock->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtStock->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtStock->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtStock->Size = System::Drawing::Size(116, 25);
			   this->txtStock->TabIndex = 8;
			   this->txtStock->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtStock->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtStock->TextContent = L"";
			   this->txtStock->ValidationPattern = L"";
			   //
			   // lblDetailsTitle
			   //
			   this->lblDetailsTitle->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblDetailsTitle->AutoSize = true;
			   this->lblDetailsTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
			   this->lblDetailsTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->lblDetailsTitle->Location = System::Drawing::Point(10, 10);
			   this->lblDetailsTitle->Name = L"lblDetailsTitle";
			   this->lblDetailsTitle->Size = System::Drawing::Size(150, 20);
			   this->lblDetailsTitle->TabIndex = 0;
			   this->lblDetailsTitle->Text = L"No product selected";
			   //
			   // picProduct
			   //
			   this->picProduct->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->picProduct->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->picProduct->Location = System::Drawing::Point(12, 44);
			   this->picProduct->Name = L"picProduct";
			   this->picProduct->Size = System::Drawing::Size(120, 120);
			   this->picProduct->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->picProduct->TabIndex = 1;
			   this->picProduct->TabStop = false;
			   //
			   // txtCategory
			   //
			   this->txtCategory->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtCategory->BackColor = System::Drawing::Color::Transparent;
			   this->txtCategory->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtCategory->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtCategory->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtCategory->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtCategory->FocusImage = nullptr;
			   this->txtCategory->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtCategory->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)),
				   static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtCategory->HoverImage = nullptr;
			   this->txtCategory->IdleImage = nullptr;
			   this->txtCategory->Location = System::Drawing::Point(15, 194);
			   this->txtCategory->Name = L"txtCategory";
			   this->txtCategory->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtCategory->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtCategory->PlaceholderText = L"";
			   this->txtCategory->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtCategory->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtCategory->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtCategory->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtCategory->Size = System::Drawing::Size(248, 25);
			   this->txtCategory->TabIndex = 6;
			   this->txtCategory->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtCategory->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtCategory->TextContent = L"";
			   this->txtCategory->ValidationPattern = L"";
			   //
			   // lblSKU
			   //
			   this->lblSKU->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblSKU->AutoSize = true;
			   this->lblSKU->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblSKU->Location = System::Drawing::Point(144, 44);
			   this->lblSKU->Name = L"lblSKU";
			   this->lblSKU->Size = System::Drawing::Size(28, 15);
			   this->lblSKU->TabIndex = 2;
			   this->lblSKU->Text = L"SKU";
			   //
			   // txtName
			   //
			   this->txtName->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtName->BackColor = System::Drawing::Color::Transparent;
			   this->txtName->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtName->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtName->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtName->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtName->FocusImage = nullptr;
			   this->txtName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtName->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtName->HoverImage = nullptr;
			   this->txtName->IdleImage = nullptr;
			   this->txtName->Location = System::Drawing::Point(147, 116);
			   this->txtName->Name = L"txtName";
			   this->txtName->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtName->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtName->PlaceholderText = L"";
			   this->txtName->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtName->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtName->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtName->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtName->Size = System::Drawing::Size(116, 25);
			   this->txtName->TabIndex = 5;
			   this->txtName->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtName->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtName->TextContent = L"";
			   this->txtName->ValidationPattern = L"";
			   //
			   // lblName
			   //
			   this->lblName->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblName->AutoSize = true;
			   this->lblName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblName->Location = System::Drawing::Point(144, 98);
			   this->lblName->Name = L"lblName";
			   this->lblName->Size = System::Drawing::Size(39, 15);
			   this->lblName->TabIndex = 4;
			   this->lblName->Text = L"Name";
			   //
			   // txtSKU
			   //
			   this->txtSKU->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtSKU->BackColor = System::Drawing::Color::Transparent;
			   this->txtSKU->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtSKU->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtSKU->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtSKU->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtSKU->FocusImage = nullptr;
			   this->txtSKU->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtSKU->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtSKU->HoverImage = nullptr;
			   this->txtSKU->IdleImage = nullptr;
			   this->txtSKU->Location = System::Drawing::Point(147, 62);
			   this->txtSKU->Name = L"txtSKU";
			   this->txtSKU->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtSKU->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtSKU->PlaceholderText = L"";
			   this->txtSKU->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtSKU->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtSKU->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtSKU->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtSKU->Size = System::Drawing::Size(116, 25);
			   this->txtSKU->TabIndex = 4;
			   this->txtSKU->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtSKU->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtSKU->TextContent = L"";
			   this->txtSKU->ValidationPattern = L"";
			   //
			   // lblCategory
			   //
			   this->lblCategory->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblCategory->AutoSize = true;
			   this->lblCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblCategory->Location = System::Drawing::Point(12, 176);
			   this->lblCategory->Name = L"lblCategory";
			   this->lblCategory->Size = System::Drawing::Size(55, 15);
			   this->lblCategory->TabIndex = 6;
			   this->lblCategory->Text = L"Category";
			   //
			   // lblPrice
			   //
			   this->lblPrice->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblPrice->AutoSize = true;
			   this->lblPrice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblPrice->Location = System::Drawing::Point(12, 230);
			   this->lblPrice->Name = L"lblPrice";
			   this->lblPrice->Size = System::Drawing::Size(65, 15);
			   this->lblPrice->TabIndex = 8;
			   this->lblPrice->Text = L"Price (EGP)";
			   //
			   // lblStock
			   //
			   this->lblStock->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblStock->AutoSize = true;
			   this->lblStock->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblStock->Location = System::Drawing::Point(144, 230);
			   this->lblStock->Name = L"lblStock";
			   this->lblStock->Size = System::Drawing::Size(36, 15);
			   this->lblStock->TabIndex = 10;
			   this->lblStock->Text = L"Stock";
			   //
			   // btnAdd
			   //
			   this->btnAdd->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnAdd->AccessibleName = L"Add";
			   this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnAdd->AutoSizeBasedOnText = false;
			   this->btnAdd->BackColor = System::Drawing::Color::Transparent;
			   this->btnAdd->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnAdd->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnAdd->BadgeValue = 0;
			   this->btnAdd->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnAdd->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnAdd->BorderWidth = 1;
			   this->btnAdd->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnAdd->ButtonImage = nullptr;
			   this->btnAdd->ButtonTextLeftPadding = 0;
			   this->btnAdd->CanBeep = true;
			   this->btnAdd->CanGlow = false;
			   this->btnAdd->CanShake = true;
			   this->btnAdd->ContextMenuStripEx = nullptr;
			   this->btnAdd->CornerRadiusBottomLeft = 6;
			   this->btnAdd->CornerRadiusBottomRight = 6;
			   this->btnAdd->CornerRadiusTopLeft = 6;
			   this->btnAdd->CornerRadiusTopRight = 6;
			   this->btnAdd->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnAdd->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnAdd->EnableLongPress = false;
			   this->btnAdd->EnableRippleEffect = true;
			   this->btnAdd->EnableShadow = false;
			   this->btnAdd->EnableTextWrapping = false;
			   this->btnAdd->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnAdd->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnAdd->GlowIntensity = 100;
			   this->btnAdd->GlowRadius = 20;
			   this->btnAdd->GradientBackground = false;
			   this->btnAdd->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnAdd->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnAdd->HintText = nullptr;
			   this->btnAdd->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnAdd->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnAdd->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnAdd->HoverTransitionDuration = 250;
			   this->btnAdd->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnAdd->ImagePadding = 5;
			   this->btnAdd->ImageSize = System::Drawing::Size(16, 16);
			   this->btnAdd->IsRadial = false;
			   this->btnAdd->IsReadOnly = false;
			   this->btnAdd->IsToggleButton = false;
			   this->btnAdd->IsToggled = false;
			   this->btnAdd->Location = System::Drawing::Point(9, 388);
			   this->btnAdd->LongPressDurationMS = 1000;
			   this->btnAdd->Name = L"btnAdd";
			   this->btnAdd->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnAdd->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnAdd->ParticleCount = 15;
			   this->btnAdd->PressAnimationScale = 0.97F;
			   this->btnAdd->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnAdd->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnAdd->PressTransitionDuration = 150;
			   this->btnAdd->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnAdd->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnAdd->RippleRadiusMultiplier = 0.6F;
			   this->btnAdd->ShadowBlur = 5;
			   this->btnAdd->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnAdd->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnAdd->ShakeDuration = 500;
			   this->btnAdd->ShakeIntensity = 5;
			   this->btnAdd->Size = System::Drawing::Size(76, 36);
			   this->btnAdd->TabIndex = 12;
			   this->btnAdd->Text = L"Add";
			   this->btnAdd->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnAdd->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnAdd->TooltipText = nullptr;
			   this->btnAdd->UseAdvancedRendering = true;
			   this->btnAdd->UseParticles = false;
			   this->btnAdd->Click += gcnew System::EventHandler(this, &InventoryForm::btnAdd_Click);
			   //
			   // btnEdit
			   //
			   this->btnEdit->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnEdit->AccessibleName = L"Save";
			   this->btnEdit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnEdit->AutoSizeBasedOnText = false;
			   this->btnEdit->BackColor = System::Drawing::Color::Transparent;
			   this->btnEdit->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnEdit->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnEdit->BadgeValue = 0;
			   this->btnEdit->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnEdit->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnEdit->BorderWidth = 1;
			   this->btnEdit->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnEdit->ButtonImage = nullptr;
			   this->btnEdit->ButtonTextLeftPadding = 0;
			   this->btnEdit->CanBeep = true;
			   this->btnEdit->CanGlow = false;
			   this->btnEdit->CanShake = true;
			   this->btnEdit->ContextMenuStripEx = nullptr;
			   this->btnEdit->CornerRadiusBottomLeft = 6;
			   this->btnEdit->CornerRadiusBottomRight = 6;
			   this->btnEdit->CornerRadiusTopLeft = 6;
			   this->btnEdit->CornerRadiusTopRight = 6;
			   this->btnEdit->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnEdit->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnEdit->EnableLongPress = false;
			   this->btnEdit->EnableRippleEffect = true;
			   this->btnEdit->EnableShadow = false;
			   this->btnEdit->EnableTextWrapping = false;
			   this->btnEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnEdit->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnEdit->GlowIntensity = 100;
			   this->btnEdit->GlowRadius = 20;
			   this->btnEdit->GradientBackground = false;
			   this->btnEdit->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnEdit->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnEdit->HintText = nullptr;
			   this->btnEdit->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnEdit->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnEdit->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnEdit->HoverTransitionDuration = 250;
			   this->btnEdit->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnEdit->ImagePadding = 5;
			   this->btnEdit->ImageSize = System::Drawing::Size(16, 16);
			   this->btnEdit->IsRadial = false;
			   this->btnEdit->IsReadOnly = false;
			   this->btnEdit->IsToggleButton = false;
			   this->btnEdit->IsToggled = false;
			   this->btnEdit->Location = System::Drawing::Point(97, 388);
			   this->btnEdit->LongPressDurationMS = 1000;
			   this->btnEdit->Name = L"btnEdit";
			   this->btnEdit->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnEdit->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnEdit->ParticleCount = 15;
			   this->btnEdit->PressAnimationScale = 0.97F;
			   this->btnEdit->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnEdit->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnEdit->PressTransitionDuration = 150;
			   this->btnEdit->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnEdit->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnEdit->RippleRadiusMultiplier = 0.6F;
			   this->btnEdit->ShadowBlur = 5;
			   this->btnEdit->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnEdit->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnEdit->ShakeDuration = 500;
			   this->btnEdit->ShakeIntensity = 5;
			   this->btnEdit->Size = System::Drawing::Size(76, 36);
			   this->btnEdit->TabIndex = 13;
			   this->btnEdit->Text = L"Save";
			   this->btnEdit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnEdit->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnEdit->TooltipText = nullptr;
			   this->btnEdit->UseAdvancedRendering = true;
			   this->btnEdit->UseParticles = false;
			   this->btnEdit->Click += gcnew System::EventHandler(this, &InventoryForm::btnEdit_Click);
			   //
			   // btnDelete
			   //
			   this->btnDelete->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnDelete->AccessibleName = L"Delete";
			   this->btnDelete->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnDelete->AutoSizeBasedOnText = false;
			   this->btnDelete->BackColor = System::Drawing::Color::Transparent;
			   this->btnDelete->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnDelete->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnDelete->BadgeValue = 0;
			   this->btnDelete->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnDelete->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnDelete->BorderWidth = 1;
			   this->btnDelete->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnDelete->ButtonImage = nullptr;
			   this->btnDelete->ButtonTextLeftPadding = 0;
			   this->btnDelete->CanBeep = true;
			   this->btnDelete->CanGlow = false;
			   this->btnDelete->CanShake = true;
			   this->btnDelete->ContextMenuStripEx = nullptr;
			   this->btnDelete->CornerRadiusBottomLeft = 6;
			   this->btnDelete->CornerRadiusBottomRight = 6;
			   this->btnDelete->CornerRadiusTopLeft = 6;
			   this->btnDelete->CornerRadiusTopRight = 6;
			   this->btnDelete->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnDelete->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnDelete->EnableLongPress = false;
			   this->btnDelete->EnableRippleEffect = true;
			   this->btnDelete->EnableShadow = false;
			   this->btnDelete->EnableTextWrapping = false;
			   this->btnDelete->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnDelete->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnDelete->GlowIntensity = 100;
			   this->btnDelete->GlowRadius = 20;
			   this->btnDelete->GradientBackground = false;
			   this->btnDelete->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnDelete->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnDelete->HintText = nullptr;
			   this->btnDelete->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnDelete->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDelete->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnDelete->HoverTransitionDuration = 250;
			   this->btnDelete->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnDelete->ImagePadding = 5;
			   this->btnDelete->ImageSize = System::Drawing::Size(16, 16);
			   this->btnDelete->IsRadial = false;
			   this->btnDelete->IsReadOnly = false;
			   this->btnDelete->IsToggleButton = false;
			   this->btnDelete->IsToggled = false;
			   this->btnDelete->Location = System::Drawing::Point(185, 388);
			   this->btnDelete->LongPressDurationMS = 1000;
			   this->btnDelete->Name = L"btnDelete";
			   this->btnDelete->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDelete->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnDelete->ParticleCount = 15;
			   this->btnDelete->PressAnimationScale = 0.97F;
			   this->btnDelete->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnDelete->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDelete->PressTransitionDuration = 150;
			   this->btnDelete->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnDelete->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnDelete->RippleRadiusMultiplier = 0.6F;
			   this->btnDelete->ShadowBlur = 5;
			   this->btnDelete->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnDelete->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnDelete->ShakeDuration = 500;
			   this->btnDelete->ShakeIntensity = 5;
			   this->btnDelete->Size = System::Drawing::Size(76, 36);
			   this->btnDelete->TabIndex = 14;
			   this->btnDelete->Text = L"Delete";
			   this->btnDelete->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnDelete->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnDelete->TooltipText = nullptr;
			   this->btnDelete->UseAdvancedRendering = true;
			   this->btnDelete->UseParticles = false;
			   this->btnDelete->Click += gcnew System::EventHandler(this, &InventoryForm::btnDelete_Click);
			   //
			   // InventoryForm
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->ClientSize = System::Drawing::Size(916, 543);
			   this->Controls->Add(this->panelCard);
			   this->Controls->Add(this->panelHeader);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"InventoryForm";
			   this->Text = L"Inventory";
			   this->panelHeader->ResumeLayout(false);
			   this->panelHeader->PerformLayout();
			   this->panelCard->ResumeLayout(false);
			   this->splitMain->Panel1->ResumeLayout(false);
			   this->splitMain->Panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->EndInit();
			   this->splitMain->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridInventory))->EndInit();
			   this->detailsPanel->ResumeLayout(false);
			   this->detailsPanel->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picProduct))->EndInit();
			   this->ResumeLayout(false);
		   }
#pragma endregion

		   //
		   // Helpers: columns, sample data, grid population, events
		   //
	private:
		void AddGridColumns()
		{
			gridInventory->Columns->Clear();
			gridInventory->AutoGenerateColumns = false;
			gridInventory->SelectionMode =
				DataGridViewSelectionMode::FullRowSelect;

			if (this->gridInventory->Columns->Count > 0) return;

			// Hidden Id
			System::Windows::Forms::DataGridViewTextBoxColumn^ colId = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colId->Name = L"colId";
			colId->HeaderText = L"Id";
			colId->Visible = false;
			this->gridInventory->Columns->Add(colId);

			// SKU
			System::Windows::Forms::DataGridViewTextBoxColumn^ colSKU = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colSKU->Name = L"colSKU";
			colSKU->HeaderText = L"SKU";
			colSKU->FillWeight = 80;
			this->gridInventory->Columns->Add(colSKU);

			// Name
			System::Windows::Forms::DataGridViewTextBoxColumn^ colName = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colName->Name = L"colName";
			colName->HeaderText = L"Product";
			colName->FillWeight = 220;
			this->gridInventory->Columns->Add(colName);

			// Category
			System::Windows::Forms::DataGridViewTextBoxColumn^ colCat = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colCat->Name = L"colCategory";
			colCat->HeaderText = L"Category";
			colCat->FillWeight = 120;
			this->gridInventory->Columns->Add(colCat);

			// Price
			System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colPrice->Name = L"colPrice";
			colPrice->HeaderText = L"Price";
			colPrice->FillWeight = 90;
			colPrice->DefaultCellStyle->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleRight;
			this->gridInventory->Columns->Add(colPrice);

			// Stock
			System::Windows::Forms::DataGridViewTextBoxColumn^ colStock = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colStock->Name = L"colStock";
			colStock->HeaderText = L"Stock";
			colStock->FillWeight = 80;
			colStock->DefaultCellStyle->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			this->gridInventory->Columns->Add(colStock);
		}

		void InitializeInventory()
		{
			_allProducts = gcnew List<ProductRow^>();

			SqlConnection^ conn = DatabaseManager::CreateConnection();

			try
			{
				conn->Open();

				// Join Inventory with Products to show meaningful info
				String^ sql =
					"SELECT i.Id AS InventoryId, "
					"       i.ProductId, "
					"       ISNULL(i.Location, '')       AS Location, "
					"       ISNULL(i.Quantity, 0)        AS Quantity, "
					"       ISNULL(p.Name, '')           AS ProductName, "
					"       ISNULL(p.Category, '')       AS Category, "
					"       ISNULL(p.Price, 0)           AS Price "
					"FROM procure.Inventory i "
					"LEFT JOIN procure.Products p ON p.Id = i.ProductId "
					"ORDER BY p.Name, i.Location;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				SqlDataReader^ r = cmd->ExecuteReader();

				while (r->Read())
				{
					ProductRow^ pr = gcnew ProductRow();

					pr->Id = r->IsDBNull(0) ? 0 : r->GetInt32(0);                // Inventory.Id
					pr->ProductId = r->IsDBNull(1) ? 0 : r->GetInt32(1);                // ProductId
					pr->Location = r->IsDBNull(2) ? L"" : r->GetString(2);             // Inventory.Location
					pr->SKU = pr->Location;                                       // map to SKU column
					pr->Stock = r->IsDBNull(3) ? 0 : r->GetInt32(3);                // Quantity
					pr->Name = r->IsDBNull(4) ? L"" : r->GetString(4);             // Product Name
					pr->Category = r->IsDBNull(5) ? L"" : r->GetString(5);             // Category
					pr->Price = r->IsDBNull(6) ? 0.0
						: Convert::ToDouble(r->GetDecimal(6)); // Price
					pr->ImagePath = nullptr;
					pr->Notes = nullptr;

					_allProducts->Add(pr);
				}

				r->Close();

				// build category combo (All + distinct categories)
				System::Collections::Generic::HashSet<String^>^ cats =
					gcnew System::Collections::Generic::HashSet<String^>();

				cats->Add(L"All");
				for each(ProductRow ^ pr in _allProducts)
				{
					if (!String::IsNullOrWhiteSpace(pr->Category))
						cats->Add(pr->Category);
				}

				cmbCategory->Items->Clear();
				for each(String ^ c in cats)
					cmbCategory->Items->Add(c);

				if (cmbCategory->Items->Count > 0)
					cmbCategory->SelectedIndex = 0;
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(
					L"Error loading inventory:\n" + ex->Message,
					L"Inventory",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			finally
			{
				if (conn != nullptr && conn->State == ConnectionState::Open)
					conn->Close();
			}
		}

		void ApplyFilters()
		{
			String^ search = txtSearch->Text->Trim()->ToLower();
			String^ selectedCategory = nullptr;

			if (cmbCategory->SelectedIndex > 0)
				selectedCategory = cmbCategory->SelectedItem->ToString();

			List<ProductRow^>^ filtered = gcnew List<ProductRow^>();

			for each(ProductRow ^ p in _allProducts)
			{
				bool matchCategory =
					(selectedCategory == nullptr ||
						selectedCategory == L"All" ||
						p->Category == selectedCategory);

				bool matchSearch =
					(search->Length == 0 ||
						(!String::IsNullOrEmpty(p->Name) && p->Name->ToLower()->Contains(search)) ||
						(!String::IsNullOrEmpty(p->SKU) && p->SKU->ToLower()->Contains(search)) ||
						(!String::IsNullOrEmpty(p->Category) && p->Category->ToLower()->Contains(search)));

				if (matchCategory && matchSearch)
					filtered->Add(p);
			}

			PopulateGrid(filtered);
		}

		void PopulateGrid(List<ProductRow^>^ rows)
		{
			this->gridInventory->Rows->Clear();

			for each(ProductRow ^ p in rows)
			{
				array<Object^>^ vals = gcnew array<Object^>(6);
				vals[0] = p->Id;                         // Inventory.Id (hidden)
				vals[1] = p->SKU;                        // Location (shown as "SKU")
				vals[2] = p->Name;                       // Product name
				vals[3] = p->Category;                   // Category
				vals[4] = p->Price.ToString("N2");       // Price from Products
				vals[5] = p->Stock;                      // Quantity
				this->gridInventory->Rows->Add(vals);
			}

			this->gridInventory->ClearSelection();
			lblDetailsTitle->Text = L"No item selected";
			ClearDetails();
			btnEdit->Enabled = false;
			btnDelete->Enabled = false;
		}

		void ClearDetails()
		{
			txtSKU->Text = L"";       // Location
			txtName->Text = L"";
			txtCategory->Text = L"";
			txtPrice->Text = L"";
			txtStock->Text = L"";
			picProduct->Image = nullptr;
		}

		// Here "id" = Inventory.Id (not ProductId)
		ProductRow^ FindProductById(int id)
		{
			for each(ProductRow ^ p in _allProducts)
				if (p->Id == id)
					return p;
			return nullptr;
		}

		//
		// Events
		//
	private: System::Void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ApplyFilters();
	}

	private: System::Void cmbCategory_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ApplyFilters();
	}

	private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
	{
		InitializeInventory();   // reload from DB
		ApplyFilters();          // apply current filters
	}

	private: System::Void gridInventory_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridInventory->SelectedRows->Count == 0)
		{
			lblDetailsTitle->Text = L"No item selected";
			ClearDetails();
			btnEdit->Enabled = false;
			btnDelete->Enabled = false;
			return;
		}

		DataGridViewRow^ row = this->gridInventory->SelectedRows[0];
		Object^ idv = row->Cells[L"colId"]->Value;
		if (idv == nullptr)
			return;

		int id = System::Convert::ToInt32(idv);
		ProductRow^ p = FindProductById(id);
		if (p == nullptr)
			return;

		// Title
		lblDetailsTitle->Text = String::Format(L"{0} — {1}", p->Name, p->Location);

		// Map fields
		txtSKU->Text = p->Location;                // location
		txtName->Text = p->Name;
		txtCategory->Text = p->Category;
		txtPrice->Text = p->Price.ToString("N2");
		txtStock->Text = p->Stock.ToString();

		// (optional) no image for now
		picProduct->Image = nullptr;

		if (Session::IsAdministrator) {
			btnEdit->Enabled = true;
			btnDelete->Enabled = true;
		}
	}

	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridInventory->SelectedRows->Count == 0)
		{
			MessageBox::Show(
				L"Select an existing inventory row to base the new entry on.",
				L"Add Inventory",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}

		DataGridViewRow^ sel = this->gridInventory->SelectedRows[0];
		int invId = System::Convert::ToInt32(sel->Cells[L"colId"]->Value);

		ProductRow^ baseRow = FindProductById(invId);
		if (baseRow == nullptr)
			return;

		String^ location = txtSKU->Text->Trim();   // reuse SKU textbox as Location
		if (String::IsNullOrWhiteSpace(location))
		{
			MessageBox::Show(L"Location cannot be empty.", L"Validation",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int qty = 0;
		try { qty = System::Convert::ToInt32(txtStock->Text); }
		catch (...) { qty = 0; }

		if (qty <= 0)
		{
			MessageBox::Show(L"Quantity must be a positive number.", L"Validation",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		SqlConnection^ conn = DatabaseManager::CreateConnection();

		try
		{
			conn->Open();

			String^ sql =
				"INSERT INTO procure.Inventory (ProductId, Location, Quantity, LastUpdated) "
				"VALUES (@pid, @loc, @qty, SYSUTCDATETIME());";

			SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
			cmd->Parameters->AddWithValue("@pid", baseRow->ProductId);
			cmd->Parameters->AddWithValue("@loc", location);
			cmd->Parameters->AddWithValue("@qty", qty);

			cmd->ExecuteNonQuery();

			MessageBox::Show(L"Inventory record added.", L"Inventory",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			InitializeInventory();
			ApplyFilters();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Error adding inventory:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		finally
		{
			if (conn != nullptr && conn->State == ConnectionState::Open)
				conn->Close();
		}
	}

	private: System::Void btnEdit_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridInventory->SelectedRows->Count == 0)
		{
			MessageBox::Show(L"Select an inventory row to update.",
				L"Edit Inventory",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}

		DataGridViewRow^ sel = this->gridInventory->SelectedRows[0];
		int invId = System::Convert::ToInt32(sel->Cells[L"colId"]->Value);

		ProductRow^ p = FindProductById(invId);
		if (p == nullptr) return;

		String^ location = txtSKU->Text->Trim();
		if (String::IsNullOrWhiteSpace(location))
		{
			MessageBox::Show(L"Location cannot be empty.", L"Validation",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		int qty = 0;
		try { qty = System::Convert::ToInt32(txtStock->Text); }
		catch (...) { qty = 0; }

		if (qty < 0)
		{
			MessageBox::Show(L"Quantity cannot be negative.", L"Validation",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		SqlConnection^ conn = DatabaseManager::CreateConnection();

		try
		{
			conn->Open();

			String^ sql =
				"UPDATE procure.Inventory "
				"SET Location = @loc, Quantity = @qty, LastUpdated = SYSUTCDATETIME() "
				"WHERE Id = @id;";

			SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
			cmd->Parameters->AddWithValue("@loc", location);
			cmd->Parameters->AddWithValue("@qty", qty);
			cmd->Parameters->AddWithValue("@id", invId);

			cmd->ExecuteNonQuery();

			MessageBox::Show(L"Inventory updated.", L"Inventory",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			InitializeInventory();
			ApplyFilters();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Error updating inventory:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		finally
		{
			if (conn != nullptr && conn->State == ConnectionState::Open)
				conn->Close();
		}
	}

	private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridInventory->SelectedRows->Count == 0)
		{
			MessageBox::Show(L"Select an inventory row to delete.",
				L"Delete Inventory",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
			return;
		}

		DataGridViewRow^ sel = this->gridInventory->SelectedRows[0];
		int invId = System::Convert::ToInt32(sel->Cells[L"colId"]->Value);

		auto result = MessageBox::Show(
			L"Delete selected inventory record? This cannot be undone.",
			L"Confirm Delete",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning);

		if (result != System::Windows::Forms::DialogResult::Yes)
			return;

		SqlConnection^ conn = DatabaseManager::CreateConnection();

		try
		{
			conn->Open();

			String^ sql = "DELETE FROM procure.Inventory WHERE Id = @id;";
			SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
			cmd->Parameters->AddWithValue("@id", invId);
			cmd->ExecuteNonQuery();

			MessageBox::Show(L"Inventory record deleted.", L"Inventory",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			InitializeInventory();
			ApplyFilters();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Error deleting inventory:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		finally
		{
			if (conn != nullptr && conn->State == ConnectionState::Open)
				conn->Close();
		}
	}
	}; // end class InventoryForm
} // end namespace IntraProcure
