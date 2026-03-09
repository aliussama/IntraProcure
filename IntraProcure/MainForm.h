#pragma once

#include "HomeForm.h"
#include "RequestCartForm.h"
#include "MyRequestsForm.h"
#include "ManagerPanelForm.h"
#include "ProfileForm.h"
#include "Session.h"
#include "SuppliersForm.h"
#include "InventoryForm.h"
#include "RegisterForm.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;
	using namespace System::Resources;
	using namespace System::IO;
	using System::Drawing::Icon;
	using System::Drawing::Image;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			ApplyRoleSecurity();

			// create ResourceManager for Resource.resx
			_resMgr = gcnew ResourceManager(
				"IntraProcure.Resource",             // <project namespace>.<resx name>
				Assembly::GetExecutingAssembly());

			// Window behaviour
			this->WindowState = FormWindowState::Maximized;
			this->StartPosition = FormStartPosition::CenterScreen;

			// Load user data and set default page
			LoadData();

			// React to any profile / session changes
			Session::CurrentUserChanged += gcnew Action(this, &MainForm::OnCurrentUserChanged);
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		// Layout

		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
		SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelPageHost;
		SiticoneNetFrameworkUI::SiticoneAdvancedPanel^ panelCard;

		// Sidebar controls

		// Header controls

		// Runtime state
		System::Windows::Forms::Form^ _currentChild;
		SiticoneNetFrameworkUI::SiticoneButton^ _activeNavButton;

	private: System::Windows::Forms::Label^ lblUserRole;

	private: System::Windows::Forms::Label^ lblUserName;

	private: SiticoneNetFrameworkUI::SiticonePanel^ pnlSideBar;

	private: System::Windows::Forms::Panel^ ContentPanel;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnLogout;

	private: SiticoneNetFrameworkUI::SiticoneButton^ btnInventory;

	private: SiticoneNetFrameworkUI::SiticoneButton^ btnSuppliers;

	private: SiticoneNetFrameworkUI::SiticoneAdvancedPanel^ panelNavHighlight;
	private: System::Windows::Forms::Label^ lblAppName;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnDashboard;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnProducts;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnMyRequests;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnCart;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnProfile;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnRegister;
	private: System::Windows::Forms::FlowLayoutPanel^ panel1;
	private: System::Windows::Forms::Label^ lblDate;

	private: System::Windows::Forms::Label^ label1;
	private: SiticoneNetFrameworkUI::SiticoneAvatar^ picUser;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

		   // Resources
		   ResourceManager^ _resMgr;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->picUser = (gcnew SiticoneNetFrameworkUI::SiticoneAvatar());
			   this->lblDate = (gcnew System::Windows::Forms::Label());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->lblUserRole = (gcnew System::Windows::Forms::Label());
			   this->lblUserName = (gcnew System::Windows::Forms::Label());
			   this->panelPageHost = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			   this->panelCard = (gcnew SiticoneNetFrameworkUI::SiticoneAdvancedPanel());
			   this->ContentPanel = (gcnew System::Windows::Forms::Panel());
			   this->pnlSideBar = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnLogout = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelNavHighlight = (gcnew SiticoneNetFrameworkUI::SiticoneAdvancedPanel());
			   this->lblAppName = (gcnew System::Windows::Forms::Label());
			   this->panel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->btnDashboard = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnProducts = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnMyRequests = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnCart = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnSuppliers = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnInventory = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnProfile = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->btnRegister = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			   this->panelHeader->SuspendLayout();
			   this->panelPageHost->SuspendLayout();
			   this->pnlSideBar->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->panel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // panelHeader
			   // 
			   this->panelHeader->BackColor = System::Drawing::Color::White;
			   this->panelHeader->Controls->Add(this->picUser);
			   this->panelHeader->Controls->Add(this->lblDate);
			   this->panelHeader->Controls->Add(this->label1);
			   this->panelHeader->Controls->Add(this->lblUserRole);
			   this->panelHeader->Controls->Add(this->lblUserName);
			   this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			   this->panelHeader->Location = System::Drawing::Point(220, 0);
			   this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelHeader->Name = L"panelHeader";
			   this->panelHeader->Size = System::Drawing::Size(964, 70);
			   this->panelHeader->TabIndex = 1;
			   // 
			   // picUser
			   // 
			   this->picUser->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->picUser->BorderColor = System::Drawing::Color::White;
			   this->picUser->BorderThickness = 1;
			   this->picUser->Cursor = System::Windows::Forms::Cursors::Default;
			   this->picUser->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picUser.Image")));
			   this->picUser->Location = System::Drawing::Point(688, 5);
			   this->picUser->Margin = 0;
			   this->picUser->Name = L"picUser";
			   this->picUser->Size = System::Drawing::Size(60, 60);
			   this->picUser->TabIndex = 43;
			   this->picUser->TintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				   static_cast<System::Int32>(static_cast<System::Byte>(130)), static_cast<System::Int32>(static_cast<System::Byte>(180)));
			   // 
			   // lblDate
			   // 
			   this->lblDate->AutoSize = true;
			   this->lblDate->Font = (gcnew System::Drawing::Font(L"Arial", 17, System::Drawing::FontStyle::Bold));
			   this->lblDate->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				   static_cast<System::Int32>(static_cast<System::Byte>(40)));
			   this->lblDate->Location = System::Drawing::Point(80, 22);
			   this->lblDate->MaximumSize = System::Drawing::Size(175, 0);
			   this->lblDate->Name = L"lblDate";
			   this->lblDate->Size = System::Drawing::Size(152, 27);
			   this->lblDate->TabIndex = 10;
			   this->lblDate->Text = L"Today\'s Date";
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold));
			   this->label1->ForeColor = System::Drawing::Color::DimGray;
			   this->label1->Location = System::Drawing::Point(20, 20);
			   this->label1->MaximumSize = System::Drawing::Size(175, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(65, 30);
			   this->label1->TabIndex = 9;
			   this->label1->Text = L"Date:";
			   // 
			   // lblUserRole
			   // 
			   this->lblUserRole->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->lblUserRole->AutoSize = true;
			   this->lblUserRole->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->lblUserRole->ForeColor = System::Drawing::Color::Gray;
			   this->lblUserRole->Location = System::Drawing::Point(753, 40);
			   this->lblUserRole->Name = L"lblUserRole";
			   this->lblUserRole->Size = System::Drawing::Size(30, 15);
			   this->lblUserRole->TabIndex = 8;
			   this->lblUserRole->Text = L"Role";
			   // 
			   // lblUserName
			   // 
			   this->lblUserName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			   this->lblUserName->AutoSize = true;
			   this->lblUserName->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 11, System::Drawing::FontStyle::Bold));
			   this->lblUserName->ForeColor = System::Drawing::Color::DimGray;
			   this->lblUserName->Location = System::Drawing::Point(753, 20);
			   this->lblUserName->MaximumSize = System::Drawing::Size(175, 0);
			   this->lblUserName->Name = L"lblUserName";
			   this->lblUserName->Size = System::Drawing::Size(79, 20);
			   this->lblUserName->TabIndex = 6;
			   this->lblUserName->Text = L"Full Name";
			   // 
			   // panelPageHost
			   // 
			   this->panelPageHost->BackColor = System::Drawing::Color::White;
			   this->panelPageHost->Controls->Add(this->panelCard);
			   this->panelPageHost->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panelPageHost->Location = System::Drawing::Point(220, 70);
			   this->panelPageHost->MinimumSize = System::Drawing::Size(20, 20);
			   this->panelPageHost->Name = L"panelPageHost";
			   this->panelPageHost->Padding = System::Windows::Forms::Padding(24);
			   this->panelPageHost->Size = System::Drawing::Size(964, 631);
			   this->panelPageHost->TabIndex = 0;
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
			   this->panelCard->BorderColor = System::Drawing::Color::Transparent;
			   this->panelCard->BorderDashPattern = nullptr;
			   this->panelCard->BorderGlowColor = System::Drawing::Color::Cyan;
			   this->panelCard->BorderGlowSize = 3;
			   this->panelCard->BorderWidth = 1;
			   this->panelCard->BottomLeftRadius = 20;
			   this->panelCard->BottomRightRadius = 20;
			   this->panelCard->ContentAlignmentCustom = System::Drawing::ContentAlignment::MiddleCenter;
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
			   this->panelCard->Location = System::Drawing::Point(24, 24);
			   this->panelCard->Name = L"panelCard";
			   this->panelCard->Padding = System::Windows::Forms::Padding(25);
			   this->panelCard->RadialGradientCenter = (cli::safe_cast<System::Drawing::PointF>(resources->GetObject(L"panelCard.RadialGradientCenter")));
			   this->panelCard->RadialGradientRadius = 1;
			   this->panelCard->ScaleRatio = 0.8F;
			   this->panelCard->SecondaryBorderColor = System::Drawing::Color::DarkGray;
			   this->panelCard->ShadowBlur = 10;
			   this->panelCard->ShadowColor = System::Drawing::Color::Black;
			   this->panelCard->ShadowDepth = 5;
			   this->panelCard->ShadowOffset = System::Drawing::Point(2, 2);
			   this->panelCard->ShadowOpacity = 0.3F;
			   this->panelCard->Size = System::Drawing::Size(916, 583);
			   this->panelCard->SlideDirection = System::Drawing::Point(0, -30);
			   this->panelCard->TabIndex = 0;
			   this->panelCard->TopLeftRadius = 20;
			   this->panelCard->TopRightRadius = 20;
			   // 
			   // ContentPanel
			   // 
			   this->ContentPanel->AutoScroll = true;
			   this->ContentPanel->BackColor = System::Drawing::SystemColors::Control;
			   this->ContentPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->ContentPanel->Location = System::Drawing::Point(0, 30);
			   this->ContentPanel->Name = L"ContentPanel";
			   this->ContentPanel->Size = System::Drawing::Size(263, 120);
			   this->ContentPanel->TabIndex = 0;
			   // 
			   // pnlSideBar
			   // 
			   this->pnlSideBar->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->pnlSideBar->BackColor = System::Drawing::Color::Transparent;
			   this->pnlSideBar->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			   this->pnlSideBar->BorderDashPattern = nullptr;
			   this->pnlSideBar->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->pnlSideBar->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				   static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->pnlSideBar->BorderThickness = 2;
			   this->pnlSideBar->Controls->Add(this->pictureBox1);
			   this->pnlSideBar->Controls->Add(this->btnLogout);
			   this->pnlSideBar->Controls->Add(this->panelNavHighlight);
			   this->pnlSideBar->Controls->Add(this->lblAppName);
			   this->pnlSideBar->Controls->Add(this->panel1);
			   this->pnlSideBar->CornerRadiusBottomLeft = 0;
			   this->pnlSideBar->CornerRadiusBottomRight = 10;
			   this->pnlSideBar->CornerRadiusTopLeft = 0;
			   this->pnlSideBar->CornerRadiusTopRight = 10;
			   this->pnlSideBar->Dock = System::Windows::Forms::DockStyle::Left;
			   this->pnlSideBar->EnableAcrylicEffect = false;
			   this->pnlSideBar->EnableMicaEffect = false;
			   this->pnlSideBar->EnableRippleEffect = false;
			   this->pnlSideBar->FillColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				   static_cast<System::Int32>(static_cast<System::Byte>(110)));
			   this->pnlSideBar->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				   System::Drawing::Color::White, System::Drawing::Color::LightGray,
					   System::Drawing::Color::Gray
			   };
			   this->pnlSideBar->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			   this->pnlSideBar->Location = System::Drawing::Point(0, 0);
			   this->pnlSideBar->Name = L"pnlSideBar";
			   this->pnlSideBar->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			   this->pnlSideBar->RippleAlpha = 50;
			   this->pnlSideBar->RippleAlphaDecrement = 3;
			   this->pnlSideBar->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				   static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			   this->pnlSideBar->RippleMaxSize = 600;
			   this->pnlSideBar->RippleSpeed = 15;
			   this->pnlSideBar->ShowBorder = true;
			   this->pnlSideBar->Size = System::Drawing::Size(220, 701);
			   this->pnlSideBar->TabIndex = 1;
			   this->pnlSideBar->TabStop = true;
			   this->pnlSideBar->TrackSystemTheme = false;
			   this->pnlSideBar->UseBorderGradient = true;
			   this->pnlSideBar->UseMultiGradient = false;
			   this->pnlSideBar->UsePatternTexture = false;
			   this->pnlSideBar->UseRadialGradient = false;
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			   this->pictureBox1->Location = System::Drawing::Point(5, 5);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(64, 64);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			   this->pictureBox1->TabIndex = 40;
			   this->pictureBox1->TabStop = false;
			   // 
			   // btnLogout
			   // 
			   this->btnLogout->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnLogout->AccessibleName = L"Log Out";
			   this->btnLogout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->btnLogout->AutoSizeBasedOnText = false;
			   this->btnLogout->BackColor = System::Drawing::Color::Transparent;
			   this->btnLogout->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnLogout->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnLogout->BadgeValue = 0;
			   this->btnLogout->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnLogout->BorderColor = System::Drawing::Color::Transparent;
			   this->btnLogout->BorderWidth = 1;
			   this->btnLogout->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnLogout->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLogout.ButtonImage")));
			   this->btnLogout->ButtonTextLeftPadding = 0;
			   this->btnLogout->CanBeep = true;
			   this->btnLogout->CanGlow = false;
			   this->btnLogout->CanShake = true;
			   this->btnLogout->ContextMenuStripEx = nullptr;
			   this->btnLogout->CornerRadiusBottomLeft = 0;
			   this->btnLogout->CornerRadiusBottomRight = 0;
			   this->btnLogout->CornerRadiusTopLeft = 0;
			   this->btnLogout->CornerRadiusTopRight = 0;
			   this->btnLogout->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnLogout->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnLogout->EnableLongPress = false;
			   this->btnLogout->EnableRippleEffect = false;
			   this->btnLogout->EnableShadow = false;
			   this->btnLogout->EnableTextWrapping = false;
			   this->btnLogout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnLogout->ForeColor = System::Drawing::Color::White;
			   this->btnLogout->GlowColor = System::Drawing::Color::Transparent;
			   this->btnLogout->GlowIntensity = 100;
			   this->btnLogout->GlowRadius = 20;
			   this->btnLogout->GradientBackground = false;
			   this->btnLogout->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnLogout->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnLogout->HintText = nullptr;
			   this->btnLogout->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnLogout->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnLogout->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnLogout->HoverTransitionDuration = 250;
			   this->btnLogout->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnLogout->ImagePadding = 5;
			   this->btnLogout->ImageSize = System::Drawing::Size(25, 25);
			   this->btnLogout->IsRadial = false;
			   this->btnLogout->IsReadOnly = false;
			   this->btnLogout->IsToggleButton = false;
			   this->btnLogout->IsToggled = false;
			   this->btnLogout->Location = System::Drawing::Point(29, 643);
			   this->btnLogout->LongPressDurationMS = 1000;
			   this->btnLogout->Name = L"btnLogout";
			   this->btnLogout->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnLogout->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnLogout->ParticleCount = 15;
			   this->btnLogout->PressAnimationScale = 0.97F;
			   this->btnLogout->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnLogout->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnLogout->PressTransitionDuration = 150;
			   this->btnLogout->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnLogout->RippleColor = System::Drawing::Color::Transparent;
			   this->btnLogout->RippleOpacity = 0;
			   this->btnLogout->RippleRadiusMultiplier = 0.6F;
			   this->btnLogout->ShadowBlur = 5;
			   this->btnLogout->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnLogout->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnLogout->ShakeDuration = 500;
			   this->btnLogout->ShakeIntensity = 5;
			   this->btnLogout->Size = System::Drawing::Size(188, 36);
			   this->btnLogout->TabIndex = 37;
			   this->btnLogout->Tag = L"logout";
			   this->btnLogout->Text = L"Log Out";
			   this->btnLogout->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnLogout->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnLogout->TooltipText = nullptr;
			   this->btnLogout->UltraFastPerformance = true;
			   this->btnLogout->UseAdvancedRendering = true;
			   this->btnLogout->UseParticles = false;
			   this->btnLogout->Click += gcnew System::EventHandler(this, &MainForm::btnLogout_Click);
			   // 
			   // panelNavHighlight
			   // 
			   this->panelNavHighlight->ActiveBackColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->ActiveBorderColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->AdvancedBorderStyle = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::BorderStyleEx::Solid;
			   this->panelNavHighlight->AnimationDuration = 500;
			   this->panelNavHighlight->AnimationType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::AnimationTypeEx::Fade;
			   this->panelNavHighlight->BackColor = System::Drawing::Color::Transparent;
			   this->panelNavHighlight->BackgroundImageCustom = nullptr;
			   this->panelNavHighlight->BackgroundImageOpacity = 1;
			   this->panelNavHighlight->BackgroundImageSizeMode = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::ImageSizeModeEx::Stretch;
			   this->panelNavHighlight->BackgroundOverlayColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				   static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			   this->panelNavHighlight->BorderColor = System::Drawing::Color::Gray;
			   this->panelNavHighlight->BorderDashPattern = nullptr;
			   this->panelNavHighlight->BorderGlowColor = System::Drawing::Color::Cyan;
			   this->panelNavHighlight->BorderGlowSize = 3;
			   this->panelNavHighlight->BorderWidth = 1;
			   this->panelNavHighlight->BottomLeftRadius = 0;
			   this->panelNavHighlight->BottomRightRadius = 10;
			   this->panelNavHighlight->ContentAlignmentCustom = System::Drawing::ContentAlignment::MiddleCenter;
			   this->panelNavHighlight->CornerPadding = System::Windows::Forms::Padding(5);
			   this->panelNavHighlight->DisabledBackColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->DisabledBorderColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->DoubleBorderSpacing = 2;
			   this->panelNavHighlight->EasingType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::EasingTypeEx::Linear;
			   this->panelNavHighlight->EnableAnimation = false;
			   this->panelNavHighlight->EnableBackgroundImage = false;
			   this->panelNavHighlight->EnableBorderGlow = false;
			   this->panelNavHighlight->EnableDoubleBorder = false;
			   this->panelNavHighlight->EnableGradient = false;
			   this->panelNavHighlight->EnableInnerShadow = false;
			   this->panelNavHighlight->EnableShadow = false;
			   this->panelNavHighlight->EnableSmartPadding = true;
			   this->panelNavHighlight->EnableStateStyles = false;
			   this->panelNavHighlight->FlowDirectionCustom = System::Windows::Forms::FlowDirection::LeftToRight;
			   this->panelNavHighlight->GradientAngle = 90;
			   this->panelNavHighlight->GradientEndColor = System::Drawing::Color::LightGray;
			   this->panelNavHighlight->GradientStartColor = System::Drawing::Color::White;
			   this->panelNavHighlight->GradientType = SiticoneNetFrameworkUI::SiticoneAdvancedPanel::GradientTypeEx::Linear;
			   this->panelNavHighlight->HoverBackColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->HoverBorderColor = System::Drawing::Color::Empty;
			   this->panelNavHighlight->InnerShadowColor = System::Drawing::Color::Black;
			   this->panelNavHighlight->InnerShadowDepth = 3;
			   this->panelNavHighlight->InnerShadowOpacity = 0.2F;
			   this->panelNavHighlight->Location = System::Drawing::Point(0, 104);
			   this->panelNavHighlight->Name = L"panelNavHighlight";
			   this->panelNavHighlight->Padding = System::Windows::Forms::Padding(10);
			   this->panelNavHighlight->RadialGradientCenter = (cli::safe_cast<System::Drawing::PointF>(resources->GetObject(L"panelNavHighlight.RadialGradientCenter")));
			   this->panelNavHighlight->RadialGradientRadius = 1;
			   this->panelNavHighlight->ScaleRatio = 0.8F;
			   this->panelNavHighlight->SecondaryBorderColor = System::Drawing::Color::DarkGray;
			   this->panelNavHighlight->ShadowBlur = 10;
			   this->panelNavHighlight->ShadowColor = System::Drawing::Color::Black;
			   this->panelNavHighlight->ShadowDepth = 5;
			   this->panelNavHighlight->ShadowOffset = System::Drawing::Point(2, 2);
			   this->panelNavHighlight->ShadowOpacity = 0.3F;
			   this->panelNavHighlight->Size = System::Drawing::Size(5, 36);
			   this->panelNavHighlight->SlideDirection = System::Drawing::Point(0, -30);
			   this->panelNavHighlight->TabIndex = 31;
			   this->panelNavHighlight->TopLeftRadius = 0;
			   this->panelNavHighlight->TopRightRadius = 10;
			   // 
			   // lblAppName
			   // 
			   this->lblAppName->AutoSize = true;
			   this->lblAppName->BackColor = System::Drawing::Color::Transparent;
			   this->lblAppName->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 14, System::Drawing::FontStyle::Bold));
			   this->lblAppName->ForeColor = System::Drawing::Color::White;
			   this->lblAppName->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->lblAppName->Location = System::Drawing::Point(75, 30);
			   this->lblAppName->Name = L"lblAppName";
			   this->lblAppName->Size = System::Drawing::Size(119, 25);
			   this->lblAppName->TabIndex = 25;
			   this->lblAppName->Text = L"IntraProcure";
			   // 
			   // panel1
			   // 
			   this->panel1->Controls->Add(this->btnDashboard);
			   this->panel1->Controls->Add(this->btnProducts);
			   this->panel1->Controls->Add(this->btnMyRequests);
			   this->panel1->Controls->Add(this->btnCart);
			   this->panel1->Controls->Add(this->btnSuppliers);
			   this->panel1->Controls->Add(this->btnInventory);
			   this->panel1->Controls->Add(this->btnProfile);
			   this->panel1->Controls->Add(this->btnRegister);
			   this->panel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			   this->panel1->Location = System::Drawing::Point(29, 104);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(188, 350);
			   this->panel1->TabIndex = 39;
			   this->panel1->WrapContents = false;
			   // 
			   // btnDashboard
			   // 
			   this->btnDashboard->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnDashboard->AccessibleName = L"Dashboard";
			   this->btnDashboard->AutoSizeBasedOnText = false;
			   this->btnDashboard->BackColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnDashboard->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnDashboard->BadgeValue = 0;
			   this->btnDashboard->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnDashboard->BorderColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->BorderWidth = 2;
			   this->btnDashboard->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDashboard.ButtonImage")));
			   this->btnDashboard->ButtonTextLeftPadding = 0;
			   this->btnDashboard->CanBeep = true;
			   this->btnDashboard->CanGlow = false;
			   this->btnDashboard->CanShake = true;
			   this->btnDashboard->ContextMenuStripEx = nullptr;
			   this->btnDashboard->CornerRadiusBottomLeft = 0;
			   this->btnDashboard->CornerRadiusBottomRight = 0;
			   this->btnDashboard->CornerRadiusTopLeft = 0;
			   this->btnDashboard->CornerRadiusTopRight = 0;
			   this->btnDashboard->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnDashboard->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnDashboard->EnableLongPress = false;
			   this->btnDashboard->EnableRippleEffect = false;
			   this->btnDashboard->EnableShadow = false;
			   this->btnDashboard->EnableTextWrapping = false;
			   this->btnDashboard->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnDashboard->ForeColor = System::Drawing::Color::White;
			   this->btnDashboard->GlowColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->GlowIntensity = 100;
			   this->btnDashboard->GlowRadius = 20;
			   this->btnDashboard->GradientBackground = false;
			   this->btnDashboard->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnDashboard->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnDashboard->HintText = nullptr;
			   this->btnDashboard->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDashboard->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnDashboard->HoverTransitionDuration = 250;
			   this->btnDashboard->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnDashboard->ImagePadding = 5;
			   this->btnDashboard->ImageSize = System::Drawing::Size(25, 25);
			   this->btnDashboard->IsRadial = false;
			   this->btnDashboard->IsReadOnly = false;
			   this->btnDashboard->IsToggleButton = false;
			   this->btnDashboard->IsToggled = false;
			   this->btnDashboard->Location = System::Drawing::Point(0, 0);
			   this->btnDashboard->LongPressDurationMS = 1000;
			   this->btnDashboard->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnDashboard->Name = L"btnDashboard";
			   this->btnDashboard->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDashboard->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->ParticleCount = 15;
			   this->btnDashboard->PressAnimationScale = 0.97F;
			   this->btnDashboard->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnDashboard->PressTransitionDuration = 150;
			   this->btnDashboard->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnDashboard->RippleColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->RippleOpacity = 0;
			   this->btnDashboard->RippleRadiusMultiplier = 0.6F;
			   this->btnDashboard->ShadowBlur = 5;
			   this->btnDashboard->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnDashboard->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnDashboard->ShakeDuration = 500;
			   this->btnDashboard->ShakeIntensity = 5;
			   this->btnDashboard->Size = System::Drawing::Size(188, 30);
			   this->btnDashboard->TabIndex = 26;
			   this->btnDashboard->Tag = L"dashboard";
			   this->btnDashboard->Text = L"Dashboard";
			   this->btnDashboard->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnDashboard->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnDashboard->TooltipText = nullptr;
			   this->btnDashboard->UltraFastPerformance = true;
			   this->btnDashboard->UseAdvancedRendering = true;
			   this->btnDashboard->UseParticles = false;
			   this->btnDashboard->Click += gcnew System::EventHandler(this, &MainForm::btnDashboard_Click);
			   // 
			   // btnProducts
			   // 
			   this->btnProducts->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnProducts->AccessibleName = L"Products";
			   this->btnProducts->AutoSizeBasedOnText = false;
			   this->btnProducts->BackColor = System::Drawing::Color::Transparent;
			   this->btnProducts->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnProducts->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnProducts->BadgeValue = 0;
			   this->btnProducts->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnProducts->BorderColor = System::Drawing::Color::Transparent;
			   this->btnProducts->BorderWidth = 2;
			   this->btnProducts->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnProducts->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnProducts.ButtonImage")));
			   this->btnProducts->ButtonTextLeftPadding = 0;
			   this->btnProducts->CanBeep = true;
			   this->btnProducts->CanGlow = false;
			   this->btnProducts->CanShake = true;
			   this->btnProducts->ContextMenuStripEx = nullptr;
			   this->btnProducts->CornerRadiusBottomLeft = 0;
			   this->btnProducts->CornerRadiusBottomRight = 0;
			   this->btnProducts->CornerRadiusTopLeft = 0;
			   this->btnProducts->CornerRadiusTopRight = 0;
			   this->btnProducts->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnProducts->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnProducts->EnableLongPress = false;
			   this->btnProducts->EnableRippleEffect = true;
			   this->btnProducts->EnableShadow = false;
			   this->btnProducts->EnableTextWrapping = false;
			   this->btnProducts->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnProducts->ForeColor = System::Drawing::Color::White;
			   this->btnProducts->GlowColor = System::Drawing::Color::Transparent;
			   this->btnProducts->GlowIntensity = 100;
			   this->btnProducts->GlowRadius = 20;
			   this->btnProducts->GradientBackground = false;
			   this->btnProducts->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnProducts->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnProducts->HintText = nullptr;
			   this->btnProducts->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnProducts->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProducts->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnProducts->HoverTransitionDuration = 250;
			   this->btnProducts->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnProducts->ImagePadding = 5;
			   this->btnProducts->ImageSize = System::Drawing::Size(25, 25);
			   this->btnProducts->IsRadial = false;
			   this->btnProducts->IsReadOnly = false;
			   this->btnProducts->IsToggleButton = false;
			   this->btnProducts->IsToggled = false;
			   this->btnProducts->Location = System::Drawing::Point(0, 45);
			   this->btnProducts->LongPressDurationMS = 1000;
			   this->btnProducts->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnProducts->Name = L"btnProducts";
			   this->btnProducts->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProducts->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnProducts->ParticleCount = 15;
			   this->btnProducts->PressAnimationScale = 0.97F;
			   this->btnProducts->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnProducts->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProducts->PressTransitionDuration = 150;
			   this->btnProducts->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnProducts->RippleColor = System::Drawing::Color::Transparent;
			   this->btnProducts->RippleOpacity = 0;
			   this->btnProducts->RippleRadiusMultiplier = 0.6F;
			   this->btnProducts->ShadowBlur = 5;
			   this->btnProducts->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnProducts->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnProducts->ShakeDuration = 500;
			   this->btnProducts->ShakeIntensity = 5;
			   this->btnProducts->Size = System::Drawing::Size(188, 30);
			   this->btnProducts->TabIndex = 27;
			   this->btnProducts->Tag = L"products";
			   this->btnProducts->Text = L"Products";
			   this->btnProducts->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnProducts->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnProducts->TooltipText = nullptr;
			   this->btnProducts->UltraFastPerformance = true;
			   this->btnProducts->UseAdvancedRendering = true;
			   this->btnProducts->UseParticles = false;
			   this->btnProducts->Click += gcnew System::EventHandler(this, &MainForm::btnProducts_Click);
			   // 
			   // btnMyRequests
			   // 
			   this->btnMyRequests->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnMyRequests->AccessibleName = L"My Requests";
			   this->btnMyRequests->AutoSizeBasedOnText = false;
			   this->btnMyRequests->BackColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnMyRequests->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnMyRequests->BadgeValue = 0;
			   this->btnMyRequests->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnMyRequests->BorderColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->BorderWidth = 1;
			   this->btnMyRequests->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnMyRequests.ButtonImage")));
			   this->btnMyRequests->ButtonTextLeftPadding = 0;
			   this->btnMyRequests->CanBeep = true;
			   this->btnMyRequests->CanGlow = false;
			   this->btnMyRequests->CanShake = true;
			   this->btnMyRequests->ContextMenuStripEx = nullptr;
			   this->btnMyRequests->CornerRadiusBottomLeft = 0;
			   this->btnMyRequests->CornerRadiusBottomRight = 0;
			   this->btnMyRequests->CornerRadiusTopLeft = 0;
			   this->btnMyRequests->CornerRadiusTopRight = 0;
			   this->btnMyRequests->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnMyRequests->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnMyRequests->EnableLongPress = false;
			   this->btnMyRequests->EnableRippleEffect = true;
			   this->btnMyRequests->EnableShadow = false;
			   this->btnMyRequests->EnableTextWrapping = false;
			   this->btnMyRequests->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnMyRequests->ForeColor = System::Drawing::Color::White;
			   this->btnMyRequests->GlowColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->GlowIntensity = 100;
			   this->btnMyRequests->GlowRadius = 20;
			   this->btnMyRequests->GradientBackground = false;
			   this->btnMyRequests->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnMyRequests->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnMyRequests->HintText = nullptr;
			   this->btnMyRequests->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnMyRequests->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnMyRequests->HoverTransitionDuration = 250;
			   this->btnMyRequests->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnMyRequests->ImagePadding = 5;
			   this->btnMyRequests->ImageSize = System::Drawing::Size(25, 25);
			   this->btnMyRequests->IsRadial = false;
			   this->btnMyRequests->IsReadOnly = false;
			   this->btnMyRequests->IsToggleButton = false;
			   this->btnMyRequests->IsToggled = false;
			   this->btnMyRequests->Location = System::Drawing::Point(0, 90);
			   this->btnMyRequests->LongPressDurationMS = 1000;
			   this->btnMyRequests->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnMyRequests->Name = L"btnMyRequests";
			   this->btnMyRequests->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnMyRequests->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->ParticleCount = 15;
			   this->btnMyRequests->PressAnimationScale = 0.97F;
			   this->btnMyRequests->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnMyRequests->PressTransitionDuration = 150;
			   this->btnMyRequests->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnMyRequests->RippleColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->RippleOpacity = 0;
			   this->btnMyRequests->RippleRadiusMultiplier = 0.6F;
			   this->btnMyRequests->ShadowBlur = 5;
			   this->btnMyRequests->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnMyRequests->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnMyRequests->ShakeDuration = 500;
			   this->btnMyRequests->ShakeIntensity = 5;
			   this->btnMyRequests->Size = System::Drawing::Size(188, 30);
			   this->btnMyRequests->TabIndex = 28;
			   this->btnMyRequests->Tag = L"request";
			   this->btnMyRequests->Text = L"My Requests";
			   this->btnMyRequests->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnMyRequests->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnMyRequests->TooltipText = nullptr;
			   this->btnMyRequests->UltraFastPerformance = true;
			   this->btnMyRequests->UseAdvancedRendering = true;
			   this->btnMyRequests->UseParticles = false;
			   this->btnMyRequests->Click += gcnew System::EventHandler(this, &MainForm::btnMyRequests_Click);
			   // 
			   // btnCart
			   // 
			   this->btnCart->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnCart->AccessibleName = L"Request Cart";
			   this->btnCart->AutoSizeBasedOnText = false;
			   this->btnCart->BackColor = System::Drawing::Color::Transparent;
			   this->btnCart->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnCart->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnCart->BadgeValue = 0;
			   this->btnCart->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnCart->BorderColor = System::Drawing::Color::Transparent;
			   this->btnCart->BorderWidth = 1;
			   this->btnCart->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnCart->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnCart.ButtonImage")));
			   this->btnCart->ButtonTextLeftPadding = 0;
			   this->btnCart->CanBeep = true;
			   this->btnCart->CanGlow = false;
			   this->btnCart->CanShake = true;
			   this->btnCart->ContextMenuStripEx = nullptr;
			   this->btnCart->CornerRadiusBottomLeft = 0;
			   this->btnCart->CornerRadiusBottomRight = 0;
			   this->btnCart->CornerRadiusTopLeft = 0;
			   this->btnCart->CornerRadiusTopRight = 0;
			   this->btnCart->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnCart->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnCart->EnableLongPress = false;
			   this->btnCart->EnableRippleEffect = true;
			   this->btnCart->EnableShadow = false;
			   this->btnCart->EnableTextWrapping = false;
			   this->btnCart->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnCart->ForeColor = System::Drawing::Color::White;
			   this->btnCart->GlowColor = System::Drawing::Color::Transparent;
			   this->btnCart->GlowIntensity = 100;
			   this->btnCart->GlowRadius = 20;
			   this->btnCart->GradientBackground = false;
			   this->btnCart->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnCart->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnCart->HintText = nullptr;
			   this->btnCart->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnCart->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnCart->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnCart->HoverTransitionDuration = 250;
			   this->btnCart->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnCart->ImagePadding = 5;
			   this->btnCart->ImageSize = System::Drawing::Size(25, 25);
			   this->btnCart->IsRadial = false;
			   this->btnCart->IsReadOnly = false;
			   this->btnCart->IsToggleButton = false;
			   this->btnCart->IsToggled = false;
			   this->btnCart->Location = System::Drawing::Point(0, 135);
			   this->btnCart->LongPressDurationMS = 1000;
			   this->btnCart->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnCart->Name = L"btnCart";
			   this->btnCart->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnCart->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnCart->ParticleCount = 15;
			   this->btnCart->PressAnimationScale = 0.97F;
			   this->btnCart->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnCart->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnCart->PressTransitionDuration = 150;
			   this->btnCart->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnCart->RippleColor = System::Drawing::Color::Transparent;
			   this->btnCart->RippleOpacity = 0;
			   this->btnCart->RippleRadiusMultiplier = 0.6F;
			   this->btnCart->ShadowBlur = 5;
			   this->btnCart->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnCart->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnCart->ShakeDuration = 500;
			   this->btnCart->ShakeIntensity = 5;
			   this->btnCart->Size = System::Drawing::Size(188, 30);
			   this->btnCart->TabIndex = 29;
			   this->btnCart->Tag = L"request_cart";
			   this->btnCart->Text = L"Request Cart";
			   this->btnCart->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnCart->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnCart->TooltipText = nullptr;
			   this->btnCart->UltraFastPerformance = true;
			   this->btnCart->UseAdvancedRendering = true;
			   this->btnCart->UseParticles = false;
			   this->btnCart->Click += gcnew System::EventHandler(this, &MainForm::btnCart_Click);
			   // 
			   // btnSuppliers
			   // 
			   this->btnSuppliers->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnSuppliers->AccessibleName = L"Suppliers";
			   this->btnSuppliers->AutoSizeBasedOnText = false;
			   this->btnSuppliers->BackColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnSuppliers->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnSuppliers->BadgeValue = 0;
			   this->btnSuppliers->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnSuppliers->BorderColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->BorderWidth = 1;
			   this->btnSuppliers->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSuppliers.ButtonImage")));
			   this->btnSuppliers->ButtonTextLeftPadding = 0;
			   this->btnSuppliers->CanBeep = true;
			   this->btnSuppliers->CanGlow = false;
			   this->btnSuppliers->CanShake = true;
			   this->btnSuppliers->ContextMenuStripEx = nullptr;
			   this->btnSuppliers->CornerRadiusBottomLeft = 0;
			   this->btnSuppliers->CornerRadiusBottomRight = 0;
			   this->btnSuppliers->CornerRadiusTopLeft = 0;
			   this->btnSuppliers->CornerRadiusTopRight = 0;
			   this->btnSuppliers->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnSuppliers->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnSuppliers->EnableLongPress = false;
			   this->btnSuppliers->EnableRippleEffect = true;
			   this->btnSuppliers->EnableShadow = false;
			   this->btnSuppliers->EnableTextWrapping = false;
			   this->btnSuppliers->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnSuppliers->ForeColor = System::Drawing::Color::White;
			   this->btnSuppliers->GlowColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->GlowIntensity = 100;
			   this->btnSuppliers->GlowRadius = 20;
			   this->btnSuppliers->GradientBackground = false;
			   this->btnSuppliers->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnSuppliers->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnSuppliers->HintText = nullptr;
			   this->btnSuppliers->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSuppliers->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnSuppliers->HoverTransitionDuration = 250;
			   this->btnSuppliers->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnSuppliers->ImagePadding = 5;
			   this->btnSuppliers->ImageSize = System::Drawing::Size(25, 25);
			   this->btnSuppliers->IsRadial = false;
			   this->btnSuppliers->IsReadOnly = false;
			   this->btnSuppliers->IsToggleButton = false;
			   this->btnSuppliers->IsToggled = false;
			   this->btnSuppliers->Location = System::Drawing::Point(0, 180);
			   this->btnSuppliers->LongPressDurationMS = 1000;
			   this->btnSuppliers->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnSuppliers->Name = L"btnSuppliers";
			   this->btnSuppliers->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSuppliers->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->ParticleCount = 15;
			   this->btnSuppliers->PressAnimationScale = 0.97F;
			   this->btnSuppliers->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnSuppliers->PressTransitionDuration = 150;
			   this->btnSuppliers->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnSuppliers->RippleColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->RippleOpacity = 0;
			   this->btnSuppliers->RippleRadiusMultiplier = 0.6F;
			   this->btnSuppliers->ShadowBlur = 5;
			   this->btnSuppliers->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnSuppliers->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnSuppliers->ShakeDuration = 500;
			   this->btnSuppliers->ShakeIntensity = 5;
			   this->btnSuppliers->Size = System::Drawing::Size(188, 30);
			   this->btnSuppliers->TabIndex = 33;
			   this->btnSuppliers->Tag = L"supplier";
			   this->btnSuppliers->Text = L"Suppliers";
			   this->btnSuppliers->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnSuppliers->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnSuppliers->TooltipText = nullptr;
			   this->btnSuppliers->UltraFastPerformance = true;
			   this->btnSuppliers->UseAdvancedRendering = true;
			   this->btnSuppliers->UseParticles = false;
			   this->btnSuppliers->Click += gcnew System::EventHandler(this, &MainForm::btnSuppliers_Click);
			   // 
			   // btnInventory
			   // 
			   this->btnInventory->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnInventory->AccessibleName = L"Inventory";
			   this->btnInventory->AutoSizeBasedOnText = false;
			   this->btnInventory->BackColor = System::Drawing::Color::Transparent;
			   this->btnInventory->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnInventory->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnInventory->BadgeValue = 0;
			   this->btnInventory->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnInventory->BorderColor = System::Drawing::Color::Transparent;
			   this->btnInventory->BorderWidth = 1;
			   this->btnInventory->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnInventory->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnInventory.ButtonImage")));
			   this->btnInventory->ButtonTextLeftPadding = 0;
			   this->btnInventory->CanBeep = true;
			   this->btnInventory->CanGlow = false;
			   this->btnInventory->CanShake = true;
			   this->btnInventory->ContextMenuStripEx = nullptr;
			   this->btnInventory->CornerRadiusBottomLeft = 0;
			   this->btnInventory->CornerRadiusBottomRight = 0;
			   this->btnInventory->CornerRadiusTopLeft = 0;
			   this->btnInventory->CornerRadiusTopRight = 0;
			   this->btnInventory->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnInventory->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnInventory->EnableLongPress = false;
			   this->btnInventory->EnableRippleEffect = true;
			   this->btnInventory->EnableShadow = false;
			   this->btnInventory->EnableTextWrapping = false;
			   this->btnInventory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnInventory->ForeColor = System::Drawing::Color::White;
			   this->btnInventory->GlowColor = System::Drawing::Color::Transparent;
			   this->btnInventory->GlowIntensity = 100;
			   this->btnInventory->GlowRadius = 20;
			   this->btnInventory->GradientBackground = false;
			   this->btnInventory->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnInventory->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnInventory->HintText = nullptr;
			   this->btnInventory->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnInventory->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnInventory->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnInventory->HoverTransitionDuration = 250;
			   this->btnInventory->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnInventory->ImagePadding = 5;
			   this->btnInventory->ImageSize = System::Drawing::Size(25, 25);
			   this->btnInventory->IsRadial = false;
			   this->btnInventory->IsReadOnly = false;
			   this->btnInventory->IsToggleButton = false;
			   this->btnInventory->IsToggled = false;
			   this->btnInventory->Location = System::Drawing::Point(0, 225);
			   this->btnInventory->LongPressDurationMS = 1000;
			   this->btnInventory->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnInventory->Name = L"btnInventory";
			   this->btnInventory->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnInventory->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnInventory->ParticleCount = 15;
			   this->btnInventory->PressAnimationScale = 0.97F;
			   this->btnInventory->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnInventory->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnInventory->PressTransitionDuration = 150;
			   this->btnInventory->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnInventory->RippleColor = System::Drawing::Color::Transparent;
			   this->btnInventory->RippleOpacity = 0;
			   this->btnInventory->RippleRadiusMultiplier = 0.6F;
			   this->btnInventory->ShadowBlur = 5;
			   this->btnInventory->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnInventory->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnInventory->ShakeDuration = 500;
			   this->btnInventory->ShakeIntensity = 5;
			   this->btnInventory->Size = System::Drawing::Size(188, 30);
			   this->btnInventory->TabIndex = 34;
			   this->btnInventory->Tag = L"inventory";
			   this->btnInventory->Text = L"Inventory";
			   this->btnInventory->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnInventory->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnInventory->TooltipText = nullptr;
			   this->btnInventory->UltraFastPerformance = true;
			   this->btnInventory->UseAdvancedRendering = true;
			   this->btnInventory->UseParticles = false;
			   this->btnInventory->Click += gcnew System::EventHandler(this, &MainForm::btnInventory_Click);
			   // 
			   // btnProfile
			   // 
			   this->btnProfile->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnProfile->AccessibleName = L"Profile";
			   this->btnProfile->AutoSizeBasedOnText = false;
			   this->btnProfile->BackColor = System::Drawing::Color::Transparent;
			   this->btnProfile->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnProfile->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnProfile->BadgeValue = 0;
			   this->btnProfile->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnProfile->BorderColor = System::Drawing::Color::Transparent;
			   this->btnProfile->BorderWidth = 1;
			   this->btnProfile->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnProfile->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnProfile.ButtonImage")));
			   this->btnProfile->ButtonTextLeftPadding = 0;
			   this->btnProfile->CanBeep = true;
			   this->btnProfile->CanGlow = false;
			   this->btnProfile->CanShake = true;
			   this->btnProfile->ContextMenuStripEx = nullptr;
			   this->btnProfile->CornerRadiusBottomLeft = 0;
			   this->btnProfile->CornerRadiusBottomRight = 0;
			   this->btnProfile->CornerRadiusTopLeft = 0;
			   this->btnProfile->CornerRadiusTopRight = 0;
			   this->btnProfile->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnProfile->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnProfile->EnableLongPress = false;
			   this->btnProfile->EnableRippleEffect = true;
			   this->btnProfile->EnableShadow = false;
			   this->btnProfile->EnableTextWrapping = false;
			   this->btnProfile->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnProfile->ForeColor = System::Drawing::Color::White;
			   this->btnProfile->GlowColor = System::Drawing::Color::Transparent;
			   this->btnProfile->GlowIntensity = 100;
			   this->btnProfile->GlowRadius = 20;
			   this->btnProfile->GradientBackground = false;
			   this->btnProfile->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnProfile->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnProfile->HintText = nullptr;
			   this->btnProfile->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnProfile->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProfile->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnProfile->HoverTransitionDuration = 250;
			   this->btnProfile->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnProfile->ImagePadding = 5;
			   this->btnProfile->ImageSize = System::Drawing::Size(25, 25);
			   this->btnProfile->IsRadial = false;
			   this->btnProfile->IsReadOnly = false;
			   this->btnProfile->IsToggleButton = false;
			   this->btnProfile->IsToggled = false;
			   this->btnProfile->Location = System::Drawing::Point(0, 270);
			   this->btnProfile->LongPressDurationMS = 1000;
			   this->btnProfile->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnProfile->Name = L"btnProfile";
			   this->btnProfile->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProfile->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnProfile->ParticleCount = 15;
			   this->btnProfile->PressAnimationScale = 0.97F;
			   this->btnProfile->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnProfile->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnProfile->PressTransitionDuration = 150;
			   this->btnProfile->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnProfile->RippleColor = System::Drawing::Color::Transparent;
			   this->btnProfile->RippleOpacity = 0;
			   this->btnProfile->RippleRadiusMultiplier = 0.6F;
			   this->btnProfile->ShadowBlur = 5;
			   this->btnProfile->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnProfile->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnProfile->ShakeDuration = 500;
			   this->btnProfile->ShakeIntensity = 5;
			   this->btnProfile->Size = System::Drawing::Size(188, 30);
			   this->btnProfile->TabIndex = 30;
			   this->btnProfile->Tag = L"profile";
			   this->btnProfile->Text = L"Profile";
			   this->btnProfile->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnProfile->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnProfile->TooltipText = nullptr;
			   this->btnProfile->UltraFastPerformance = true;
			   this->btnProfile->UseAdvancedRendering = true;
			   this->btnProfile->UseParticles = false;
			   this->btnProfile->Click += gcnew System::EventHandler(this, &MainForm::btnProfile_Click);
			   // 
			   // btnRegister
			   // 
			   this->btnRegister->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				   L"";
			   this->btnRegister->AccessibleName = L"Register";
			   this->btnRegister->AutoSizeBasedOnText = false;
			   this->btnRegister->BackColor = System::Drawing::Color::Transparent;
			   this->btnRegister->BadgeBackColor = System::Drawing::Color::Black;
			   this->btnRegister->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnRegister->BadgeValue = 0;
			   this->btnRegister->BadgeValueForeColor = System::Drawing::Color::White;
			   this->btnRegister->BorderColor = System::Drawing::Color::Transparent;
			   this->btnRegister->BorderWidth = 1;
			   this->btnRegister->ButtonBackColor = System::Drawing::Color::Transparent;
			   this->btnRegister->ButtonImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnRegister.ButtonImage")));
			   this->btnRegister->ButtonTextLeftPadding = 0;
			   this->btnRegister->CanBeep = true;
			   this->btnRegister->CanGlow = false;
			   this->btnRegister->CanShake = true;
			   this->btnRegister->ContextMenuStripEx = nullptr;
			   this->btnRegister->CornerRadiusBottomLeft = 0;
			   this->btnRegister->CornerRadiusBottomRight = 0;
			   this->btnRegister->CornerRadiusTopLeft = 0;
			   this->btnRegister->CornerRadiusTopRight = 0;
			   this->btnRegister->CustomCursor = System::Windows::Forms::Cursors::Default;
			   this->btnRegister->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				   static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			   this->btnRegister->EnableLongPress = false;
			   this->btnRegister->EnableRippleEffect = true;
			   this->btnRegister->EnableShadow = false;
			   this->btnRegister->EnableTextWrapping = false;
			   this->btnRegister->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btnRegister->ForeColor = System::Drawing::Color::White;
			   this->btnRegister->GlowColor = System::Drawing::Color::Transparent;
			   this->btnRegister->GlowIntensity = 100;
			   this->btnRegister->GlowRadius = 20;
			   this->btnRegister->GradientBackground = false;
			   this->btnRegister->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				   static_cast<System::Int32>(static_cast<System::Byte>(64)));
			   this->btnRegister->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			   this->btnRegister->HintText = nullptr;
			   this->btnRegister->HoverBackColor = System::Drawing::Color::Transparent;
			   this->btnRegister->HoverFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRegister->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)),
				   static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnRegister->HoverTransitionDuration = 250;
			   this->btnRegister->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnRegister->ImagePadding = 5;
			   this->btnRegister->ImageSize = System::Drawing::Size(25, 25);
			   this->btnRegister->IsRadial = false;
			   this->btnRegister->IsReadOnly = false;
			   this->btnRegister->IsToggleButton = false;
			   this->btnRegister->IsToggled = false;
			   this->btnRegister->Location = System::Drawing::Point(0, 315);
			   this->btnRegister->LongPressDurationMS = 1000;
			   this->btnRegister->Margin = System::Windows::Forms::Padding(0, 0, 0, 15);
			   this->btnRegister->Name = L"btnRegister";
			   this->btnRegister->NormalFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRegister->ParticleColor = System::Drawing::Color::Transparent;
			   this->btnRegister->ParticleCount = 15;
			   this->btnRegister->PressAnimationScale = 0.97F;
			   this->btnRegister->PressedBackColor = System::Drawing::Color::Transparent;
			   this->btnRegister->PressedFontStyle = System::Drawing::FontStyle::Regular;
			   this->btnRegister->PressTransitionDuration = 150;
			   this->btnRegister->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				   static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			   this->btnRegister->RippleColor = System::Drawing::Color::Transparent;
			   this->btnRegister->RippleOpacity = 0;
			   this->btnRegister->RippleRadiusMultiplier = 0.6F;
			   this->btnRegister->ShadowBlur = 5;
			   this->btnRegister->ShadowColor = System::Drawing::Color::Transparent;
			   this->btnRegister->ShadowOffset = System::Drawing::Point(0, 2);
			   this->btnRegister->ShakeDuration = 500;
			   this->btnRegister->ShakeIntensity = 5;
			   this->btnRegister->Size = System::Drawing::Size(188, 30);
			   this->btnRegister->TabIndex = 38;
			   this->btnRegister->Tag = L"register";
			   this->btnRegister->Text = L"Register";
			   this->btnRegister->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnRegister->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(190)),
				   static_cast<System::Int32>(static_cast<System::Byte>(191)));
			   this->btnRegister->TooltipText = nullptr;
			   this->btnRegister->UltraFastPerformance = true;
			   this->btnRegister->UseAdvancedRendering = true;
			   this->btnRegister->UseParticles = false;
			   this->btnRegister->Click += gcnew System::EventHandler(this, &MainForm::btnRegister_Click);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::White;
			   this->ClientSize = System::Drawing::Size(1184, 701);
			   this->Controls->Add(this->panelPageHost);
			   this->Controls->Add(this->panelHeader);
			   this->Controls->Add(this->pnlSideBar);
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->MinimumSize = System::Drawing::Size(1200, 740);
			   this->Name = L"MainForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"IntraProcure – Internal Procurement System";
			   this->panelHeader->ResumeLayout(false);
			   this->panelHeader->PerformLayout();
			   this->panelPageHost->ResumeLayout(false);
			   this->pnlSideBar->ResumeLayout(false);
			   this->pnlSideBar->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->panel1->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion

		   // ========= HELPER METHODS =========
	private:
		void LoadChildForm(System::Windows::Forms::Form^ child)
		{
			if (_currentChild != nullptr)
				_currentChild->Close();

			_currentChild = child;
			child->TopLevel = false;
			child->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			child->Dock = System::Windows::Forms::DockStyle::Fill;

			this->panelCard->Controls->Clear();
			this->panelCard->Controls->Add(child);
			child->Show();
		}

		// Load user data and set default page
		void LoadData() {
			lblDate->Text = System::DateTime::Now.ToString("dd/MM/yyyy");

			RefreshUserHeader();

			// Default page
			if (Session::IsManager)
			{
				LoadChildForm(gcnew ManagerPanelForm());
				SetActiveNavButton(btnDashboard);
			}
			else
			{
				LoadChildForm(gcnew HomeForm());
				SetActiveNavButton(btnProducts);
			}
		}

	private: void OnCurrentUserChanged()
	{
		// Whenever Session changes, update header labels & picture
		RefreshUserHeader();
	}

	private: void RefreshUserHeader()
	{
		try
		{
			// Name
			if (!String::IsNullOrEmpty(Session::FullName))
				lblUserName->Text = Session::FullName;
			else if (!String::IsNullOrEmpty(Session::Username))
				lblUserName->Text = Session::Username;
			else
				lblUserName->Text = L"User";

			// Role
			if (Session::IsAdministrator)
				lblUserRole->Text = L"Administrator";
			else if (Session::IsManager)
				lblUserRole->Text = L"Manager";
			else
				lblUserRole->Text = L"Employee";

			// Picture
			array<System::Byte>^ ProfileImageBytes;
			ProfileImageBytes = Session::Photo;

			if (ProfileImageBytes != nullptr && ProfileImageBytes->Length > 0)
			{
				try
				{
					MemoryStream^ ms = gcnew MemoryStream(ProfileImageBytes);
					picUser->Image = Image::FromStream(ms);
				}
				catch (...)
				{
					// If corrupt image, just ignore and keep default avatar
					ProfileImageBytes = nullptr;
					picUser->Image = LoadImageFromResource("profile_purple");
				}
			}
		}
		catch (Exception^)
		{
			// Avoid UI crash because of bad image data
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

		   void SetActiveNavButton(SiticoneNetFrameworkUI::SiticoneButton^ btn)
		   {
			   // Reset old active button
			   if (_activeNavButton != nullptr)
			   {
				   _activeNavButton->TextColor = Color::FromArgb(193, 190, 191);
				   _activeNavButton->HoverTextColor = Color::FromArgb(193, 190, 191);

				   // Reset to gray icon (inactive)
				   String^ inactiveIcon = _activeNavButton->Tag->ToString() + "_grey";
				   _activeNavButton->ButtonImage = LoadImageFromResource(inactiveIcon);
			   }

			   // Set new active button
			   _activeNavButton = btn;
			   String^ activeIcon = _activeNavButton->Tag->ToString() + "_white";
			   btn->TextColor = Color::White;
			   btn->HoverTextColor = Color::White;

			   // Set active icon (colored)195219
			   btn->ButtonImage = LoadImageFromResource(activeIcon);

			   // Move selection panel
			   panelNavHighlight->Visible = true;
			   panelNavHighlight->Top = btn->Top + 104;
			   panelNavHighlight->Height = btn->Height;
		   }

		   void ApplyRoleSecurity()
		   {
			   // Only Admin can manage users & suppliers
			   btnSuppliers->Visible = Session::IsAdministrator;

			   // Only Admin can regiter users
			   btnRegister->Visible = Session::IsAdministrator;

			   // Manager & Admin can access ManagerPanel
			   btnDashboard->Visible = (Session::IsManager || Session::IsAdministrator);

			   // Profile and Home available to everyone
			   btnProducts->Visible = true;
			   btnProfile->Visible = true;
		   }

		   // ========= NAV EVENTS =========
	private: System::Void btnDashboard_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (Session::IsManager)
		{
			LoadChildForm(gcnew ManagerPanelForm());
		}
		else
		{
			LoadChildForm(gcnew MyRequestsForm());
		}
		SetActiveNavButton(btnDashboard);
	}

	private: System::Void btnProducts_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LoadChildForm(gcnew HomeForm());
		SetActiveNavButton(btnProducts);
	}

	private: System::Void btnMyRequests_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LoadChildForm(gcnew MyRequestsForm());
		SetActiveNavButton(btnMyRequests);
	}

	private: System::Void btnCart_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LoadChildForm(gcnew RequestCartForm());
		SetActiveNavButton(btnCart);
	}
	private: System::Void btnProfile_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LoadChildForm(gcnew ProfileForm());
		SetActiveNavButton(btnProfile);
	}

	private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto result = MessageBox::Show(
			L"Are you sure you want to log out?",
			L"Log Out",
			MessageBoxButtons::YesNo,
			MessageBoxIcon::Question);

		if (result == System::Windows::Forms::DialogResult::Yes)
		{
			Application::Restart();
		}
	}
	private: System::Void btnSuppliers_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadChildForm(gcnew SuppliersForm());
		SetActiveNavButton(btnSuppliers);
	}
	private: System::Void btnInventory_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadChildForm(gcnew InventoryForm());
		SetActiveNavButton(btnInventory);
	}
	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadChildForm(gcnew RegisterForm());
		SetActiveNavButton(btnRegister);
	}
	};
}
