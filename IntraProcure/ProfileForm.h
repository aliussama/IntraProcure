#pragma once

#include "UiStyler.h"
#include "Session.h"
#include "DatabaseManager.h"
#include "EmployeeManager.h"
#include "Employee.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Security::Cryptography;
	using namespace System::Reflection;
	using namespace System::Resources;
	using System::Drawing::Icon;
	using System::Drawing::Image;

	/// <summary>
	/// ProfileForm – user information & password change
	/// </summary>
	public ref class ProfileForm : public System::Windows::Forms::Form
	{
	public:
		ProfileForm(void)
		{
			InitializeComponent();

			// Apply shared styling

			UiStyler::StyleTextBox(txtConfirmNewPassword);
			UiStyler::StyleTextBox(txtCurrentPassword);
			UiStyler::StyleTextBox(txtNewPassword);
			UiStyler::StylePrimaryButton(btnSaveProfile);
			UiStyler::StylePrimaryButton(btnChangePassword);
			UiStyler::StyleButton(btnClearPic);

			// create ResourceManager for Resource.resx
			_resMgr = gcnew ResourceManager(
				"IntraProcure.Resource",             // <project namespace>.<resx name>
				Assembly::GetExecutingAssembly());

			// read-only identity fields
			txtID->IsReadOnly = true;
			txtUsername->IsReadOnly = true;
			txtRole->IsReadOnly = true;

			lblPasswordStatus->Text = L"";

			InitializeCombos();
			LoadCurrentUser();
		}

	protected:
		~ProfileForm()
		{
			if (components)
				delete components;
		}

	private:
		// Layout
		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
		System::Windows::Forms::Label^ lblTitle;

		SiticoneNetFrameworkUI::SiticonePanel^ panelMain;

		// User info controls

		// Password controls

	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel2;

	private: System::Windows::Forms::Label^ lblFullName;

	private: System::Windows::Forms::Label^ lblEmail;

	private: System::Windows::Forms::Label^ lblDepartment;
	private: System::Windows::Forms::ComboBox^ cmbDepartment;
	private: System::Windows::Forms::Label^ lblRole;

	private: SiticoneNetFrameworkUI::SiticoneButton^ btnSaveProfile;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtEmail;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtFullName;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtRole;

	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtPhone;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::CheckBox^ chkShowPassword;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnChangePassword;
	private: SiticoneNetFrameworkUI::SiticoneVSeparator^ siticoneVSeparator1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ cmbCountry;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ cmbCity;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtWorkAddress;

	private: System::Windows::Forms::Label^ label7;

	private: System::Windows::Forms::Label^ label5;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtUsername;

	private: System::Windows::Forms::Label^ label6;
	private: SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced^ txtID;

	private: System::Windows::Forms::Label^ lblPasswordStatus;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtCurrentPassword;
	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtConfirmNewPassword;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtNewPassword;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: SiticoneNetFrameworkUI::SiticoneAvatar^ picUser;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnClearPic;

		   System::ComponentModel::Container^ components;

		   ResourceManager^ _resMgr;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ProfileForm::typeid));
			   this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->lblTitle = (gcnew System::Windows::Forms::Label());
			   this->panelMain = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			   this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			   this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			   this->btnClearPic = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->picUser = (gcnew SiticoneNetFrameworkUI::SiticoneAvatar());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->txtUsername = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->txtID = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->txtWorkAddress = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->cmbCountry = (gcnew System::Windows::Forms::ComboBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->cmbCity = (gcnew System::Windows::Forms::ComboBox());
			   this->siticoneVSeparator1 = (gcnew SiticoneNetFrameworkUI::SiticoneVSeparator());
			   this->txtPhone = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->txtRole = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblFullName = (gcnew System::Windows::Forms::Label());
			   this->txtEmail = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblEmail = (gcnew System::Windows::Forms::Label());
			   this->txtFullName = (gcnew SiticoneNetFrameworkUI::SiticoneTextBoxAdvanced());
			   this->lblDepartment = (gcnew System::Windows::Forms::Label());
			   this->cmbDepartment = (gcnew System::Windows::Forms::ComboBox());
			   this->lblRole = (gcnew System::Windows::Forms::Label());
			   this->btnSaveProfile = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->siticonePanel2 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			   this->txtConfirmNewPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			   this->txtNewPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			   this->txtCurrentPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			   this->lblPasswordStatus = (gcnew System::Windows::Forms::Label());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->label10 = (gcnew System::Windows::Forms::Label());
			   this->chkShowPassword = (gcnew System::Windows::Forms::CheckBox());
			   this->btnChangePassword = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelHeader->SuspendLayout();
			   this->panelMain->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			   this->splitContainer1->Panel1->SuspendLayout();
			   this->splitContainer1->Panel2->SuspendLayout();
			   this->splitContainer1->SuspendLayout();
			   this->siticonePanel1->SuspendLayout();
			   this->siticonePanel2->SuspendLayout();
			   this->SuspendLayout();
			   //
			   // panelHeader
			   //
			   this->panelHeader->BackColor = System::Drawing::Color::White;
			   this->panelHeader->Controls->Add(this->lblTitle);
			   this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			   this->panelHeader->Location = System::Drawing::Point(0, 0);
			   this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelHeader->Name = L"panelHeader";
			   this->panelHeader->Size = System::Drawing::Size(916, 50);
			   this->panelHeader->TabIndex = 0;
			   //
			   // lblTitle
			   //
			   this->lblTitle->AutoSize = true;
			   this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			   this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->lblTitle->Location = System::Drawing::Point(18, 14);
			   this->lblTitle->Name = L"lblTitle";
			   this->lblTitle->Size = System::Drawing::Size(71, 25);
			   this->lblTitle->TabIndex = 0;
			   this->lblTitle->Text = L"Profile";
			   //
			   // panelMain
			   //
			   this->panelMain->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelMain->BackColor = System::Drawing::Color::Transparent;
			   this->panelMain->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			   this->panelMain->BorderDashPattern = nullptr;
			   this->panelMain->BorderGradientEndColor = System::Drawing::Color::Gray;
			   this->panelMain->BorderGradientStartColor = System::Drawing::Color::Gray;
			   this->panelMain->BorderThickness = 2;
			   this->panelMain->Controls->Add(this->splitContainer1);
			   this->panelMain->CornerRadiusBottomLeft = 5;
			   this->panelMain->CornerRadiusBottomRight = 5;
			   this->panelMain->CornerRadiusTopLeft = 5;
			   this->panelMain->CornerRadiusTopRight = 5;
			   this->panelMain->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panelMain->EnableAcrylicEffect = false;
			   this->panelMain->EnableMicaEffect = false;
			   this->panelMain->EnableRippleEffect = false;
			   this->panelMain->FillColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->panelMain->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				   System::Drawing::Color::White, System::Drawing::Color::LightGray,
					   System::Drawing::Color::Gray
			   };
			   this->panelMain->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			   this->panelMain->Location = System::Drawing::Point(0, 50);
			   this->panelMain->Name = L"panelMain";
			   this->panelMain->Padding = System::Windows::Forms::Padding(5);
			   this->panelMain->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			   this->panelMain->RippleAlpha = 50;
			   this->panelMain->RippleAlphaDecrement = 3;
			   this->panelMain->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->panelMain->RippleMaxSize = 600;
			   this->panelMain->RippleSpeed = 15;
			   this->panelMain->ShowBorder = true;
			   this->panelMain->Size = System::Drawing::Size(916, 493);
			   this->panelMain->TabIndex = 1;
			   this->panelMain->TabStop = true;
			   this->panelMain->TrackSystemTheme = false;
			   this->panelMain->UseBorderGradient = true;
			   this->panelMain->UseMultiGradient = false;
			   this->panelMain->UsePatternTexture = false;
			   this->panelMain->UseRadialGradient = false;
			   //
			   // splitContainer1
			   //
			   this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->splitContainer1->Location = System::Drawing::Point(2, 2);
			   this->splitContainer1->Name = L"splitContainer1";
			   //
			   // splitContainer1.Panel1
			   //
			   this->splitContainer1->Panel1->Controls->Add(this->siticonePanel1);
			   //
			   // splitContainer1.Panel2
			   //
			   this->splitContainer1->Panel2->Controls->Add(this->siticonePanel2);
			   this->splitContainer1->Size = System::Drawing::Size(911, 489);
			   this->splitContainer1->SplitterDistance = 600;
			   this->splitContainer1->TabIndex = 4;
			   //
			   // siticonePanel1
			   //
			   this->siticonePanel1->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel1->BackColor = System::Drawing::Color::Transparent;
			   this->siticonePanel1->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			   this->siticonePanel1->BorderDashPattern = nullptr;
			   this->siticonePanel1->BorderGradientEndColor = System::Drawing::Color::Purple;
			   this->siticonePanel1->BorderGradientStartColor = System::Drawing::Color::Blue;
			   this->siticonePanel1->BorderThickness = 2;
			   this->siticonePanel1->Controls->Add(this->btnClearPic);
			   this->siticonePanel1->Controls->Add(this->picUser);
			   this->siticonePanel1->Controls->Add(this->label5);
			   this->siticonePanel1->Controls->Add(this->txtUsername);
			   this->siticonePanel1->Controls->Add(this->label6);
			   this->siticonePanel1->Controls->Add(this->txtID);
			   this->siticonePanel1->Controls->Add(this->txtWorkAddress);
			   this->siticonePanel1->Controls->Add(this->label7);
			   this->siticonePanel1->Controls->Add(this->label2);
			   this->siticonePanel1->Controls->Add(this->cmbCountry);
			   this->siticonePanel1->Controls->Add(this->label1);
			   this->siticonePanel1->Controls->Add(this->cmbCity);
			   this->siticonePanel1->Controls->Add(this->siticoneVSeparator1);
			   this->siticonePanel1->Controls->Add(this->txtPhone);
			   this->siticonePanel1->Controls->Add(this->label3);
			   this->siticonePanel1->Controls->Add(this->txtRole);
			   this->siticonePanel1->Controls->Add(this->lblFullName);
			   this->siticonePanel1->Controls->Add(this->txtEmail);
			   this->siticonePanel1->Controls->Add(this->lblEmail);
			   this->siticonePanel1->Controls->Add(this->txtFullName);
			   this->siticonePanel1->Controls->Add(this->lblDepartment);
			   this->siticonePanel1->Controls->Add(this->cmbDepartment);
			   this->siticonePanel1->Controls->Add(this->lblRole);
			   this->siticonePanel1->Controls->Add(this->btnSaveProfile);
			   this->siticonePanel1->CornerRadiusBottomLeft = 0;
			   this->siticonePanel1->CornerRadiusBottomRight = 10;
			   this->siticonePanel1->CornerRadiusTopLeft = 0;
			   this->siticonePanel1->CornerRadiusTopRight = 10;
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
			   this->siticonePanel1->Location = System::Drawing::Point(0, 0);
			   this->siticonePanel1->Name = L"siticonePanel1";
			   this->siticonePanel1->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			   this->siticonePanel1->RippleAlpha = 50;
			   this->siticonePanel1->RippleAlphaDecrement = 3;
			   this->siticonePanel1->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel1->RippleMaxSize = 600;
			   this->siticonePanel1->RippleSpeed = 15;
			   this->siticonePanel1->ShowBorder = false;
			   this->siticonePanel1->Size = System::Drawing::Size(600, 489);
			   this->siticonePanel1->TabIndex = 2;
			   this->siticonePanel1->TabStop = true;
			   this->siticonePanel1->TrackSystemTheme = false;
			   this->siticonePanel1->UseBorderGradient = false;
			   this->siticonePanel1->UseMultiGradient = false;
			   this->siticonePanel1->UsePatternTexture = false;
			   this->siticonePanel1->UseRadialGradient = false;
			   //
			   // btnClearPic
			   //
			   this->btnClearPic->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnClearPic->AccessibleName = L"Clear Picture";
			   this->btnClearPic->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->btnClearPic->AutoSizeBasedOnText = false;
			   this->btnClearPic->BackColor = System::Drawing::Color::Transparent;
			   this->btnClearPic->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnClearPic->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnClearPic->BadgeValue = 0;
			   this->btnClearPic->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnClearPic->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				   static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnClearPic->BorderWidth = 1;
			   this->btnClearPic->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnClearPic->ButtonImage = nullptr;
			   this->btnClearPic->ButtonTextLeftPadding = 0;
			   this->btnClearPic->CanBeep = true;
			   this->btnClearPic->CanGlow = false;
			   this->btnClearPic->CanShake = true;
			   this->btnClearPic->ContextMenuStripEx = nullptr;
			   this->btnClearPic->CornerRadiusBottomLeft = 10;
			   this->btnClearPic->CornerRadiusBottomRight = 10;
			   this->btnClearPic->CornerRadiusTopLeft = 10;
			   this->btnClearPic->CornerRadiusTopRight = 10;
			   this->btnClearPic->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnClearPic->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnClearPic->EnableLongPress = false;
			   this->btnClearPic->EnableRippleEffect = true;
			   this->btnClearPic->EnableShadow = false;
			   this->btnClearPic->EnableTextWrapping = false;
			   this->btnClearPic->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			   this->btnClearPic->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnClearPic->GlowIntensity = 100;
			   this->btnClearPic->GlowRadius = 20;
			   this->btnClearPic->GradientBackground = false;
			   this->btnClearPic->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnClearPic->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnClearPic->HintText = nullptr;
			   this->btnClearPic->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnClearPic->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClearPic->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClearPic->HoverTransitionDuration = 250;
			   this->btnClearPic->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnClearPic->ImagePadding = 5;
			   this->btnClearPic->ImageSize = System::Drawing::Size(16, 16);
			   this->btnClearPic->IsRadial = false;
			   this->btnClearPic->IsReadOnly = false;
			   this->btnClearPic->IsToggleButton = false;
			   this->btnClearPic->IsToggled = false;
			   this->btnClearPic->Location = System::Drawing::Point(210, 15);
			   this->btnClearPic->LongPressDurationMS = 1000;
			   this->btnClearPic->Name = L"btnClearPic";
			   this->btnClearPic->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClearPic->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnClearPic->ParticleCount = 15;
			   this->btnClearPic->PressAnimationScale = 0.97F;
			   this->btnClearPic->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnClearPic->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnClearPic->PressTransitionDuration = 150;
			   this->btnClearPic->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnClearPic->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClearPic->RippleRadiusMultiplier = 0.6F;
			   this->btnClearPic->ShadowBlur = 5;
			   this->btnClearPic->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClearPic->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnClearPic->ShakeDuration = 500;
			   this->btnClearPic->ShakeIntensity = 5;
			   this->btnClearPic->Size = System::Drawing::Size(81, 21);
			   this->btnClearPic->TabIndex = 43;
			   this->btnClearPic->Text = L"Clear Picture";
			   this->btnClearPic->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnClearPic->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnClearPic->TooltipText = nullptr;
			   this->btnClearPic->UseAdvancedRendering = true;
			   this->btnClearPic->UseParticles = false;
			   this->btnClearPic->Click += gcnew System::EventHandler(this, &ProfileForm::btnClearPic_Click);
			   //
			   // picUser
			   //
			   this->picUser->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->picUser->BorderColor = System::Drawing::Color::White;
			   this->picUser->BorderThickness = 1;
			   this->picUser->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->picUser->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picUser.Image")));
			   this->picUser->Location = System::Drawing::Point(90, 15);
			   this->picUser->Margin = 0;
			   this->picUser->Name = L"picUser";
			   this->picUser->Size = System::Drawing::Size(120, 120);
			   this->picUser->TabIndex = 42;
			   this->picUser->TintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				   static_cast<System::Int32>(static_cast<System::Byte>(130)), static_cast<System::Int32>(static_cast<System::Byte>(180)));
			   this->picUser->Click += gcnew System::EventHandler(this, &ProfileForm::picUser_Click);
			   //
			   // label5
			   //
			   this->label5->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label5->AutoSize = true;
			   this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label5->Location = System::Drawing::Point(315, 159);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(67, 13);
			   this->label5->TabIndex = 36;
			   this->label5->Text = L"Employee ID";
			   //
			   // txtUsername
			   //
			   this->txtUsername->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtUsername->BackColor = System::Drawing::Color::Transparent;
			   this->txtUsername->BackgroundColor = System::Drawing::Color::White;
			   this->txtUsername->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtUsername->Cursor = System::Windows::Forms::Cursors::No;
			   this->txtUsername->Enabled = false;
			   this->txtUsername->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtUsername->FocusImage = nullptr;
			   this->txtUsername->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtUsername->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)),
				   static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtUsername->HoverImage = nullptr;
			   this->txtUsername->IdleImage = nullptr;
			   this->txtUsername->IsReadOnly = true;
			   this->txtUsername->Location = System::Drawing::Point(318, 231);
			   this->txtUsername->Name = L"txtUsername";
			   this->txtUsername->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtUsername->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtUsername->PlaceholderText = L"";
			   this->txtUsername->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtUsername->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtUsername->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtUsername->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtUsername->Size = System::Drawing::Size(248, 25);
			   this->txtUsername->TabIndex = 39;
			   this->txtUsername->TabStop = false;
			   this->txtUsername->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtUsername->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtUsername->TextContent = L"";
			   this->txtUsername->ValidationPattern = L"";
			   //
			   // label6
			   //
			   this->label6->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label6->AutoSize = true;
			   this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label6->Location = System::Drawing::Point(315, 214);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(55, 13);
			   this->label6->TabIndex = 37;
			   this->label6->Text = L"Username";
			   //
			   // txtID
			   //
			   this->txtID->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtID->BackColor = System::Drawing::Color::Transparent;
			   this->txtID->BackgroundColor = System::Drawing::Color::White;
			   this->txtID->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtID->Cursor = System::Windows::Forms::Cursors::No;
			   this->txtID->Enabled = false;
			   this->txtID->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtID->FocusImage = nullptr;
			   this->txtID->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtID->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtID->HoverImage = nullptr;
			   this->txtID->IdleImage = nullptr;
			   this->txtID->IsReadOnly = true;
			   this->txtID->Location = System::Drawing::Point(318, 176);
			   this->txtID->Name = L"txtID";
			   this->txtID->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtID->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtID->PlaceholderText = L"";
			   this->txtID->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtID->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtID->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtID->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtID->Size = System::Drawing::Size(248, 25);
			   this->txtID->TabIndex = 38;
			   this->txtID->TabStop = false;
			   this->txtID->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtID->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtID->TextContent = L"";
			   this->txtID->ValidationPattern = L"";
			   //
			   // txtWorkAddress
			   //
			   this->txtWorkAddress->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtWorkAddress->BackColor = System::Drawing::Color::Transparent;
			   this->txtWorkAddress->BackgroundColor = System::Drawing::Color::White;
			   this->txtWorkAddress->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtWorkAddress->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtWorkAddress->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtWorkAddress->FocusImage = nullptr;
			   this->txtWorkAddress->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtWorkAddress->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)),
				   static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtWorkAddress->HoverImage = nullptr;
			   this->txtWorkAddress->IdleImage = nullptr;
			   this->txtWorkAddress->Location = System::Drawing::Point(318, 286);
			   this->txtWorkAddress->Name = L"txtWorkAddress";
			   this->txtWorkAddress->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtWorkAddress->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtWorkAddress->PlaceholderText = L"";
			   this->txtWorkAddress->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtWorkAddress->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtWorkAddress->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtWorkAddress->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtWorkAddress->Size = System::Drawing::Size(248, 25);
			   this->txtWorkAddress->TabIndex = 7;
			   this->txtWorkAddress->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtWorkAddress->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtWorkAddress->TextContent = L"";
			   this->txtWorkAddress->ValidationPattern = L"";
			   //
			   // label7
			   //
			   this->label7->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label7->AutoSize = true;
			   this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label7->Location = System::Drawing::Point(315, 269);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(74, 13);
			   this->label7->TabIndex = 34;
			   this->label7->Text = L"Work Address";
			   //
			   // label2
			   //
			   this->label2->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label2->AutoSize = true;
			   this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label2->Location = System::Drawing::Point(20, 379);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(43, 13);
			   this->label2->TabIndex = 26;
			   this->label2->Text = L"Country";
			   //
			   // cmbCountry
			   //
			   this->cmbCountry->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->cmbCountry->BackColor = System::Drawing::Color::White;
			   this->cmbCountry->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->cmbCountry->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->cmbCountry->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->cmbCountry->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->cmbCountry->FormattingEnabled = true;
			   this->cmbCountry->Location = System::Drawing::Point(23, 396);
			   this->cmbCountry->Name = L"cmbCountry";
			   this->cmbCountry->Size = System::Drawing::Size(248, 23);
			   this->cmbCountry->TabIndex = 5;
			   //
			   // label1
			   //
			   this->label1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label1->AutoSize = true;
			   this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label1->Location = System::Drawing::Point(20, 324);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(24, 13);
			   this->label1->TabIndex = 24;
			   this->label1->Text = L"City";
			   //
			   // cmbCity
			   //
			   this->cmbCity->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->cmbCity->BackColor = System::Drawing::Color::White;
			   this->cmbCity->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->cmbCity->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->cmbCity->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->cmbCity->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->cmbCity->FormattingEnabled = true;
			   this->cmbCity->Location = System::Drawing::Point(23, 341);
			   this->cmbCity->Name = L"cmbCity";
			   this->cmbCity->Size = System::Drawing::Size(248, 23);
			   this->cmbCity->TabIndex = 4;
			   //
			   // siticoneVSeparator1
			   //
			   this->siticoneVSeparator1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			   this->siticoneVSeparator1->BackColor = System::Drawing::Color::Transparent;
			   this->siticoneVSeparator1->GradientEndColor = System::Drawing::Color::DarkGray;
			   this->siticoneVSeparator1->GradientMode = SiticoneNetFrameworkUI::SiticoneVSeparator::LinearGradientMode::None;
			   this->siticoneVSeparator1->GradientStartColor = System::Drawing::Color::LightGray;
			   this->siticoneVSeparator1->LineColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)),
				   static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(223)));
			   this->siticoneVSeparator1->LineWidth = 1;
			   this->siticoneVSeparator1->Location = System::Drawing::Point(290, 25);
			   this->siticoneVSeparator1->Name = L"siticoneVSeparator1";
			   this->siticoneVSeparator1->ParallelLines = 1;
			   this->siticoneVSeparator1->ParallelLineSpacing = 4;
			   this->siticoneVSeparator1->SegmentNumberColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->siticoneVSeparator1->SegmentNumberFont = (gcnew System::Drawing::Font(L"Segoe UI", 8));
			   this->siticoneVSeparator1->Segments = 1;
			   this->siticoneVSeparator1->SegmentSpacing = 10;
			   this->siticoneVSeparator1->SeparatorDashStyle = SiticoneNetFrameworkUI::SiticoneVSeparator::CustomDashStyle::Solid;
			   this->siticoneVSeparator1->ShowSegmentNumbers = false;
			   this->siticoneVSeparator1->Size = System::Drawing::Size(10, 441);
			   this->siticoneVSeparator1->TabIndex = 23;
			   this->siticoneVSeparator1->Text = L"siticoneVSeparator1";
			   this->siticoneVSeparator1->UltraFastMode = true;
			   //
			   // txtPhone
			   //
			   this->txtPhone->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtPhone->BackColor = System::Drawing::Color::Transparent;
			   this->txtPhone->BackgroundColor = System::Drawing::Color::White;
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
			   this->txtPhone->Location = System::Drawing::Point(23, 286);
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
			   this->txtPhone->Size = System::Drawing::Size(248, 25);
			   this->txtPhone->TabIndex = 3;
			   this->txtPhone->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtPhone->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtPhone->TextContent = L"";
			   this->txtPhone->ValidationPattern = L"";
			   //
			   // label3
			   //
			   this->label3->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label3->AutoSize = true;
			   this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label3->Location = System::Drawing::Point(20, 269);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(78, 13);
			   this->label3->TabIndex = 21;
			   this->label3->Text = L"Phone Number";
			   //
			   // txtRole
			   //
			   this->txtRole->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtRole->BackColor = System::Drawing::Color::Transparent;
			   this->txtRole->BackgroundColor = System::Drawing::Color::White;
			   this->txtRole->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtRole->Cursor = System::Windows::Forms::Cursors::No;
			   this->txtRole->Enabled = false;
			   this->txtRole->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtRole->FocusImage = nullptr;
			   this->txtRole->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtRole->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				   static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtRole->HoverImage = nullptr;
			   this->txtRole->IdleImage = nullptr;
			   this->txtRole->IsReadOnly = true;
			   this->txtRole->Location = System::Drawing::Point(321, 395);
			   this->txtRole->Name = L"txtRole";
			   this->txtRole->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtRole->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtRole->PlaceholderText = L"";
			   this->txtRole->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtRole->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtRole->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtRole->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtRole->Size = System::Drawing::Size(248, 25);
			   this->txtRole->TabIndex = 17;
			   this->txtRole->TabStop = false;
			   this->txtRole->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtRole->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtRole->TextContent = L"";
			   this->txtRole->ValidationPattern = L"";
			   //
			   // lblFullName
			   //
			   this->lblFullName->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblFullName->AutoSize = true;
			   this->lblFullName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->lblFullName->Location = System::Drawing::Point(20, 159);
			   this->lblFullName->Name = L"lblFullName";
			   this->lblFullName->Size = System::Drawing::Size(54, 13);
			   this->lblFullName->TabIndex = 5;
			   this->lblFullName->Text = L"Full Name";
			   //
			   // txtEmail
			   //
			   this->txtEmail->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtEmail->BackColor = System::Drawing::Color::Transparent;
			   this->txtEmail->BackgroundColor = System::Drawing::Color::White;
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
			   this->txtEmail->Location = System::Drawing::Point(23, 231);
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
			   this->txtEmail->Size = System::Drawing::Size(248, 25);
			   this->txtEmail->TabIndex = 2;
			   this->txtEmail->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtEmail->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtEmail->TextContent = L"";
			   this->txtEmail->ValidationPattern = L"";
			   //
			   // lblEmail
			   //
			   this->lblEmail->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblEmail->AutoSize = true;
			   this->lblEmail->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->lblEmail->Location = System::Drawing::Point(20, 214);
			   this->lblEmail->Name = L"lblEmail";
			   this->lblEmail->Size = System::Drawing::Size(32, 13);
			   this->lblEmail->TabIndex = 7;
			   this->lblEmail->Text = L"Email";
			   //
			   // txtFullName
			   //
			   this->txtFullName->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtFullName->BackColor = System::Drawing::Color::Transparent;
			   this->txtFullName->BackgroundColor = System::Drawing::Color::White;
			   this->txtFullName->BorderColor = System::Drawing::Color::DarkGray;
			   this->txtFullName->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtFullName->FocusBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtFullName->FocusImage = nullptr;
			   this->txtFullName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtFullName->HoverBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(149)),
				   static_cast<System::Int32>(static_cast<System::Byte>(165)), static_cast<System::Int32>(static_cast<System::Byte>(166)));
			   this->txtFullName->HoverImage = nullptr;
			   this->txtFullName->IdleImage = nullptr;
			   this->txtFullName->Location = System::Drawing::Point(23, 176);
			   this->txtFullName->Name = L"txtFullName";
			   this->txtFullName->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(117)),
				   static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(117)));
			   this->txtFullName->PlaceholderFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			   this->txtFullName->PlaceholderText = L"";
			   this->txtFullName->ReadOnlyColors->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(245)));
			   this->txtFullName->ReadOnlyColors->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->txtFullName->ReadOnlyColors->PlaceholderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->txtFullName->ReadOnlyColors->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->txtFullName->Size = System::Drawing::Size(248, 25);
			   this->txtFullName->TabIndex = 1;
			   this->txtFullName->TextBoxType = SiticoneNetFrameworkUI::TextBoxType::Material;
			   this->txtFullName->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->txtFullName->TextContent = L"";
			   this->txtFullName->ValidationPattern = L"";
			   //
			   // lblDepartment
			   //
			   this->lblDepartment->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblDepartment->AutoSize = true;
			   this->lblDepartment->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->lblDepartment->Location = System::Drawing::Point(318, 324);
			   this->lblDepartment->Name = L"lblDepartment";
			   this->lblDepartment->Size = System::Drawing::Size(62, 13);
			   this->lblDepartment->TabIndex = 9;
			   this->lblDepartment->Text = L"Department";
			   //
			   // cmbDepartment
			   //
			   this->cmbDepartment->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->cmbDepartment->BackColor = System::Drawing::Color::White;
			   this->cmbDepartment->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			   this->cmbDepartment->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->cmbDepartment->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->cmbDepartment->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->cmbDepartment->FormattingEnabled = true;
			   this->cmbDepartment->Location = System::Drawing::Point(321, 340);
			   this->cmbDepartment->Name = L"cmbDepartment";
			   this->cmbDepartment->Size = System::Drawing::Size(248, 23);
			   this->cmbDepartment->TabIndex = 8;
			   //
			   // lblRole
			   //
			   this->lblRole->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblRole->AutoSize = true;
			   this->lblRole->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->lblRole->Location = System::Drawing::Point(318, 381);
			   this->lblRole->Name = L"lblRole";
			   this->lblRole->Size = System::Drawing::Size(29, 13);
			   this->lblRole->TabIndex = 11;
			   this->lblRole->Text = L"Role";
			   //
			   // btnSaveProfile
			   //
			   this->btnSaveProfile->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnSaveProfile->AccessibleName = L"Save Changes";
			   this->btnSaveProfile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnSaveProfile->AutoSizeBasedOnText = false;
			   this->btnSaveProfile->BackColor = System::Drawing::Color::Transparent;
			   this->btnSaveProfile->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnSaveProfile->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnSaveProfile->BadgeValue = 0;
			   this->btnSaveProfile->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnSaveProfile->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)),
				   static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnSaveProfile->BorderWidth = 1;
			   this->btnSaveProfile->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnSaveProfile->ButtonImage = nullptr;
			   this->btnSaveProfile->ButtonTextLeftPadding = 0;
			   this->btnSaveProfile->CanBeep = true;
			   this->btnSaveProfile->CanGlow = false;
			   this->btnSaveProfile->CanShake = true;
			   this->btnSaveProfile->ContextMenuStripEx = nullptr;
			   this->btnSaveProfile->CornerRadiusBottomLeft = 6;
			   this->btnSaveProfile->CornerRadiusBottomRight = 6;
			   this->btnSaveProfile->CornerRadiusTopLeft = 6;
			   this->btnSaveProfile->CornerRadiusTopRight = 6;
			   this->btnSaveProfile->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnSaveProfile->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnSaveProfile->EnableLongPress = false;
			   this->btnSaveProfile->EnableRippleEffect = true;
			   this->btnSaveProfile->EnableShadow = false;
			   this->btnSaveProfile->EnableTextWrapping = false;
			   this->btnSaveProfile->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnSaveProfile->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnSaveProfile->GlowIntensity = 100;
			   this->btnSaveProfile->GlowRadius = 20;
			   this->btnSaveProfile->GradientBackground = false;
			   this->btnSaveProfile->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnSaveProfile->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnSaveProfile->HintText = nullptr;
			   this->btnSaveProfile->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnSaveProfile->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSaveProfile->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnSaveProfile->HoverTransitionDuration = 250;
			   this->btnSaveProfile->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnSaveProfile->ImagePadding = 5;
			   this->btnSaveProfile->ImageSize = System::Drawing::Size(16, 16);
			   this->btnSaveProfile->IsRadial = false;
			   this->btnSaveProfile->IsReadOnly = false;
			   this->btnSaveProfile->IsToggleButton = false;
			   this->btnSaveProfile->IsToggled = false;
			   this->btnSaveProfile->Location = System::Drawing::Point(455, 450);
			   this->btnSaveProfile->LongPressDurationMS = 1000;
			   this->btnSaveProfile->Name = L"btnSaveProfile";
			   this->btnSaveProfile->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSaveProfile->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnSaveProfile->ParticleCount = 15;
			   this->btnSaveProfile->PressAnimationScale = 0.97F;
			   this->btnSaveProfile->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnSaveProfile->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSaveProfile->PressTransitionDuration = 150;
			   this->btnSaveProfile->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnSaveProfile->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnSaveProfile->RippleRadiusMultiplier = 0.6F;
			   this->btnSaveProfile->ShadowBlur = 5;
			   this->btnSaveProfile->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnSaveProfile->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnSaveProfile->ShakeDuration = 500;
			   this->btnSaveProfile->ShakeIntensity = 5;
			   this->btnSaveProfile->Size = System::Drawing::Size(130, 30);
			   this->btnSaveProfile->TabIndex = 9;
			   this->btnSaveProfile->Text = L"Save Changes";
			   this->btnSaveProfile->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnSaveProfile->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnSaveProfile->TooltipText = nullptr;
			   this->btnSaveProfile->UseAdvancedRendering = true;
			   this->btnSaveProfile->UseParticles = false;
			   this->btnSaveProfile->Click += gcnew System::EventHandler(this, &ProfileForm::btnSaveProfile_Click);
			   //
			   // siticonePanel2
			   //
			   this->siticonePanel2->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel2->BackColor = System::Drawing::Color::Transparent;
			   this->siticonePanel2->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			   this->siticonePanel2->BorderDashPattern = nullptr;
			   this->siticonePanel2->BorderGradientEndColor = System::Drawing::Color::Purple;
			   this->siticonePanel2->BorderGradientStartColor = System::Drawing::Color::Blue;
			   this->siticonePanel2->BorderThickness = 2;
			   this->siticonePanel2->Controls->Add(this->txtConfirmNewPassword);
			   this->siticonePanel2->Controls->Add(this->txtNewPassword);
			   this->siticonePanel2->Controls->Add(this->txtCurrentPassword);
			   this->siticonePanel2->Controls->Add(this->lblPasswordStatus);
			   this->siticonePanel2->Controls->Add(this->label8);
			   this->siticonePanel2->Controls->Add(this->label9);
			   this->siticonePanel2->Controls->Add(this->label10);
			   this->siticonePanel2->Controls->Add(this->chkShowPassword);
			   this->siticonePanel2->Controls->Add(this->btnChangePassword);
			   this->siticonePanel2->CornerRadiusBottomLeft = 10;
			   this->siticonePanel2->CornerRadiusBottomRight = 0;
			   this->siticonePanel2->CornerRadiusTopLeft = 10;
			   this->siticonePanel2->CornerRadiusTopRight = 0;
			   this->siticonePanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->siticonePanel2->EnableAcrylicEffect = false;
			   this->siticonePanel2->EnableMicaEffect = false;
			   this->siticonePanel2->EnableRippleEffect = false;
			   this->siticonePanel2->FillColor = System::Drawing::Color::White;
			   this->siticonePanel2->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				   System::Drawing::Color::White, System::Drawing::Color::LightGray,
					   System::Drawing::Color::Gray
			   };
			   this->siticonePanel2->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			   this->siticonePanel2->Location = System::Drawing::Point(0, 0);
			   this->siticonePanel2->Name = L"siticonePanel2";
			   this->siticonePanel2->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			   this->siticonePanel2->RippleAlpha = 50;
			   this->siticonePanel2->RippleAlphaDecrement = 3;
			   this->siticonePanel2->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->siticonePanel2->RippleMaxSize = 600;
			   this->siticonePanel2->RippleSpeed = 15;
			   this->siticonePanel2->ShowBorder = false;
			   this->siticonePanel2->Size = System::Drawing::Size(307, 489);
			   this->siticonePanel2->TabIndex = 3;
			   this->siticonePanel2->TabStop = true;
			   this->siticonePanel2->TrackSystemTheme = false;
			   this->siticonePanel2->UseBorderGradient = false;
			   this->siticonePanel2->UseMultiGradient = false;
			   this->siticonePanel2->UsePatternTexture = false;
			   this->siticonePanel2->UseRadialGradient = false;
			   //
			   // txtConfirmNewPassword
			   //
			   this->txtConfirmNewPassword->AccessibleDescription = L"A customizable text input field.";
			   this->txtConfirmNewPassword->AccessibleName = L"Text Box";
			   this->txtConfirmNewPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			   this->txtConfirmNewPassword->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtConfirmNewPassword->BackColor = System::Drawing::Color::Transparent;
			   this->txtConfirmNewPassword->BlinkCount = 3;
			   this->txtConfirmNewPassword->BlinkShadow = false;
			   this->txtConfirmNewPassword->BorderColor1 = System::Drawing::Color::DarkGray;
			   this->txtConfirmNewPassword->BorderColor2 = System::Drawing::Color::DarkGray;
			   this->txtConfirmNewPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtConfirmNewPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtConfirmNewPassword->CanShake = true;
			   this->txtConfirmNewPassword->ContinuousBlink = false;
			   this->txtConfirmNewPassword->CornerRadiusBottomLeft = 5;
			   this->txtConfirmNewPassword->CornerRadiusBottomRight = 5;
			   this->txtConfirmNewPassword->CornerRadiusTopLeft = 5;
			   this->txtConfirmNewPassword->CornerRadiusTopRight = 5;
			   this->txtConfirmNewPassword->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtConfirmNewPassword->CursorBlinkRate = 500;
			   this->txtConfirmNewPassword->CursorColor = System::Drawing::Color::Black;
			   this->txtConfirmNewPassword->CursorHeight = 26;
			   this->txtConfirmNewPassword->CursorOffset = 0;
			   this->txtConfirmNewPassword->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			   this->txtConfirmNewPassword->CursorWidth = 1;
			   this->txtConfirmNewPassword->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			   this->txtConfirmNewPassword->DisabledBorderColor = System::Drawing::Color::LightGray;
			   this->txtConfirmNewPassword->DisabledTextColor = System::Drawing::Color::Gray;
			   this->txtConfirmNewPassword->EnableDropShadow = false;
			   this->txtConfirmNewPassword->FillColor1 = System::Drawing::Color::White;
			   this->txtConfirmNewPassword->FillColor2 = System::Drawing::Color::White;
			   this->txtConfirmNewPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.5F));
			   this->txtConfirmNewPassword->ForeColor = System::Drawing::Color::DimGray;
			   this->txtConfirmNewPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			   this->txtConfirmNewPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			   this->txtConfirmNewPassword->IsEnabled = true;
			   this->txtConfirmNewPassword->Location = System::Drawing::Point(21, 286);
			   this->txtConfirmNewPassword->MaxLength = 50;
			   this->txtConfirmNewPassword->Name = L"txtConfirmNewPassword";
			   this->txtConfirmNewPassword->PlaceholderColor = System::Drawing::Color::Gray;
			   this->txtConfirmNewPassword->PlaceholderText = L"Confirm Password...";
			   this->txtConfirmNewPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			   this->txtConfirmNewPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			   this->txtConfirmNewPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			   this->txtConfirmNewPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			   this->txtConfirmNewPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			   this->txtConfirmNewPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				   static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->txtConfirmNewPassword->ShadowAnimationDuration = 1;
			   this->txtConfirmNewPassword->ShadowBlur = 10;
			   this->txtConfirmNewPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->txtConfirmNewPassword->Size = System::Drawing::Size(248, 25);
			   this->txtConfirmNewPassword->SolidBorderColor = System::Drawing::Color::DarkGray;
			   this->txtConfirmNewPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtConfirmNewPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			   this->txtConfirmNewPassword->SolidFillColor = System::Drawing::Color::White;
			   this->txtConfirmNewPassword->TabIndex = 12;
			   this->txtConfirmNewPassword->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			   this->txtConfirmNewPassword->UseSystemPasswordChar = true;
			   this->txtConfirmNewPassword->ValidationErrorMessage = L"Invalid input.";
			   this->txtConfirmNewPassword->ValidationFunction = nullptr;
			   //
			   // txtNewPassword
			   //
			   this->txtNewPassword->AccessibleDescription = L"A customizable text input field.";
			   this->txtNewPassword->AccessibleName = L"Text Box";
			   this->txtNewPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			   this->txtNewPassword->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtNewPassword->BackColor = System::Drawing::Color::Transparent;
			   this->txtNewPassword->BlinkCount = 3;
			   this->txtNewPassword->BlinkShadow = false;
			   this->txtNewPassword->BorderColor1 = System::Drawing::Color::DarkGray;
			   this->txtNewPassword->BorderColor2 = System::Drawing::Color::DarkGray;
			   this->txtNewPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtNewPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtNewPassword->CanShake = true;
			   this->txtNewPassword->ContinuousBlink = false;
			   this->txtNewPassword->CornerRadiusBottomLeft = 5;
			   this->txtNewPassword->CornerRadiusBottomRight = 5;
			   this->txtNewPassword->CornerRadiusTopLeft = 5;
			   this->txtNewPassword->CornerRadiusTopRight = 5;
			   this->txtNewPassword->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtNewPassword->CursorBlinkRate = 500;
			   this->txtNewPassword->CursorColor = System::Drawing::Color::Black;
			   this->txtNewPassword->CursorHeight = 26;
			   this->txtNewPassword->CursorOffset = 0;
			   this->txtNewPassword->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			   this->txtNewPassword->CursorWidth = 1;
			   this->txtNewPassword->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			   this->txtNewPassword->DisabledBorderColor = System::Drawing::Color::LightGray;
			   this->txtNewPassword->DisabledTextColor = System::Drawing::Color::Gray;
			   this->txtNewPassword->EnableDropShadow = false;
			   this->txtNewPassword->FillColor1 = System::Drawing::Color::White;
			   this->txtNewPassword->FillColor2 = System::Drawing::Color::White;
			   this->txtNewPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.5F));
			   this->txtNewPassword->ForeColor = System::Drawing::Color::DimGray;
			   this->txtNewPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			   this->txtNewPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			   this->txtNewPassword->IsEnabled = true;
			   this->txtNewPassword->Location = System::Drawing::Point(21, 231);
			   this->txtNewPassword->MaxLength = 50;
			   this->txtNewPassword->Name = L"txtNewPassword";
			   this->txtNewPassword->PlaceholderColor = System::Drawing::Color::Gray;
			   this->txtNewPassword->PlaceholderText = L"New Password...";
			   this->txtNewPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			   this->txtNewPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			   this->txtNewPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			   this->txtNewPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			   this->txtNewPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			   this->txtNewPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				   static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->txtNewPassword->ShadowAnimationDuration = 1;
			   this->txtNewPassword->ShadowBlur = 10;
			   this->txtNewPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->txtNewPassword->Size = System::Drawing::Size(248, 25);
			   this->txtNewPassword->SolidBorderColor = System::Drawing::Color::DarkGray;
			   this->txtNewPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtNewPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			   this->txtNewPassword->SolidFillColor = System::Drawing::Color::White;
			   this->txtNewPassword->TabIndex = 11;
			   this->txtNewPassword->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			   this->txtNewPassword->UseSystemPasswordChar = true;
			   this->txtNewPassword->ValidationErrorMessage = L"Invalid input.";
			   this->txtNewPassword->ValidationFunction = nullptr;
			   //
			   // txtCurrentPassword
			   //
			   this->txtCurrentPassword->AccessibleDescription = L"A customizable text input field.";
			   this->txtCurrentPassword->AccessibleName = L"Text Box";
			   this->txtCurrentPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			   this->txtCurrentPassword->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->txtCurrentPassword->BackColor = System::Drawing::Color::Transparent;
			   this->txtCurrentPassword->BlinkCount = 3;
			   this->txtCurrentPassword->BlinkShadow = false;
			   this->txtCurrentPassword->BorderColor1 = System::Drawing::Color::DarkGray;
			   this->txtCurrentPassword->BorderColor2 = System::Drawing::Color::DarkGray;
			   this->txtCurrentPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtCurrentPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtCurrentPassword->CanShake = true;
			   this->txtCurrentPassword->ContinuousBlink = false;
			   this->txtCurrentPassword->CornerRadiusBottomLeft = 5;
			   this->txtCurrentPassword->CornerRadiusBottomRight = 5;
			   this->txtCurrentPassword->CornerRadiusTopLeft = 5;
			   this->txtCurrentPassword->CornerRadiusTopRight = 5;
			   this->txtCurrentPassword->Cursor = System::Windows::Forms::Cursors::IBeam;
			   this->txtCurrentPassword->CursorBlinkRate = 500;
			   this->txtCurrentPassword->CursorColor = System::Drawing::Color::Black;
			   this->txtCurrentPassword->CursorHeight = 26;
			   this->txtCurrentPassword->CursorOffset = 0;
			   this->txtCurrentPassword->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			   this->txtCurrentPassword->CursorWidth = 1;
			   this->txtCurrentPassword->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			   this->txtCurrentPassword->DisabledBorderColor = System::Drawing::Color::LightGray;
			   this->txtCurrentPassword->DisabledTextColor = System::Drawing::Color::Gray;
			   this->txtCurrentPassword->EnableDropShadow = false;
			   this->txtCurrentPassword->FillColor1 = System::Drawing::Color::White;
			   this->txtCurrentPassword->FillColor2 = System::Drawing::Color::White;
			   this->txtCurrentPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.5F));
			   this->txtCurrentPassword->ForeColor = System::Drawing::Color::DimGray;
			   this->txtCurrentPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			   this->txtCurrentPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			   this->txtCurrentPassword->IsEnabled = true;
			   this->txtCurrentPassword->Location = System::Drawing::Point(21, 176);
			   this->txtCurrentPassword->MaxLength = 50;
			   this->txtCurrentPassword->Name = L"txtCurrentPassword";
			   this->txtCurrentPassword->PlaceholderColor = System::Drawing::Color::Gray;
			   this->txtCurrentPassword->PlaceholderText = L"Current Password...";
			   this->txtCurrentPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			   this->txtCurrentPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			   this->txtCurrentPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			   this->txtCurrentPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			   this->txtCurrentPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			   this->txtCurrentPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				   static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->txtCurrentPassword->ShadowAnimationDuration = 1;
			   this->txtCurrentPassword->ShadowBlur = 10;
			   this->txtCurrentPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->txtCurrentPassword->Size = System::Drawing::Size(248, 25);
			   this->txtCurrentPassword->SolidBorderColor = System::Drawing::Color::DarkGray;
			   this->txtCurrentPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->txtCurrentPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			   this->txtCurrentPassword->SolidFillColor = System::Drawing::Color::White;
			   this->txtCurrentPassword->TabIndex = 10;
			   this->txtCurrentPassword->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			   this->txtCurrentPassword->UseSystemPasswordChar = true;
			   this->txtCurrentPassword->ValidationErrorMessage = L"Invalid input.";
			   this->txtCurrentPassword->ValidationFunction = nullptr;
			   //
			   // lblPasswordStatus
			   //
			   this->lblPasswordStatus->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->lblPasswordStatus->AutoSize = true;
			   this->lblPasswordStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			   this->lblPasswordStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)));
			   this->lblPasswordStatus->Location = System::Drawing::Point(18, 345);
			   this->lblPasswordStatus->Name = L"lblPasswordStatus";
			   this->lblPasswordStatus->Size = System::Drawing::Size(0, 15);
			   this->lblPasswordStatus->TabIndex = 48;
			   //
			   // label8
			   //
			   this->label8->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label8->AutoSize = true;
			   this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label8->Location = System::Drawing::Point(18, 269);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(91, 13);
			   this->label8->TabIndex = 46;
			   this->label8->Text = L"Confirm Password";
			   //
			   // label9
			   //
			   this->label9->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label9->AutoSize = true;
			   this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label9->Location = System::Drawing::Point(18, 159);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(90, 13);
			   this->label9->TabIndex = 42;
			   this->label9->Text = L"Current Password";
			   //
			   // label10
			   //
			   this->label10->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->label10->AutoSize = true;
			   this->label10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				   static_cast<System::Int32>(static_cast<System::Byte>(80)));
			   this->label10->Location = System::Drawing::Point(18, 214);
			   this->label10->Name = L"label10";
			   this->label10->Size = System::Drawing::Size(78, 13);
			   this->label10->TabIndex = 43;
			   this->label10->Text = L"New Password";
			   //
			   // chkShowPassword
			   //
			   this->chkShowPassword->Anchor = System::Windows::Forms::AnchorStyles::Top;
			   this->chkShowPassword->AutoSize = true;
			   this->chkShowPassword->Location = System::Drawing::Point(21, 320);
			   this->chkShowPassword->Name = L"chkShowPassword";
			   this->chkShowPassword->Size = System::Drawing::Size(101, 17);
			   this->chkShowPassword->TabIndex = 13;
			   this->chkShowPassword->Text = L"Show password";
			   this->chkShowPassword->UseVisualStyleBackColor = true;
			   this->chkShowPassword->CheckedChanged += gcnew System::EventHandler(this, &ProfileForm::chkShowPassword_CheckedChanged);
			   //
			   // btnChangePassword
			   //
			   this->btnChangePassword->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnChangePassword->AccessibleName = L"Update Password";
			   this->btnChangePassword->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->btnChangePassword->AutoSizeBasedOnText = false;
			   this->btnChangePassword->BackColor = System::Drawing::Color::Transparent;
			   this->btnChangePassword->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnChangePassword->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			   this->btnChangePassword->BadgeValue = 0;
			   this->btnChangePassword->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnChangePassword->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)),
				   static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
			   this->btnChangePassword->BorderWidth = 1;
			   this->btnChangePassword->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				   static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->btnChangePassword->ButtonImage = nullptr;
			   this->btnChangePassword->ButtonTextLeftPadding = 0;
			   this->btnChangePassword->CanBeep = true;
			   this->btnChangePassword->CanGlow = false;
			   this->btnChangePassword->CanShake = true;
			   this->btnChangePassword->ContextMenuStripEx = nullptr;
			   this->btnChangePassword->CornerRadiusBottomLeft = 6;
			   this->btnChangePassword->CornerRadiusBottomRight = 6;
			   this->btnChangePassword->CornerRadiusTopLeft = 6;
			   this->btnChangePassword->CornerRadiusTopRight = 6;
			   this->btnChangePassword->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnChangePassword->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnChangePassword->EnableLongPress = false;
			   this->btnChangePassword->EnableRippleEffect = true;
			   this->btnChangePassword->EnableShadow = false;
			   this->btnChangePassword->EnableTextWrapping = false;
			   this->btnChangePassword->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.2F));
			   this->btnChangePassword->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->btnChangePassword->GlowIntensity = 100;
			   this->btnChangePassword->GlowRadius = 20;
			   this->btnChangePassword->GradientBackground = false;
			   this->btnChangePassword->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnChangePassword->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnChangePassword->HintText = nullptr;
			   this->btnChangePassword->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				   static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			   this->btnChangePassword->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnChangePassword->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnChangePassword->HoverTransitionDuration = 250;
			   this->btnChangePassword->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnChangePassword->ImagePadding = 5;
			   this->btnChangePassword->ImageSize = System::Drawing::Size(16, 16);
			   this->btnChangePassword->IsRadial = false;
			   this->btnChangePassword->IsReadOnly = false;
			   this->btnChangePassword->IsToggleButton = false;
			   this->btnChangePassword->IsToggled = false;
			   this->btnChangePassword->Location = System::Drawing::Point(140, 450);
			   this->btnChangePassword->LongPressDurationMS = 1000;
			   this->btnChangePassword->Name = L"btnChangePassword";
			   this->btnChangePassword->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnChangePassword->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				   static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			   this->btnChangePassword->ParticleCount = 15;
			   this->btnChangePassword->PressAnimationScale = 0.97F;
			   this->btnChangePassword->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				   static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			   this->btnChangePassword->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnChangePassword->PressTransitionDuration = 150;
			   this->btnChangePassword->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnChangePassword->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnChangePassword->RippleRadiusMultiplier = 0.6F;
			   this->btnChangePassword->ShadowBlur = 5;
			   this->btnChangePassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnChangePassword->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnChangePassword->ShakeDuration = 500;
			   this->btnChangePassword->ShakeIntensity = 5;
			   this->btnChangePassword->Size = System::Drawing::Size(150, 30);
			   this->btnChangePassword->TabIndex = 14;
			   this->btnChangePassword->Text = L"Update Password";
			   this->btnChangePassword->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   this->btnChangePassword->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->btnChangePassword->TooltipText = nullptr;
			   this->btnChangePassword->UseAdvancedRendering = true;
			   this->btnChangePassword->UseParticles = false;
			   this->btnChangePassword->Click += gcnew System::EventHandler(this, &ProfileForm::btnChangePassword_Click);
			   //
			   // ProfileForm
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				   static_cast<System::Int32>(static_cast<System::Byte>(250)));
			   this->ClientSize = System::Drawing::Size(916, 543);
			   this->Controls->Add(this->panelMain);
			   this->Controls->Add(this->panelHeader);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->Name = L"ProfileForm";
			   this->Text = L"Profile – IntraProcure";
			   this->panelHeader->ResumeLayout(false);
			   this->panelHeader->PerformLayout();
			   this->panelMain->ResumeLayout(false);
			   this->splitContainer1->Panel1->ResumeLayout(false);
			   this->splitContainer1->Panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			   this->splitContainer1->ResumeLayout(false);
			   this->siticonePanel1->ResumeLayout(false);
			   this->siticonePanel1->PerformLayout();
			   this->siticonePanel2->ResumeLayout(false);
			   this->siticonePanel2->PerformLayout();
			   this->ResumeLayout(false);
		   }
#pragma endregion

		   array<System::Byte>^ _profileImageBytes;

		   // ----------------------------------------------------
				   // ComboBox data
				   // ----------------------------------------------------
		   void InitializeCombos()
		   {
			   // Department
			   cmbDepartment->Items->Clear();
			   cmbDepartment->Items->AddRange(
				   gcnew array<Object^>{
				   L"Engineering",
					   L"IT",
					   L"Procurement",
					   L"Finance",
					   L"HR",
					   L"Operations",
					   L"Logistics",
					   L"Administration",
					   L"Marketing",
					   L"Sales"
			   }
			   );

			   // Country
			   cmbCountry->Items->Clear();
			   cmbCountry->Items->AddRange(
				   gcnew array<Object^>{
				   L"Egypt",
					   L"Saudi Arabia",
					   L"United Arab Emirates",
					   L"Qatar",
					   L"Kuwait",
					   L"USA",
					   L"United Kingdom",
					   L"Germany",
					   L"France"
			   }
			   );

			   // City   static list, you can extend anytime
			   cmbCity->Items->Clear();
			   cmbCity->Items->AddRange(
				   gcnew array<Object^>{
				   L"Cairo",
					   L"Giza",
					   L"Alexandria",
					   L"Dubai",
					   L"Riyadh",
					   L"Jeddah",
					   L"Doha",
					   L"London",
					   L"New York"
			   }
			   );
		   }

		   // ----------------------------------------------------
		   // Load currently logged-in employee
		   // ----------------------------------------------------
		   void LoadCurrentUser()
		   {
			   if (Session::UserId <= 0)
			   {
				   MessageBox::Show(
					   L"No logged-in user. Please log in again.",
					   L"Profile",
					   MessageBoxButtons::OK,
					   MessageBoxIcon::Warning);
				   return;
			   }

			   String^ error = nullptr;
			   Employee^ emp = EmployeeManager::GetById(Session::UserId, error);

			   if (emp == nullptr)
			   {
				   String^ msg = L"Unable to load your profile.";
				   if (!String::IsNullOrEmpty(error))
					   msg += L"\n\n" + error;

				   MessageBox::Show(
					   msg,
					   L"Profile",
					   MessageBoxButtons::OK,
					   MessageBoxIcon::Error);
				   return;
			   }

			   // basic fields
			   txtID->Text = emp->Id.ToString();
			   txtUsername->Text = emp->Username;
			   txtFullName->Text = emp->FullName;
			   txtEmail->Text = emp->Email;
			   txtPhone->Text = emp->Phone;

			   txtRole->Text = emp->IsAdministrator
				   ? L"Administrator"
				   : (emp->IsManager ? L"Manager" : L"Employee");

			   // department
			   if (!String::IsNullOrEmpty(emp->Department))
			   {
				   int idx = cmbDepartment->Items->IndexOf(emp->Department);
				   if (idx >= 0)
					   cmbDepartment->SelectedIndex = idx;
				   else
				   {
					   cmbDepartment->Items->Add(emp->Department);
					   cmbDepartment->SelectedItem = emp->Department;
				   }
			   }

			   // city
			   if (!String::IsNullOrEmpty(emp->City))
			   {
				   int idxCountry = cmbCity->Items->IndexOf(emp->City);
				   if (idxCountry >= 0)
					   cmbCity->SelectedIndex = idxCountry;
				   else
				   {
					   cmbCity->Items->Add(emp->City);
					   cmbCity->SelectedItem = emp->City;
				   }
			   }

			   // country
			   if (!String::IsNullOrEmpty(emp->Country))
			   {
				   int idxCountry = cmbCountry->Items->IndexOf(emp->Country);
				   if (idxCountry >= 0)
					   cmbCountry->SelectedIndex = idxCountry;
				   else
				   {
					   cmbCountry->Items->Add(emp->Country);
					   cmbCountry->SelectedItem = emp->Country;
				   }
			   }

			   // address put into WorkAddress (city is separate on the UI)
			   if (!String::IsNullOrEmpty(emp->Address))
				   txtWorkAddress->Text = emp->Address;

			   _profileImageBytes = emp->ProfileImage;

			   if (_profileImageBytes != nullptr && _profileImageBytes->Length > 0)
			   {
				   try
				   {
					   MemoryStream^ ms = gcnew MemoryStream(_profileImageBytes);
					   picUser->Image = Image::FromStream(ms);
				   }
				   catch (...)
				   {
					   // If corrupt image, just ignore and keep default avatar
					   _profileImageBytes = nullptr;
				   }
			   }
		   }
		   // ----------------------------------------------------
		   // Save profile (including picture)
		   // ----------------------------------------------------
		   void SaveProfile()
		   {
			   SqlConnection^ conn = nullptr;

			   int empId = Session::UserId;
			   if (empId <= 0)
			   {
				   MessageBox::Show(L"User session is not initialized.", L"Error",
					   MessageBoxButtons::OK, MessageBoxIcon::Error);
				   return;
			   }

			   Employee^ e = Session::CurrentUser();

			   e->FullName = txtFullName->Text->Trim();
			   e->Department = (cmbDepartment->SelectedItem == nullptr)
				   ? nullptr
				   : cmbDepartment->SelectedItem->ToString();
			   e->Email = txtEmail->Text->Trim();
			   e->Phone = txtPhone->Text->Trim();
			   e->City = (cmbCity->SelectedItem == nullptr)
				   ? nullptr
				   : cmbCity->SelectedItem->ToString();
			   e->Country = (cmbCountry->SelectedItem == nullptr)
				   ? nullptr
				   : cmbCountry->SelectedItem->ToString();
			   if (!String::IsNullOrEmpty(txtWorkAddress->Text))
				   e->Address = txtWorkAddress->Text->Trim();
			   else
				   e->Address = e->City;

			   // Prepare photo bytes (if user selected a picture)
			   if (picUser->Image != nullptr)
			   {
				   MemoryStream^ ms = gcnew MemoryStream();
				   picUser->Image->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
				   e->ProfileImage = ms->ToArray();
			   }

			   String^ error = nullptr;
			   bool ok = EmployeeManager::UpdateProfile(e, error);
			   Session::UpdateProfile(e->FullName, e->Department, e->Email, e->ProfileImage);

			   if (!ok)
			   {
				   MessageBox::Show(
					   L"Failed to update profile.\n\n" + (error == nullptr ? "" : error),
					   L"Profile",
					   MessageBoxButtons::OK,
					   MessageBoxIcon::Error);
				   return;
			   }

			   // If update succeeded, keep Session::CurrentUser in sync (we already updated e)
			   MessageBox::Show(
				   L"Profile updated successfully.",
				   L"Profile",
				   MessageBoxButtons::OK,
				   MessageBoxIcon::Information);
		   }

		   // ----------------------------------------------------
		   // Password helpers (re-use same hashing idea)
		   // ----------------------------------------------------
		   static String^ GenerateSalt(int size)
		   {
			   if (size <= 0) size = 16;
			   array<Byte>^ saltBytes = gcnew array<Byte>(size);
			   RNGCryptoServiceProvider^ rng = gcnew RNGCryptoServiceProvider();
			   rng->GetBytes(saltBytes);
			   return Convert::ToBase64String(saltBytes);
		   }

		   static String^ HashPassword(String^ password, String^ salt)
		   {
			   if (String::IsNullOrEmpty(password)) return String::Empty;

			   String^ toHash = password + ":" + (salt == nullptr ? "" : salt);
			   array<Byte>^ bytes = Encoding::UTF8->GetBytes(toHash);
			   SHA256^ sha = SHA256::Create();
			   array<Byte>^ hash = sha->ComputeHash(bytes);
			   return Convert::ToBase64String(hash);
		   }

		   bool ChangePassword(String^ currentPwd, String^ newPwd)
		   {
			   lblPasswordStatus->Text = L"";

			   String^ error = nullptr;
			   Employee^ user = EmployeeManager::Authenticate(Session::Username, currentPwd, error);

			   if (user == nullptr)
			   {
				   if (String::IsNullOrEmpty(error))
					   error = L"Current password is incorrect.";
				   lblPasswordStatus->Text = error;
				   return false;
			   }

			   String^ salt = GenerateSalt(16);
			   String^ hash = HashPassword(newPwd, salt);

			   SqlConnection^ conn = DatabaseManager::CreateConnection();
			   try
			   {
				   conn->Open();
				   String^ sql =
					   "UPDATE procure.Employees "
					   "SET PasswordHash=@h, PasswordSalt=@s "
					   "WHERE Id=@id;";
				   SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				   cmd->Parameters->AddWithValue("@h", hash);
				   cmd->Parameters->AddWithValue("@s", salt);
				   cmd->Parameters->AddWithValue("@id", Session::UserId);

				   int rows = cmd->ExecuteNonQuery();
				   if (rows <= 0)
				   {
					   lblPasswordStatus->Text = L"Failed to update password.";
					   return false;
				   }

				   lblPasswordStatus->Text = L"Password updated successfully.";
				   return true;
			   }
			   catch (Exception^ ex)
			   {
				   lblPasswordStatus->Text = L"Error: " + ex->Message;
				   return false;
			   }
			   finally
			   {
				   if (conn != nullptr &&
					   conn->State == System::Data::ConnectionState::Open)
				   {
					   try { conn->Close(); }
					   catch (...) {}
				   }
			   }
		   }

		   // Load a resource that may be an Image or an Icon and return an Image (Bitmap) safely.
		   System::Drawing::Image^ LoadImageFromResource(System::String^ key)
		   {
			   if (_resMgr == nullptr || String::IsNullOrEmpty(key)) return nullptr;
			   Object^ obj = _resMgr->GetObject(key);
			   if (obj == nullptr) return nullptr;

			   System::Drawing::Image^ img = dynamic_cast<System::Drawing::Image^>(obj);
			   if (img != nullptr) return img;

			   System::Drawing::Icon^ ico = dynamic_cast<System::Drawing::Icon^>(obj);
			   if (ico != nullptr) return ico->ToBitmap();

			   return nullptr;
		   }

		   // ----------------------------------------------------
		   // Event handlers wired from designer
		   // ----------------------------------------------------
	private:
		System::Void chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			bool show = chkShowPassword->Checked;
			txtCurrentPassword->UseSystemPasswordChar = !show;
			txtNewPassword->UseSystemPasswordChar = !show;
			txtConfirmNewPassword->UseSystemPasswordChar = !show;
		}

		System::Void btnSaveProfile_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SaveProfile();
		}

		System::Void btnChangePassword_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ currentPwd = txtCurrentPassword->Text;
			String^ newPwd = txtNewPassword->Text;
			String^ confirm = txtConfirmNewPassword->Text;

			if (String::IsNullOrWhiteSpace(currentPwd) ||
				String::IsNullOrWhiteSpace(newPwd) ||
				String::IsNullOrWhiteSpace(confirm))
			{
				lblPasswordStatus->Text = L"Please fill all password fields.";
				return;
			}

			if (newPwd->Length < 6)
			{
				lblPasswordStatus->Text = L"New password must be at least 6 characters.";
				return;
			}

			if (newPwd != confirm)
			{
				lblPasswordStatus->Text = L"New password and confirmation do not match.";
				return;
			}

			if (ChangePassword(currentPwd, newPwd))
			{
				txtCurrentPassword->Clear();
				txtNewPassword->Clear();
				txtConfirmNewPassword->Clear();
			}
		}

		// Button you added for choosing a profile picture.
		System::Void picUser_Click(System::Object^ sender, System::EventArgs^ e)
		{
			OpenFileDialog^ dlg = gcnew OpenFileDialog();
			dlg->Title = L"Choose profile picture";
			dlg->Filter = L"Image files|*.jpg;*.jpeg;*.png;*.bmp;*.gif|All files|*.*";
			dlg->Multiselect = false;
			dlg->CheckFileExists = true;
			dlg->RestoreDirectory = true;

			if (dlg->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
			{
				String^ path = dlg->FileName;
				try
				{
					// Optional: reject very large files (5 MB)
					System::IO::FileInfo^ fi = gcnew System::IO::FileInfo(path);
					const long long MAX_BYTES = 5LL * 1024 * 1024;
					if (fi->Length > MAX_BYTES)
					{
						MessageBox::Show(
							L"Selected image is too large. Please choose an image under 5 MB.",
							L"Image too large",
							MessageBoxButtons::OK,
							MessageBoxIcon::Warning);
						return;
					}

					// Read file bytes safely (no exclusive lock)
					array<Byte>^ bytes = nullptr;
					System::IO::FileStream^ fs = nullptr;
					try
					{
						fs = gcnew System::IO::FileStream(path, System::IO::FileMode::Open, System::IO::FileAccess::Read, System::IO::FileShare::Read);
						bytes = gcnew array<Byte>(static_cast<int>(fs->Length));
						int read = fs->Read(bytes, 0, bytes->Length);
						if (read != bytes->Length)
							throw gcnew System::IO::IOException(L"Failed to read the entire file.");
					}
					finally
					{
						if (fs != nullptr) { try { fs->Close(); } catch (...) {} delete fs; }
					}

					// Load image from memory to avoid locking the file and to validate image content
					System::IO::MemoryStream^ ms = nullptr;
					Image^ loaded = nullptr;
					try
					{
						ms = gcnew System::IO::MemoryStream(bytes);
						loaded = Image::FromStream(ms);

						// Clone into a Bitmap so it is independent of the stream
						Image^ display = gcnew System::Drawing::Bitmap(loaded);
						// Assign to picture box (existing image will be replaced)
						picUser->Image = display;

						// Store bytes for DB
						_profileImageBytes = bytes;
					}
					finally
					{
						// dispose temporary objects; do NOT delete 'display' because picUser now owns the reference
						if (loaded != nullptr) { delete loaded; loaded = nullptr; }
						if (ms != nullptr) { try { ms->Close(); } catch (...) {} delete ms; ms = nullptr; }
					}
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(
						L"Could not load image: " + ex->Message,
						L"Image error",
						MessageBoxButtons::OK,
						MessageBoxIcon::Error);
					_profileImageBytes = nullptr;
				}
			}
		}
	private: System::Void btnClearPic_Click(System::Object^ sender, System::EventArgs^ e) {
		picUser->Image = LoadImageFromResource("profile_purple");
		_profileImageBytes = nullptr;
	}
	};
}