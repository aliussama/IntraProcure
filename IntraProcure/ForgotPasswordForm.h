#pragma once

#include "UiStyler.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ForgotPasswordForm
	/// </summary>
	public ref class ForgotPasswordForm : public System::Windows::Forms::Form
	{
	public:
		ForgotPasswordForm(String^ title, String^ description, String^ formName)
		{
			InitializeComponent();

			UiStyler::StyleTextBox(txtUser);
			UiStyler::StylePrimaryButton(btnSubmit);
			UiStyler::StyleSecondaryButton(btnCancel);

			lblTitle->Text = title;
			lblDescription->Text = description;
			this->Text = formName;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ForgotPasswordForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblDescription;
	protected:

	private: System::Windows::Forms::Label^ lblUser;

	private: System::Windows::Forms::Label^ lblExtraInfo;
	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtUser;
	private: System::Windows::Forms::TextBox^ txtExtraInfo;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnSubmit;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnCancel;

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
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblDescription = (gcnew System::Windows::Forms::Label());
			this->lblUser = (gcnew System::Windows::Forms::Label());
			this->lblExtraInfo = (gcnew System::Windows::Forms::Label());
			this->txtUser = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->txtExtraInfo = (gcnew System::Windows::Forms::TextBox());
			this->btnSubmit = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->btnCancel = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->SuspendLayout();
			//
			// lblTitle
			//
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblTitle->Location = System::Drawing::Point(20, 20);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(166, 21);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Reset Your Password";
			//
			// lblDescription
			//
			this->lblDescription->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblDescription->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(90)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(90)));
			this->lblDescription->Location = System::Drawing::Point(20, 45);
			this->lblDescription->Name = L"lblDescription";
			this->lblDescription->Size = System::Drawing::Size(350, 40);
			this->lblDescription->TabIndex = 1;
			this->lblDescription->Text = L"Enter your username or email. An admin will help reset your password.";
			//
			// lblUser
			//
			this->lblUser->AutoSize = true;
			this->lblUser->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblUser->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblUser->Location = System::Drawing::Point(20, 90);
			this->lblUser->Name = L"lblUser";
			this->lblUser->Size = System::Drawing::Size(106, 15);
			this->lblUser->TabIndex = 2;
			this->lblUser->Text = L"Username or Email";
			//
			// lblExtraInfo
			//
			this->lblExtraInfo->AutoSize = true;
			this->lblExtraInfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblExtraInfo->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblExtraInfo->Location = System::Drawing::Point(20, 145);
			this->lblExtraInfo->Name = L"lblExtraInfo";
			this->lblExtraInfo->Size = System::Drawing::Size(141, 15);
			this->lblExtraInfo->TabIndex = 4;
			this->lblExtraInfo->Text = L"Additional info (optional)";
			//
			// txtUser
			//
			this->txtUser->AccessibleDescription = L"A customizable text input field.";
			this->txtUser->AccessibleName = L"Text Box";
			this->txtUser->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtUser->BackColor = System::Drawing::Color::Transparent;
			this->txtUser->BlinkCount = 3;
			this->txtUser->BlinkShadow = false;
			this->txtUser->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtUser->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtUser->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUser->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUser->CanShake = true;
			this->txtUser->ContinuousBlink = false;
			this->txtUser->CornerRadiusBottomLeft = 6;
			this->txtUser->CornerRadiusBottomRight = 6;
			this->txtUser->CornerRadiusTopLeft = 6;
			this->txtUser->CornerRadiusTopRight = 6;
			this->txtUser->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtUser->CursorBlinkRate = 500;
			this->txtUser->CursorColor = System::Drawing::Color::Black;
			this->txtUser->CursorHeight = 26;
			this->txtUser->CursorOffset = 0;
			this->txtUser->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtUser->CursorWidth = 1;
			this->txtUser->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtUser->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtUser->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtUser->EnableDropShadow = false;
			this->txtUser->FillColor1 = System::Drawing::Color::White;
			this->txtUser->FillColor2 = System::Drawing::Color::White;
			this->txtUser->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtUser->ForeColor = System::Drawing::Color::DimGray;
			this->txtUser->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtUser->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtUser->IsEnabled = true;
			this->txtUser->Location = System::Drawing::Point(20, 110);
			this->txtUser->Name = L"txtUser";
			this->txtUser->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtUser->PlaceholderText = L"Enter your username or email";
			this->txtUser->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtUser->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtUser->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtUser->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtUser->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtUser->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUser->ShadowAnimationDuration = 1;
			this->txtUser->ShadowBlur = 10;
			this->txtUser->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtUser->Size = System::Drawing::Size(340, 26);
			this->txtUser->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtUser->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtUser->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtUser->SolidFillColor = System::Drawing::Color::White;
			this->txtUser->TabIndex = 5;
			this->txtUser->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtUser->ValidationErrorMessage = L"Invalid input.";
			this->txtUser->ValidationFunction = nullptr;
			//
			// txtExtraInfo
			//
			this->txtExtraInfo->BackColor = System::Drawing::Color::White;
			this->txtExtraInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtExtraInfo->Location = System::Drawing::Point(20, 165);
			this->txtExtraInfo->Multiline = true;
			this->txtExtraInfo->Name = L"txtExtraInfo";
			this->txtExtraInfo->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtExtraInfo->Size = System::Drawing::Size(340, 40);
			this->txtExtraInfo->TabIndex = 8;
			//
			// btnSubmit
			//
			this->btnSubmit->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnSubmit->AccessibleName = L"Send Request";
			this->btnSubmit->AutoSizeBasedOnText = false;
			this->btnSubmit->BackColor = System::Drawing::Color::Transparent;
			this->btnSubmit->BadgeBackColor = System::Drawing::Color::Black;
			this->btnSubmit->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnSubmit->BadgeValue = 0;
			this->btnSubmit->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnSubmit->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnSubmit->BorderWidth = 1;
			this->btnSubmit->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnSubmit->ButtonImage = nullptr;
			this->btnSubmit->ButtonTextLeftPadding = 0;
			this->btnSubmit->CanBeep = true;
			this->btnSubmit->CanGlow = false;
			this->btnSubmit->CanShake = true;
			this->btnSubmit->ContextMenuStripEx = nullptr;
			this->btnSubmit->CornerRadiusBottomLeft = 6;
			this->btnSubmit->CornerRadiusBottomRight = 6;
			this->btnSubmit->CornerRadiusTopLeft = 6;
			this->btnSubmit->CornerRadiusTopRight = 6;
			this->btnSubmit->CustomCursor = System::Windows::Forms::Cursors::Default;
			this->btnSubmit->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnSubmit->EnableLongPress = false;
			this->btnSubmit->EnableRippleEffect = true;
			this->btnSubmit->EnableShadow = false;
			this->btnSubmit->EnableTextWrapping = false;
			this->btnSubmit->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			this->btnSubmit->ForeColor = System::Drawing::Color::White;
			this->btnSubmit->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnSubmit->GlowIntensity = 100;
			this->btnSubmit->GlowRadius = 20;
			this->btnSubmit->GradientBackground = false;
			this->btnSubmit->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnSubmit->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnSubmit->HintText = nullptr;
			this->btnSubmit->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnSubmit->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSubmit->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSubmit->HoverTransitionDuration = 250;
			this->btnSubmit->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnSubmit->ImagePadding = 5;
			this->btnSubmit->ImageSize = System::Drawing::Size(16, 16);
			this->btnSubmit->IsRadial = false;
			this->btnSubmit->IsReadOnly = false;
			this->btnSubmit->IsToggleButton = false;
			this->btnSubmit->IsToggled = false;
			this->btnSubmit->Location = System::Drawing::Point(20, 215);
			this->btnSubmit->LongPressDurationMS = 1000;
			this->btnSubmit->Name = L"btnSubmit";
			this->btnSubmit->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSubmit->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnSubmit->ParticleCount = 15;
			this->btnSubmit->PressAnimationScale = 0.97F;
			this->btnSubmit->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnSubmit->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnSubmit->PressTransitionDuration = 150;
			this->btnSubmit->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnSubmit->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSubmit->RippleRadiusMultiplier = 0.6F;
			this->btnSubmit->ShadowBlur = 5;
			this->btnSubmit->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnSubmit->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnSubmit->ShakeDuration = 500;
			this->btnSubmit->ShakeIntensity = 5;
			this->btnSubmit->Size = System::Drawing::Size(120, 30);
			this->btnSubmit->TabIndex = 10;
			this->btnSubmit->Text = L"Send Request";
			this->btnSubmit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnSubmit->TextColor = System::Drawing::Color::White;
			this->btnSubmit->TooltipText = nullptr;
			this->btnSubmit->UseAdvancedRendering = true;
			this->btnSubmit->UseParticles = false;
			this->btnSubmit->Click += gcnew System::EventHandler(this, &ForgotPasswordForm::btnSubmit_Click);
			//
			// btnCancel
			//
			this->btnCancel->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnCancel->AccessibleName = L"Cancel";
			this->btnCancel->AutoSizeBasedOnText = false;
			this->btnCancel->BackColor = System::Drawing::Color::Transparent;
			this->btnCancel->BadgeBackColor = System::Drawing::Color::Black;
			this->btnCancel->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnCancel->BadgeValue = 0;
			this->btnCancel->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnCancel->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnCancel->BorderWidth = 1;
			this->btnCancel->ButtonBackColor = System::Drawing::Color::Transparent;
			this->btnCancel->ButtonImage = nullptr;
			this->btnCancel->ButtonTextLeftPadding = 0;
			this->btnCancel->CanBeep = true;
			this->btnCancel->CanGlow = false;
			this->btnCancel->CanShake = true;
			this->btnCancel->ContextMenuStripEx = nullptr;
			this->btnCancel->CornerRadiusBottomLeft = 6;
			this->btnCancel->CornerRadiusBottomRight = 6;
			this->btnCancel->CornerRadiusTopLeft = 6;
			this->btnCancel->CornerRadiusTopRight = 6;
			this->btnCancel->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnCancel->CustomCursor = System::Windows::Forms::Cursors::Hand;
			this->btnCancel->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnCancel->EnableLongPress = false;
			this->btnCancel->EnableRippleEffect = true;
			this->btnCancel->EnableShadow = false;
			this->btnCancel->EnableTextWrapping = false;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->ForeColor = System::Drawing::Color::White;
			this->btnCancel->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnCancel->GlowIntensity = 100;
			this->btnCancel->GlowRadius = 20;
			this->btnCancel->GradientBackground = false;
			this->btnCancel->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnCancel->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnCancel->HintText = nullptr;
			this->btnCancel->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnCancel->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancel->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancel->HoverTransitionDuration = 250;
			this->btnCancel->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnCancel->ImagePadding = 5;
			this->btnCancel->ImageSize = System::Drawing::Size(16, 16);
			this->btnCancel->IsRadial = false;
			this->btnCancel->IsReadOnly = false;
			this->btnCancel->IsToggleButton = false;
			this->btnCancel->IsToggled = false;
			this->btnCancel->Location = System::Drawing::Point(160, 215);
			this->btnCancel->LongPressDurationMS = 1000;
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancel->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnCancel->ParticleCount = 15;
			this->btnCancel->PressAnimationScale = 0.97F;
			this->btnCancel->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnCancel->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancel->PressTransitionDuration = 150;
			this->btnCancel->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnCancel->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancel->RippleRadiusMultiplier = 0.6F;
			this->btnCancel->ShadowBlur = 5;
			this->btnCancel->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancel->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnCancel->ShakeDuration = 500;
			this->btnCancel->ShakeIntensity = 5;
			this->btnCancel->Size = System::Drawing::Size(90, 30);
			this->btnCancel->TabIndex = 11;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCancel->TextColor = System::Drawing::Color::Black;
			this->btnCancel->TooltipText = nullptr;
			this->btnCancel->UseAdvancedRendering = true;
			this->btnCancel->UseParticles = false;
			this->btnCancel->Click += gcnew System::EventHandler(this, &ForgotPasswordForm::btnCancel_Click);
			//
			// ForgotPasswordForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->ClientSize = System::Drawing::Size(384, 251);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnSubmit);
			this->Controls->Add(this->txtExtraInfo);
			this->Controls->Add(this->txtUser);
			this->Controls->Add(this->lblExtraInfo);
			this->Controls->Add(this->lblUser);
			this->Controls->Add(this->lblDescription);
			this->Controls->Add(this->lblTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"ForgotPasswordForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Forgot Password – IntraProcure";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void btnSubmit_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (String::IsNullOrWhiteSpace(txtUser->Text))
		{
			MessageBox::Show(L"Please enter your username or email.",
				L"Reset Password", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// TODO: store reset request in DB / send email, etc.

		MessageBox::Show(
			L"Your request has been sent to the administrator.\n"
			L"You will be contacted with reset instructions.",
			L"Reset Password", MessageBoxButtons::OK, MessageBoxIcon::Information);

		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}

	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
	}
	};
}
