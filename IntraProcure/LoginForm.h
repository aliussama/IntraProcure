#pragma once

#include "MainForm.h"
#include "RegisterForm.h"
#include "ForgotPasswordForm.h"
#include "UiStyler.h"
#include "Config.h"
#include "EmployeeManager.h"
#include "Employee.h"
#include "Session.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();

			UiStyler::StyleTextBox(txtUsername);
			UiStyler::StyleTextBox(txtPassword);
			UiStyler::StylePrimaryButton(btnLogin);

			this->KeyPreview = true;

			lblLoginStatus->Text = L"";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblAppName;
	private: System::Windows::Forms::Label^ lblSignIn;
	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtUsername;
	protected:

	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::Label^ lblPassword;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtPassword;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnLogin;

	private: SiticoneNetFrameworkUI::SiticonePanel^ panelCard;
	private: System::Windows::Forms::CheckBox^ chkShowPassword;
	private: System::Windows::Forms::Label^ lblForgotPassword;
	private: System::Windows::Forms::Label^ lblLoginStatus;

	private:
		bool _isLoggingIn = false;
	private: System::Windows::Forms::Label^ lblRegister;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->lblAppName = (gcnew System::Windows::Forms::Label());
			this->lblSignIn = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->btnLogin = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->panelCard = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->lblRegister = (gcnew System::Windows::Forms::Label());
			this->lblForgotPassword = (gcnew System::Windows::Forms::Label());
			this->lblLoginStatus = (gcnew System::Windows::Forms::Label());
			this->chkShowPassword = (gcnew System::Windows::Forms::CheckBox());
			this->panelCard->SuspendLayout();
			this->SuspendLayout();
			//
			// lblAppName
			//
			this->lblAppName->AutoSize = true;
			this->lblAppName->BackColor = System::Drawing::Color::Transparent;
			this->lblAppName->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold));
			this->lblAppName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblAppName->Location = System::Drawing::Point(145, 20);
			this->lblAppName->Name = L"lblAppName";
			this->lblAppName->Size = System::Drawing::Size(136, 30);
			this->lblAppName->TabIndex = 0;
			this->lblAppName->Text = L"IntraProcure";
			//
			// lblSignIn
			//
			this->lblSignIn->AutoSize = true;
			this->lblSignIn->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSignIn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblSignIn->Location = System::Drawing::Point(10, 10);
			this->lblSignIn->Name = L"lblSignIn";
			this->lblSignIn->Size = System::Drawing::Size(59, 21);
			this->lblSignIn->TabIndex = 1;
			this->lblSignIn->Text = L"Sign in";
			//
			// txtUsername
			//
			this->txtUsername->AccessibleDescription = L"A customizable text input field.";
			this->txtUsername->AccessibleName = L"Text Box";
			this->txtUsername->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtUsername->BackColor = System::Drawing::Color::Transparent;
			this->txtUsername->BlinkCount = 3;
			this->txtUsername->BlinkShadow = false;
			this->txtUsername->BorderColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->txtUsername->BorderColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->txtUsername->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUsername->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUsername->CanShake = true;
			this->txtUsername->ContinuousBlink = false;
			this->txtUsername->CornerRadiusBottomLeft = 6;
			this->txtUsername->CornerRadiusBottomRight = 6;
			this->txtUsername->CornerRadiusTopLeft = 6;
			this->txtUsername->CornerRadiusTopRight = 6;
			this->txtUsername->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtUsername->CursorBlinkRate = 500;
			this->txtUsername->CursorColor = System::Drawing::Color::Black;
			this->txtUsername->CursorHeight = 26;
			this->txtUsername->CursorOffset = 0;
			this->txtUsername->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtUsername->CursorWidth = 1;
			this->txtUsername->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtUsername->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtUsername->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtUsername->EnableDropShadow = false;
			this->txtUsername->FillColor1 = System::Drawing::Color::White;
			this->txtUsername->FillColor2 = System::Drawing::Color::White;
			this->txtUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtUsername->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->txtUsername->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtUsername->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtUsername->IsEnabled = true;
			this->txtUsername->Location = System::Drawing::Point(10, 62);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtUsername->PlaceholderText = L"Enter your username…";
			this->txtUsername->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtUsername->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtUsername->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtUsername->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtUsername->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtUsername->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUsername->ShadowAnimationDuration = 1;
			this->txtUsername->ShadowBlur = 10;
			this->txtUsername->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtUsername->Size = System::Drawing::Size(300, 26);
			this->txtUsername->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtUsername->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUsername->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtUsername->SolidFillColor = System::Drawing::Color::White;
			this->txtUsername->TabIndex = 2;
			this->txtUsername->TextPadding = System::Windows::Forms::Padding(10, 0, 6, 0);
			this->txtUsername->ValidationErrorMessage = L"Invalid input.";
			this->txtUsername->ValidationFunction = nullptr;
			//
			// lblUsername
			//
			this->lblUsername->AutoSize = true;
			this->lblUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(178)));
			this->lblUsername->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->lblUsername->Location = System::Drawing::Point(10, 45);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(60, 15);
			this->lblUsername->TabIndex = 4;
			this->lblUsername->Text = L"Username";
			//
			// lblPassword
			//
			this->lblPassword->AutoSize = true;
			this->lblPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->lblPassword->Location = System::Drawing::Point(10, 98);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(57, 15);
			this->lblPassword->TabIndex = 6;
			this->lblPassword->Text = L"Password";
			//
			// txtPassword
			//
			this->txtPassword->AccessibleDescription = L"A customizable text input field.";
			this->txtPassword->AccessibleName = L"Text Box";
			this->txtPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtPassword->BackColor = System::Drawing::Color::Transparent;
			this->txtPassword->BlinkCount = 3;
			this->txtPassword->BlinkShadow = false;
			this->txtPassword->BorderColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->txtPassword->BorderColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->txtPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtPassword->CanShake = true;
			this->txtPassword->ContinuousBlink = false;
			this->txtPassword->CornerRadiusBottomLeft = 6;
			this->txtPassword->CornerRadiusBottomRight = 6;
			this->txtPassword->CornerRadiusTopLeft = 6;
			this->txtPassword->CornerRadiusTopRight = 6;
			this->txtPassword->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtPassword->CursorBlinkRate = 500;
			this->txtPassword->CursorColor = System::Drawing::Color::Black;
			this->txtPassword->CursorHeight = 26;
			this->txtPassword->CursorOffset = 0;
			this->txtPassword->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtPassword->CursorWidth = 1;
			this->txtPassword->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtPassword->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtPassword->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtPassword->EnableDropShadow = false;
			this->txtPassword->FillColor1 = System::Drawing::Color::White;
			this->txtPassword->FillColor2 = System::Drawing::Color::White;
			this->txtPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->txtPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtPassword->IsEnabled = true;
			this->txtPassword->Location = System::Drawing::Point(10, 115);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtPassword->PlaceholderText = L"Enter your password…";
			this->txtPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtPassword->ShadowAnimationDuration = 1;
			this->txtPassword->ShadowBlur = 10;
			this->txtPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtPassword->Size = System::Drawing::Size(300, 26);
			this->txtPassword->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtPassword->SolidFillColor = System::Drawing::Color::White;
			this->txtPassword->TabIndex = 5;
			this->txtPassword->TextPadding = System::Windows::Forms::Padding(10, 0, 6, 0);
			this->txtPassword->UseSystemPasswordChar = true;
			this->txtPassword->ValidationErrorMessage = L"Invalid input.";
			this->txtPassword->ValidationFunction = nullptr;
			//
			// btnLogin
			//
			this->btnLogin->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnLogin->AccessibleName = L"Sign in";
			this->btnLogin->AutoSizeBasedOnText = false;
			this->btnLogin->BackColor = System::Drawing::Color::Transparent;
			this->btnLogin->BadgeBackColor = System::Drawing::Color::Black;
			this->btnLogin->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnLogin->BadgeValue = 0;
			this->btnLogin->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnLogin->BorderColor = System::Drawing::Color::Transparent;
			this->btnLogin->BorderWidth = 2;
			this->btnLogin->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnLogin->ButtonImage = nullptr;
			this->btnLogin->ButtonTextLeftPadding = 0;
			this->btnLogin->CanBeep = true;
			this->btnLogin->CanGlow = false;
			this->btnLogin->CanShake = true;
			this->btnLogin->ContextMenuStripEx = nullptr;
			this->btnLogin->CornerRadiusBottomLeft = 6;
			this->btnLogin->CornerRadiusBottomRight = 6;
			this->btnLogin->CornerRadiusTopLeft = 6;
			this->btnLogin->CornerRadiusTopRight = 6;
			this->btnLogin->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnLogin->CustomCursor = System::Windows::Forms::Cursors::Hand;
			this->btnLogin->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnLogin->EnableLongPress = false;
			this->btnLogin->EnableRippleEffect = true;
			this->btnLogin->EnableShadow = false;
			this->btnLogin->EnableTextWrapping = false;
			this->btnLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			this->btnLogin->ForeColor = System::Drawing::Color::White;
			this->btnLogin->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnLogin->GlowIntensity = 100;
			this->btnLogin->GlowRadius = 20;
			this->btnLogin->GradientBackground = false;
			this->btnLogin->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnLogin->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnLogin->HintText = nullptr;
			this->btnLogin->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(140)));
			this->btnLogin->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnLogin->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnLogin->HoverTransitionDuration = 250;
			this->btnLogin->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnLogin->ImagePadding = 5;
			this->btnLogin->ImageSize = System::Drawing::Size(16, 16);
			this->btnLogin->IsRadial = false;
			this->btnLogin->IsReadOnly = false;
			this->btnLogin->IsToggleButton = false;
			this->btnLogin->IsToggled = false;
			this->btnLogin->Location = System::Drawing::Point(10, 201);
			this->btnLogin->LongPressDurationMS = 1000;
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnLogin->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnLogin->ParticleCount = 15;
			this->btnLogin->PressAnimationScale = 0.97F;
			this->btnLogin->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnLogin->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnLogin->PressTransitionDuration = 150;
			this->btnLogin->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnLogin->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnLogin->RippleRadiusMultiplier = 0.6F;
			this->btnLogin->ShadowBlur = 5;
			this->btnLogin->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnLogin->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnLogin->ShakeDuration = 500;
			this->btnLogin->ShakeIntensity = 5;
			this->btnLogin->Size = System::Drawing::Size(140, 30);
			this->btnLogin->TabIndex = 7;
			this->btnLogin->Text = L"Sign in";
			this->btnLogin->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnLogin->TextColor = System::Drawing::Color::White;
			this->btnLogin->TooltipText = nullptr;
			this->btnLogin->UseAdvancedRendering = true;
			this->btnLogin->UseParticles = false;
			this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
			//
			// panelCard
			//
			this->panelCard->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelCard->BackColor = System::Drawing::Color::Transparent;
			this->panelCard->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			this->panelCard->BorderDashPattern = nullptr;
			this->panelCard->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->panelCard->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->panelCard->BorderThickness = 2;
			this->panelCard->Controls->Add(this->lblRegister);
			this->panelCard->Controls->Add(this->lblForgotPassword);
			this->panelCard->Controls->Add(this->lblLoginStatus);
			this->panelCard->Controls->Add(this->chkShowPassword);
			this->panelCard->Controls->Add(this->txtUsername);
			this->panelCard->Controls->Add(this->lblSignIn);
			this->panelCard->Controls->Add(this->lblPassword);
			this->panelCard->Controls->Add(this->lblUsername);
			this->panelCard->Controls->Add(this->txtPassword);
			this->panelCard->Controls->Add(this->btnLogin);
			this->panelCard->CornerRadiusBottomLeft = 10;
			this->panelCard->CornerRadiusBottomRight = 10;
			this->panelCard->CornerRadiusTopLeft = 10;
			this->panelCard->CornerRadiusTopRight = 10;
			this->panelCard->EnableAcrylicEffect = false;
			this->panelCard->EnableMicaEffect = false;
			this->panelCard->EnableRippleEffect = false;
			this->panelCard->FillColor = System::Drawing::Color::White;
			this->panelCard->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->panelCard->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->panelCard->Location = System::Drawing::Point(30, 80);
			this->panelCard->Name = L"panelCard";
			this->panelCard->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->panelCard->RippleAlpha = 50;
			this->panelCard->RippleAlphaDecrement = 3;
			this->panelCard->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelCard->RippleMaxSize = 600;
			this->panelCard->RippleSpeed = 15;
			this->panelCard->ShowBorder = true;
			this->panelCard->Size = System::Drawing::Size(340, 268);
			this->panelCard->TabIndex = 10;
			this->panelCard->TabStop = true;
			this->panelCard->TrackSystemTheme = false;
			this->panelCard->UseBorderGradient = true;
			this->panelCard->UseMultiGradient = false;
			this->panelCard->UsePatternTexture = false;
			this->panelCard->UseRadialGradient = false;
			//
			// lblRegister
			//
			this->lblRegister->AutoSize = true;
			this->lblRegister->Cursor = System::Windows::Forms::Cursors::Hand;
			this->lblRegister->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F, System::Drawing::FontStyle::Underline));
			this->lblRegister->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				static_cast<System::Int32>(static_cast<System::Byte>(189)));
			this->lblRegister->Location = System::Drawing::Point(82, 240);
			this->lblRegister->Name = L"lblRegister";
			this->lblRegister->Size = System::Drawing::Size(176, 15);
			this->lblRegister->TabIndex = 11;
			this->lblRegister->Text = L"Don\'t have an account\? Register";
			this->lblRegister->Click += gcnew System::EventHandler(this, &LoginForm::lblRegister_Click);
			//
			// lblForgotPassword
			//
			this->lblForgotPassword->AutoSize = true;
			this->lblForgotPassword->Cursor = System::Windows::Forms::Cursors::Hand;
			this->lblForgotPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F, System::Drawing::FontStyle::Underline));
			this->lblForgotPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)),
				static_cast<System::Int32>(static_cast<System::Byte>(117)), static_cast<System::Int32>(static_cast<System::Byte>(189)));
			this->lblForgotPassword->Location = System::Drawing::Point(160, 208);
			this->lblForgotPassword->Name = L"lblForgotPassword";
			this->lblForgotPassword->Size = System::Drawing::Size(100, 15);
			this->lblForgotPassword->TabIndex = 10;
			this->lblForgotPassword->Text = L"Forgot password\?";
			this->lblForgotPassword->Click += gcnew System::EventHandler(this, &LoginForm::lblForgotPassword_Click);
			//
			// lblLoginStatus
			//
			this->lblLoginStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblLoginStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->lblLoginStatus->Location = System::Drawing::Point(10, 167);
			this->lblLoginStatus->Name = L"lblLoginStatus";
			this->lblLoginStatus->Size = System::Drawing::Size(324, 31);
			this->lblLoginStatus->TabIndex = 9;
			//
			// chkShowPassword
			//
			this->chkShowPassword->AutoSize = true;
			this->chkShowPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->chkShowPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->chkShowPassword->Location = System::Drawing::Point(10, 145);
			this->chkShowPassword->Name = L"chkShowPassword";
			this->chkShowPassword->Size = System::Drawing::Size(108, 19);
			this->chkShowPassword->TabIndex = 8;
			this->chkShowPassword->Text = L"Show password";
			this->chkShowPassword->UseVisualStyleBackColor = true;
			this->chkShowPassword->CheckedChanged += gcnew System::EventHandler(this, &LoginForm::chkShowPassword_CheckedChanged);
			//
			// LoginForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->ClientSize = System::Drawing::Size(404, 361);
			this->Controls->Add(this->panelCard);
			this->Controls->Add(this->lblAppName);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sign in – IntraProcure";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &LoginForm::LoginForm_KeyDown);
			this->panelCard->ResumeLayout(false);
			this->panelCard->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		// prevent double execution (double Click / Enter / extra event)
		if (_isLoggingIn) return;

		lblLoginStatus->Text = L"";

		String^ username = txtUsername->Text->Trim();
		String^ password = txtPassword->Text;

		if (String::IsNullOrWhiteSpace(username) || String::IsNullOrWhiteSpace(password))
		{
			lblLoginStatus->Text = L"Please enter both username and password.";
			return;
		}

		String^ error = nullptr;

		Employee^ user = EmployeeManager::Authenticate(username, password, error);

		if (user == nullptr)
		{
			if (String::IsNullOrEmpty(error))
				error = L"Incorrect username or password.";

			lblLoginStatus->Text = error;
			return;
		}

		Session::InitializeFromLogin(user->Id, user->Username,
			user->FullName, user->IsManager, user->IsAdministrator,
			user->Department, user->Email, user->ProfileImage
		);

		// Now open the main shell; it will decide what page to show
		_isLoggingIn = true;
		MainForm^ main = gcnew MainForm();

		// When MainForm closes, also close this hidden LoginForm.
		main->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(
			this, &LoginForm::MainForm_FormClosed);

		main->Show();
		this->Hide();
	}

		   System::Void MainForm_FormClosed(
			   System::Object^ sender,
			   System::Windows::Forms::FormClosedEventArgs^ e)
		   {
			   // Close the hidden login form -> app fully exits
			   this->Close();
		   }

	private: System::Void chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		// When checkbox is checked → show the password
		// When unchecked → hide (mask) the password
		this->txtPassword->UseSystemPasswordChar = !this->chkShowPassword->Checked;
	}

	private: System::Void lblForgotPassword_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ Title = "Reset Your Password";
		String^ Description = "Enter your username or email. An admin will help reset your password.";
		String^ FormName = "Forget Password - IntraProcure";

		ForgotPasswordForm^ dlg = gcnew ForgotPasswordForm(Title, Description, FormName);
		dlg->ShowDialog(this);
		dlg->Close();
	}

	private: System::Void LoginForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
		{
			btnLogin_Click(sender, e);
			e->Handled = true;
		}
	}
	private: System::Void lblRegister_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ Title = "Register an account";
		String^ Description = "Enter your username or email. An admin will register you.";
		String^ FormName = "Register - IntraProcure";

		ForgotPasswordForm^ dlg = gcnew ForgotPasswordForm(Title, Description, FormName);
		dlg->ShowDialog(this);
		dlg->Close();
	}
	};
}
