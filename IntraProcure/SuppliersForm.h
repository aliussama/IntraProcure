#pragma once

#include "UiStyler.h"
#include "Session.h"
#include "Supplier.h"
#include "SupplierManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace IntraProcure {
	/// <summary>
	/// SuppliersForm - list, search, add, edit, delete suppliers
	/// </summary>
	public ref class SuppliersForm : public System::Windows::Forms::Form
	{
	public:
		SuppliersForm(void)
		{
			InitializeComponent();

			// style helpers
			UiStyler::StyleTextBox(txtSearch);
			UiStyler::StylePrimaryButton(btnAdd);
			UiStyler::StyleSecondaryButton(btnEdit);
			UiStyler::StyleDangerButton(btnDelete);
			UiStyler::StyleButton(btnRefresh);
			UiStyler::StyleGrid(gridSuppliers);

			// grid setup & load
			AddGridColumns();
			InitializeSuppliers();   // sample data (replace with DB)
			ApplyFilters();
			ApplyRolePermissions();
		}

	protected:
		~SuppliersForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// Designer components
		System::ComponentModel::Container^ components;

		// Header area
		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
		System::Windows::Forms::Label^ lblTitle;
		SiticoneNetFrameworkUI::SiticoneTextBox^ txtSearch;
		SiticoneNetFrameworkUI::SiticoneButton^ btnRefresh;

		// Main card / layout
		SiticoneNetFrameworkUI::SiticoneAdvancedPanel^ panelCard;
		System::Windows::Forms::SplitContainer^ splitMain;

		// Left: suppliers list
		System::Windows::Forms::DataGridView^ gridSuppliers;

		// Right: details / editor
		System::Windows::Forms::Panel^ detailsPanel;
		System::Windows::Forms::Label^ lblDetailsTitle;
		System::Windows::Forms::Label^ lblName;

		System::Windows::Forms::Label^ lblContact;

		System::Windows::Forms::Label^ lblEmail;

		System::Windows::Forms::Label^ lblPhone;

		System::Windows::Forms::Label^ lblAddress;

		// action buttons
		SiticoneNetFrameworkUI::SiticoneButton^ btnAdd;
		SiticoneNetFrameworkUI::SiticoneButton^ btnEdit;
		SiticoneNetFrameworkUI::SiticoneButton^ btnDelete;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtName;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtPhone;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtEmail;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtContact;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtAddress;

		   // Runtime state
		   ref struct SupplierRow {
			   int Id;
			   String^ Name;
			   String^ ContactPerson;
			   String^ Email;
			   String^ Phone;
			   String^ Address;
			   String^ Notes;
		   };

		   List<SupplierRow^>^ _allSuppliers;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SuppliersForm::typeid));
			   this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->txtSearch = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			   this->btnRefresh = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelCard = (gcnew SiticoneNetFrameworkUI::SiticoneAdvancedPanel());
			   this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			   this->gridSuppliers = (gcnew System::Windows::Forms::DataGridView());
			   this->detailsPanel = (gcnew System::Windows::Forms::Panel());
			   this->txtAddress = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->txtPhone = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblDetailsTitle = (gcnew System::Windows::Forms::Label());
			   this->txtEmail = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->txtName = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->txtContact = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblName = (gcnew System::Windows::Forms::Label());
			   this->lblContact = (gcnew System::Windows::Forms::Label());
			   this->lblEmail = (gcnew System::Windows::Forms::Label());
			   this->lblPhone = (gcnew System::Windows::Forms::Label());
			   this->lblAddress = (gcnew System::Windows::Forms::Label());
			   this->btnAdd = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnEdit = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnDelete = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelHeader->SuspendLayout();
			   this->panelCard->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->BeginInit();
			   this->splitMain->Panel1->SuspendLayout();
			   this->splitMain->Panel2->SuspendLayout();
			   this->splitMain->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridSuppliers))->BeginInit();
			   this->detailsPanel->SuspendLayout();
			   this->SuspendLayout();
			   //
			   // panelHeader
			   //
			   this->panelHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelHeader->Controls->Add(this->lblTitle);
			   this->panelHeader->Controls->Add(this->txtSearch);
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
			   this->lblTitle->Size = System::Drawing::Size(95, 25);
			   this->lblTitle->TabIndex = 0;
			   this->lblTitle->Text = L"Suppliers";
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
			   this->txtSearch->PlaceholderText = L"Search suppliers by name, contact or email...";
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
			   this->txtSearch->Size = System::Drawing::Size(380, 32);
			   this->txtSearch->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			   this->txtSearch->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtSearch->SolidBorderHoverColor = System::Drawing::Color::Gray;
			   this->txtSearch->SolidFillColor = System::Drawing::Color::White;
			   this->txtSearch->TabIndex = 0;
			   this->txtSearch->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			   this->txtSearch->ValidationErrorMessage = L"Invalid input.";
			   this->txtSearch->ValidationFunction = nullptr;
			   this->txtSearch->TextChanged += gcnew System::EventHandler(this, &SuppliersForm::txtSearch_TextChanged);
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
			   this->btnRefresh->Location = System::Drawing::Point(580, 18);
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
			   this->btnRefresh->TabIndex = 1;
			   this->btnRefresh->Text = L"Refresh";
			   this->btnRefresh->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnRefresh->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnRefresh->TooltipText = nullptr;
			   this->btnRefresh->UseAdvancedRendering = true;
			   this->btnRefresh->UseParticles = false;
			   this->btnRefresh->Click += gcnew System::EventHandler(this, &SuppliersForm::btnRefresh_Click);
			   //
			   // panelCard
			   //
			   this->panelCard->ActiveBackColor = System::Drawing::Color::Empty;
			   this->panelCard->ActiveBorderColor = System::Drawing::Color::Empty;
			   this->panelCard->AdvancedBorderStyle = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::BorderStyleEx::Solid;
			   this->panelCard->AnimationDuration = 500;
			   this->panelCard->AnimationType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::AnimationTypeEx::Fade;
			   this->panelCard->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelCard->BackgroundImageCustom = nullptr;
			   this->panelCard->BackgroundImageOpacity = 1;
			   this->panelCard->BackgroundImageSizeMode = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::ImageSizeModeEx::Stretch;
			   this->panelCard->BackgroundOverlayColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->panelCard->BorderColor = System::Drawing::Color::Gray;
			   this->panelCard->BorderDashPattern = nullptr;
			   this->panelCard->BorderGlowColor = System::Drawing::Color::Cyan;
			   this->panelCard->BorderGlowSize = 3;
			   this->panelCard->BorderWidth = 1;
			   this->panelCard->BottomLeftRadius = 12;
			   this->panelCard->BottomRightRadius = 12;
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
			   this->panelCard->TopLeftRadius = 12;
			   this->panelCard->TopRightRadius = 12;
			   //
			   // splitMain
			   //
			   this->splitMain->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->splitMain->Location = System::Drawing::Point(12, 12);
			   this->splitMain->Name = L"splitMain";
			   //
			   // splitMain.Panel1
			   //
			   this->splitMain->Panel1->Controls->Add(this->gridSuppliers);
			   //
			   // splitMain.Panel2
			   //
			   this->splitMain->Panel2->Controls->Add(this->detailsPanel);
			   this->splitMain->Size = System::Drawing::Size(892, 447);
			   this->splitMain->SplitterDistance = 560;
			   this->splitMain->TabIndex = 1;
			   //
			   // gridSuppliers
			   //
			   this->gridSuppliers->AllowUserToAddRows = false;
			   this->gridSuppliers->AllowUserToDeleteRows = false;
			   this->gridSuppliers->AllowUserToResizeRows = false;
			   this->gridSuppliers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			   this->gridSuppliers->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->gridSuppliers->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->gridSuppliers->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			   this->gridSuppliers->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->gridSuppliers->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				   static_cast<System::Int32>(static_cast<System::Byte>(249)));
			   this->gridSuppliers->Location = System::Drawing::Point(0, 0);
			   this->gridSuppliers->Name = L"gridSuppliers";
			   this->gridSuppliers->ReadOnly = true;
			   this->gridSuppliers->RowHeadersVisible = false;
			   this->gridSuppliers->RowTemplate->Height = 40;
			   this->gridSuppliers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			   this->gridSuppliers->Size = System::Drawing::Size(560, 447);
			   this->gridSuppliers->TabIndex = 0;
			   this->gridSuppliers->SelectionChanged += gcnew System::EventHandler(this, &SuppliersForm::gridSuppliers_SelectionChanged);
			   //
			   // detailsPanel
			   //
			   this->detailsPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->detailsPanel->Controls->Add(this->txtAddress);
			   this->detailsPanel->Controls->Add(this->txtPhone);
			   this->detailsPanel->Controls->Add(this->lblDetailsTitle);
			   this->detailsPanel->Controls->Add(this->txtEmail);
			   this->detailsPanel->Controls->Add(this->txtName);
			   this->detailsPanel->Controls->Add(this->txtContact);
			   this->detailsPanel->Controls->Add(this->lblName);
			   this->detailsPanel->Controls->Add(this->lblContact);
			   this->detailsPanel->Controls->Add(this->lblEmail);
			   this->detailsPanel->Controls->Add(this->lblPhone);
			   this->detailsPanel->Controls->Add(this->lblAddress);
			   this->detailsPanel->Controls->Add(this->btnAdd);
			   this->detailsPanel->Controls->Add(this->btnEdit);
			   this->detailsPanel->Controls->Add(this->btnDelete);
			   this->detailsPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->detailsPanel->Location = System::Drawing::Point(0, 0);
			   this->detailsPanel->Name = L"detailsPanel";
			   this->detailsPanel->Padding = System::Windows::Forms::Padding(10);
			   this->detailsPanel->Size = System::Drawing::Size(328, 447);
			   this->detailsPanel->TabIndex = 0;
			   //
			   // txtAddress
			   //
			   this->txtAddress->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtAddress->BackColor = System::Drawing::Color::Transparent;
			   this->txtAddress->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->txtAddress->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtAddress->BottomLeftCornerRadius = 5;
			   this->txtAddress->BottomRightCornerRadius = 5;
			   this->txtAddress->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtAddress->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtAddress->FocusImage = nullptr;
			   this->txtAddress->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtAddress->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtAddress->HoverImage = nullptr;
			   this->txtAddress->IdleImage = nullptr;
			   this->txtAddress->InputType = SiticoneNetFrameworkUI::AdvancedTextBoxInputType::Email;
			   this->txtAddress->Location = System::Drawing::Point(12, 278);
			   this->txtAddress->Multiline = true;
			   this->txtAddress->Name = L"txtAddress";
			   this->txtAddress->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(108)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(125)));
			   this->txtAddress->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtAddress->PlaceholderText = L"";
			   this->txtAddress->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtAddress->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtAddress->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtAddress->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtAddress->Size = System::Drawing::Size(280, 100);
			   this->txtAddress->TabIndex = 14;
			   this->txtAddress->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtAddress->TextContent = L"";
			   this->txtAddress->TopLeftCornerRadius = 5;
			   this->txtAddress->TopRightCornerRadius = 5;
			   this->txtAddress->ValidationEnabled = false;
			   this->txtAddress->ValidationPattern = L"";
			   //
			   // txtPhone
			   //
			   this->txtPhone->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtPhone->BackColor = System::Drawing::Color::Transparent;
			   this->txtPhone->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtPhone->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtPhone->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtPhone->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtPhone->FocusImage = nullptr;
			   this->txtPhone->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtPhone->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtPhone->HoverImage = nullptr;
			   this->txtPhone->IdleImage = nullptr;
			   this->txtPhone->Location = System::Drawing::Point(12, 224);
			   this->txtPhone->Name = L"txtPhone";
			   this->txtPhone->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtPhone->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtPhone->PlaceholderText = L"";
			   this->txtPhone->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtPhone->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtPhone->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtPhone->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtPhone->Size = System::Drawing::Size(280, 25);
			   this->txtPhone->TabIndex = 6;
			   this->txtPhone->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtPhone->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtPhone->TextContent = L"";
			   this->txtPhone->ValidationPattern = L"";
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
			   this->lblDetailsTitle->Size = System::Drawing::Size(151, 20);
			   this->lblDetailsTitle->TabIndex = 0;
			   this->lblDetailsTitle->Text = L"No supplier selected";
			   //
			   // txtEmail
			   //
			   this->txtEmail->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtEmail->BackColor = System::Drawing::Color::Transparent;
			   this->txtEmail->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)), static_cast<System::Int32>(static_cast<System::Byte>(250)),
				   static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtEmail->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtEmail->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtEmail->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtEmail->FocusImage = nullptr;
			   this->txtEmail->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtEmail->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtEmail->HoverImage = nullptr;
			   this->txtEmail->IdleImage = nullptr;
			   this->txtEmail->Location = System::Drawing::Point(12, 170);
			   this->txtEmail->Name = L"txtEmail";
			   this->txtEmail->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtEmail->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtEmail->PlaceholderText = L"";
			   this->txtEmail->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtEmail->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtEmail->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtEmail->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtEmail->Size = System::Drawing::Size(280, 25);
			   this->txtEmail->TabIndex = 5;
			   this->txtEmail->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtEmail->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtEmail->TextContent = L"";
			   this->txtEmail->ValidationPattern = L"";
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
			   this->txtName->Location = System::Drawing::Point(12, 62);
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
			   this->txtName->Size = System::Drawing::Size(280, 25);
			   this->txtName->TabIndex = 3;
			   this->txtName->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtName->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtName->TextContent = L"";
			   this->txtName->ValidationPattern = L"";
			   //
			   // txtContact
			   //
			   this->txtContact->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtContact->BackColor = System::Drawing::Color::Transparent;
			   this->txtContact->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)), static_cast<System::Int32>(static_cast<System::Byte>(252)));
			   this->txtContact->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtContact->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtContact->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtContact->FocusImage = nullptr;
			   this->txtContact->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtContact->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)),
				   static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtContact->HoverImage = nullptr;
			   this->txtContact->IdleImage = nullptr;
			   this->txtContact->Location = System::Drawing::Point(12, 116);
			   this->txtContact->Name = L"txtContact";
			   this->txtContact->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtContact->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtContact->PlaceholderText = L"";
			   this->txtContact->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtContact->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtContact->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtContact->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtContact->Size = System::Drawing::Size(280, 25);
			   this->txtContact->TabIndex = 4;
			   this->txtContact->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtContact->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtContact->TextContent = L"";
			   this->txtContact->ValidationPattern = L"";
			   //
			   // lblName
			   //
			   this->lblName->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblName->AutoSize = true;
			   this->lblName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblName->Location = System::Drawing::Point(12, 44);
			   this->lblName->Name = L"lblName";
			   this->lblName->Size = System::Drawing::Size(39, 15);
			   this->lblName->TabIndex = 1;
			   this->lblName->Text = L"Name";
			   //
			   // lblContact
			   //
			   this->lblContact->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblContact->AutoSize = true;
			   this->lblContact->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblContact->Location = System::Drawing::Point(12, 98);
			   this->lblContact->Name = L"lblContact";
			   this->lblContact->Size = System::Drawing::Size(88, 15);
			   this->lblContact->TabIndex = 3;
			   this->lblContact->Text = L"Contact Person";
			   //
			   // lblEmail
			   //
			   this->lblEmail->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblEmail->AutoSize = true;
			   this->lblEmail->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblEmail->Location = System::Drawing::Point(12, 152);
			   this->lblEmail->Name = L"lblEmail";
			   this->lblEmail->Size = System::Drawing::Size(36, 15);
			   this->lblEmail->TabIndex = 5;
			   this->lblEmail->Text = L"Email";
			   //
			   // lblPhone
			   //
			   this->lblPhone->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblPhone->AutoSize = true;
			   this->lblPhone->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblPhone->Location = System::Drawing::Point(12, 206);
			   this->lblPhone->Name = L"lblPhone";
			   this->lblPhone->Size = System::Drawing::Size(41, 15);
			   this->lblPhone->TabIndex = 7;
			   this->lblPhone->Text = L"Phone";
			   //
			   // lblAddress
			   //
			   this->lblAddress->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblAddress->AutoSize = true;
			   this->lblAddress->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->lblAddress->Location = System::Drawing::Point(12, 260);
			   this->lblAddress->Name = L"lblAddress";
			   this->lblAddress->Size = System::Drawing::Size(49, 15);
			   this->lblAddress->TabIndex = 9;
			   this->lblAddress->Text = L"Address";
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
			   this->btnAdd->Location = System::Drawing::Point(23, 391);
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
			   this->btnAdd->Size = System::Drawing::Size(90, 36);
			   this->btnAdd->TabIndex = 11;
			   this->btnAdd->Text = L"Add";
			   this->btnAdd->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnAdd->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnAdd->TooltipText = nullptr;
			   this->btnAdd->UseAdvancedRendering = true;
			   this->btnAdd->UseParticles = false;
			   this->btnAdd->Click += gcnew System::EventHandler(this, &SuppliersForm::btnAdd_Click);
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
			   this->btnEdit->Location = System::Drawing::Point(119, 391);
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
			   this->btnEdit->Size = System::Drawing::Size(90, 36);
			   this->btnEdit->TabIndex = 12;
			   this->btnEdit->Text = L"Save";
			   this->btnEdit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnEdit->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnEdit->TooltipText = nullptr;
			   this->btnEdit->UseAdvancedRendering = true;
			   this->btnEdit->UseParticles = false;
			   this->btnEdit->Click += gcnew System::EventHandler(this, &SuppliersForm::btnEdit_Click);
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
			   this->btnDelete->Location = System::Drawing::Point(215, 391);
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
			   this->btnDelete->Size = System::Drawing::Size(90, 36);
			   this->btnDelete->TabIndex = 13;
			   this->btnDelete->Text = L"Delete";
			   this->btnDelete->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnDelete->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnDelete->TooltipText = nullptr;
			   this->btnDelete->UseAdvancedRendering = true;
			   this->btnDelete->UseParticles = false;
			   this->btnDelete->Click += gcnew System::EventHandler(this, &SuppliersForm::btnDelete_Click);
			   //
			   // SuppliersForm
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->ClientSize = System::Drawing::Size(916, 543);
			   this->Controls->Add(this->panelCard);
			   this->Controls->Add(this->panelHeader);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"SuppliersForm";
			   this->Text = L"Suppliers";
			   this->panelHeader->ResumeLayout(false);
			   this->panelHeader->PerformLayout();
			   this->panelCard->ResumeLayout(false);
			   this->splitMain->Panel1->ResumeLayout(false);
			   this->splitMain->Panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->EndInit();
			   this->splitMain->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridSuppliers))->EndInit();
			   this->detailsPanel->ResumeLayout(false);
			   this->detailsPanel->PerformLayout();
			   this->ResumeLayout(false);
		   }
#pragma endregion

		   //
		   // Helpers: grid columns, style, load, populate, filtering
		   //
	private:
		void AddGridColumns()
		{
			if (this->gridSuppliers->Columns->Count > 0) return;

			// Id (hidden)
			System::Windows::Forms::DataGridViewTextBoxColumn^ colId = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colId->Name = L"colId";
			colId->HeaderText = L"ID";
			colId->Visible = false;
			this->gridSuppliers->Columns->Add(colId);

			// Name
			System::Windows::Forms::DataGridViewTextBoxColumn^ colName = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colName->Name = L"colName";
			colName->HeaderText = L"Supplier";
			colName->FillWeight = 200;
			this->gridSuppliers->Columns->Add(colName);

			// Contact
			System::Windows::Forms::DataGridViewTextBoxColumn^ colContact = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colContact->Name = L"colContact";
			colContact->HeaderText = L"Contact Person";
			colContact->FillWeight = 150;
			this->gridSuppliers->Columns->Add(colContact);

			// Email
			System::Windows::Forms::DataGridViewTextBoxColumn^ colEmail = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colEmail->Name = L"colEmail";
			colEmail->HeaderText = L"Email";
			colEmail->FillWeight = 160;
			this->gridSuppliers->Columns->Add(colEmail);

			// Phone
			System::Windows::Forms::DataGridViewTextBoxColumn^ colPhone = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colPhone->Name = L"colPhone";
			colPhone->HeaderText = L"Phone";
			colPhone->FillWeight = 110;
			this->gridSuppliers->Columns->Add(colPhone);

			// Address (short)
			System::Windows::Forms::DataGridViewTextBoxColumn^ colAddr = gcnew System::Windows::Forms::DataGridViewTextBoxColumn();
			colAddr->Name = L"colAddress";
			colAddr->HeaderText = L"Address";
			colAddr->FillWeight = 250;
			this->gridSuppliers->Columns->Add(colAddr);
		}

		// Load suppliers from database via SupplierManager
		void InitializeSuppliers()
		{
			_allSuppliers = gcnew List<SupplierRow^>();

			try
			{
				String^ error = nullptr;
				List<Supplier^>^ dbList = SupplierManager::GetAll(error);

				if (dbList == nullptr)
				{
					if (!String::IsNullOrEmpty(error))
					{
						MessageBox::Show(
							L"Failed to load suppliers:\n" + error,
							L"Suppliers",
							MessageBoxButtons::OK,
							MessageBoxIcon::Error
						);
					}
					return;
				}

				for each (Supplier ^ sup in dbList)
				{
					SupplierRow^ r = gcnew SupplierRow();
					r->Id = sup->Id;
					r->Name = sup->Name;
					r->ContactPerson = sup->ContactName;
					r->Email = sup->Email;
					r->Phone = sup->Phone;
					r->Address = sup->Address;

					_allSuppliers->Add(r);
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(
					L"Unexpected error while loading suppliers:\n" + ex->Message,
					L"Suppliers",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
			}
		}

		void ApplyFilters()
		{
			String^ search = txtSearch->Text->Trim()->ToLower();

			List<SupplierRow^>^ filtered = gcnew List<SupplierRow^>();
			for each (SupplierRow ^ s in _allSuppliers)
			{
				bool matchSearch = (search->Length == 0 ||
					(s->Name != nullptr && s->Name->ToLower()->Contains(search)) ||
					(s->ContactPerson != nullptr && s->ContactPerson->ToLower()->Contains(search)) ||
					(s->Email != nullptr && s->Email->ToLower()->Contains(search)));

				if (matchSearch)
					filtered->Add(s);
			}

			PopulateGrid(filtered);
		}

		void ApplyRolePermissions()
		{
			bool canEdit = Session::IsManager || Session::IsAdministrator;

			btnAdd->Enabled = canEdit;
			btnEdit->Enabled = canEdit;
			btnDelete->Enabled = canEdit;
		}

		void PopulateGrid(List<SupplierRow^>^ rows)
		{
			this->gridSuppliers->Rows->Clear();
			for each (SupplierRow ^ s in rows)
			{
				array<Object^>^ vals = gcnew array<Object^>(6);
				vals[0] = s->Id;
				vals[1] = s->Name;
				vals[2] = s->ContactPerson;
				vals[3] = s->Email;
				vals[4] = s->Phone;
				vals[5] = s->Address;
				this->gridSuppliers->Rows->Add(vals);
			}

			this->gridSuppliers->ClearSelection();
			lblDetailsTitle->Text = L"No supplier selected";
			ClearDetailsInputs();
			btnEdit->Enabled = false;
			btnDelete->Enabled = false;
		}

		void ClearDetailsInputs()
		{
			txtName->Text = L"";
			txtContact->Text = L"";
			txtEmail->Text = L"";
			txtPhone->Text = L"";
			txtAddress->Text = L"";
		}

		// Find supplier by ID in _allSuppliers
		SupplierRow^ FindSupplierById(int id)
		{
			for each (SupplierRow ^ s in _allSuppliers)
			{
				if (s->Id == id) return s;
			}
			return nullptr;
		}

		// Generate next supplier id (simple)
		int NextSupplierId()
		{
			int maxId = 0;
			for each (SupplierRow ^ s in _allSuppliers)
				if (s->Id > maxId) maxId = s->Id;
			return maxId + 1;
		}

		//
		// Event handlers
		//

	private: System::Void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ApplyFilters();
	}

	private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
	{
		InitializeSuppliers();   // reload from database
		ApplyFilters();          // reapply current search filter
	}

	private: System::Void gridSuppliers_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridSuppliers->SelectedRows->Count == 0)
		{
			lblDetailsTitle->Text = L"No supplier selected";
			ClearDetailsInputs();
			btnEdit->Enabled = false;
			btnDelete->Enabled = false;
			return;
		}

		DataGridViewRow^ row = this->gridSuppliers->SelectedRows[0];
		Object^ idv = row->Cells[L"colId"]->Value;
		if (idv == nullptr) return;
		int id = System::Convert::ToInt32(idv);
		SupplierRow^ s = FindSupplierById(id);
		if (s == nullptr) return;

		lblDetailsTitle->Text = String::Format(L"{0} — {1}", s->Name, s->ContactPerson);
		txtName->Text = s->Name;
		txtContact->Text = s->ContactPerson;
		txtEmail->Text = s->Email;
		txtPhone->Text = s->Phone;
		txtAddress->Text = s->Address;

		btnEdit->Enabled = true;
		btnDelete->Enabled = true;
	}

	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
	{
		// Basic validation
		String^ name = txtName->Text->Trim();
		if (String::IsNullOrWhiteSpace(name))
		{
			MessageBox::Show(
				L"Please enter supplier name.",
				L"Validation",
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning
			);
			return;
		}

		// Build Supplier model from UI
		Supplier^ sup = gcnew Supplier();
		sup->Name = name;
		sup->ContactName = txtContact->Text->Trim();
		sup->Email = txtEmail->Text->Trim();
		sup->Phone = txtPhone->Text->Trim();
		sup->Address = txtAddress->Text->Trim();
		// You can later expose Currency / PaymentTerms / Notes on the UI if you want

		try
		{
			String^ error = nullptr;
			bool ok = SupplierManager::CreateSupplier(sup, error);

			if (!ok)
			{
				String^ msg = L"Failed to add supplier.";
				if (!String::IsNullOrEmpty(error))
					msg += L"\n\n" + error;

				MessageBox::Show(
					msg,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
				return;
			}

			// Mirror into our local view-model list
			SupplierRow^ row = gcnew SupplierRow();
			row->Id = sup->Id;                // new DB identity
			row->Name = sup->Name;
			row->ContactPerson = sup->ContactName;
			row->Email = sup->Email;
			row->Phone = sup->Phone;
			row->Address = sup->Address;

			_allSuppliers->Add(row);
			ApplyFilters();

			// Select newly created row in grid
			for each (DataGridViewRow ^ r in this->gridSuppliers->Rows)
			{
				if (r->Cells[L"colId"]->Value != nullptr &&
					System::Convert::ToInt32(r->Cells[L"colId"]->Value) == row->Id)
				{
					r->Selected = true;
					this->gridSuppliers->CurrentCell = r->Cells[1]; // focus name cell
					break;
				}
			}

			MessageBox::Show(
				L"Supplier added.",
				L"Added",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Unexpected error while adding supplier:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void btnEdit_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridSuppliers->SelectedRows->Count == 0)
		{
			MessageBox::Show(L"Select a supplier to save changes.", L"Edit", MessageBoxButtons::OK, MessageBoxIcon::Information);
			return;
		}

		DataGridViewRow^ sel = this->gridSuppliers->SelectedRows[0];
		int id = System::Convert::ToInt32(sel->Cells[L"colId"]->Value);
		SupplierRow^ s = FindSupplierById(id);
		if (s == nullptr) return;

		// Validate
		String^ name = txtName->Text->Trim();
		if (String::IsNullOrWhiteSpace(name))
		{
			MessageBox::Show(L"Supplier name cannot be empty.", L"Validation", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// Prepare new values
		String^ newName = name;
		String^ newContact = txtContact->Text->Trim();
		String^ newEmail = txtEmail->Text->Trim();
		String^ newPhone = txtPhone->Text->Trim();
		String^ newAddress = txtAddress->Text->Trim();

		try
		{
			// Build Supplier model for DB
			Supplier^ sup = gcnew Supplier();
			sup->Id = s->Id;
			sup->Name = newName;
			sup->ContactName = newContact;
			sup->Email = newEmail;
			sup->Phone = newPhone;
			sup->Address = newAddress;

			String^ error = nullptr;
			bool ok = SupplierManager::UpdateSupplier(sup, error);

			if (!ok)
			{
				String^ msg = L"Failed to update supplier.";
				if (!String::IsNullOrEmpty(error))
					msg += L"\n\n" + error;

				MessageBox::Show(
					msg,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
				return;
			}

			// Update in-memory row
			s->Name = newName;
			s->ContactPerson = newContact;
			s->Email = newEmail;
			s->Phone = newPhone;
			s->Address = newAddress;

			// Update grid row
			sel->Cells[L"colName"]->Value = s->Name;
			sel->Cells[L"colContact"]->Value = s->ContactPerson;
			sel->Cells[L"colEmail"]->Value = s->Email;
			sel->Cells[L"colPhone"]->Value = s->Phone;
			sel->Cells[L"colAddress"]->Value = s->Address;

			MessageBox::Show(
				L"Supplier updated.",
				L"Saved",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Unexpected error while updating supplier:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}

	private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->gridSuppliers->SelectedRows->Count == 0)
		{
			MessageBox::Show(
				L"Select a supplier to delete.",
				L"Delete",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			return;
		}

		DataGridViewRow^ sel = this->gridSuppliers->SelectedRows[0];
		int id = System::Convert::ToInt32(sel->Cells[L"colId"]->Value);

		auto result = MessageBox::Show(
			L"Delete selected supplier? This action cannot be undone.",
			L"Delete Supplier",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Warning
		);
		if (result != System::Windows::Forms::DialogResult::Yes)
			return;

		try
		{
			String^ error = nullptr;
			bool ok = SupplierManager::DeleteSupplier(id, error);

			if (!ok)
			{
				String^ msg = L"Failed to delete supplier.";
				if (!String::IsNullOrEmpty(error))
					msg += L"\n\n" + error;

				MessageBox::Show(
					msg,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
				return;
			}

			// Remove from local list
			for (int i = _allSuppliers->Count - 1; i >= 0; --i)
			{
				if (_allSuppliers[i]->Id == id)
				{
					_allSuppliers->RemoveAt(i);
					break;
				}
			}

			ApplyFilters();

			MessageBox::Show(
				L"Supplier deleted.",
				L"Deleted",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(
				L"Unexpected error while deleting supplier:\n" + ex->Message,
				L"Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error
			);
		}
	}
	}; // end class SuppliersForm
} // end namespace IntraProcure
