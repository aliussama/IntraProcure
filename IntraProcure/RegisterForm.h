#pragma once

#include "UiStyler.h"
#include "EmployeeManager.h"
#include "Employee.h"
#include "Config.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RegisterForm
	/// </summary>
	public ref class RegisterForm : public System::Windows::Forms::Form
	{
	public:
		RegisterForm(void)
		{
			InitializeComponent();

			UiStyler::StyleTextBox(txtFullName);
			UiStyler::StyleTextBox(txtEmail);
			UiStyler::StyleTextBox(txtUsername);
			UiStyler::StyleTextBox(txtPassword);
			UiStyler::StyleTextBox(txtConfirmPassword);

			UiStyler::StylePrimaryButton(btnRegister);
			UiStyler::StyleSecondaryButton(btnCancel);

			this->KeyPreview = true;

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

			if (cmbDepartment->Items->Count > 0)
				cmbDepartment->SelectedIndex = 0;

			// Default role is "Employee"
			if (chkIsEmployee != nullptr) chkIsEmployee->Checked = true;
			if (chkIsManager != nullptr)  chkIsManager->Checked = false;
			if (chkIsAdmin != nullptr)    chkIsAdmin->Checked = false;

			if (lblStatus != nullptr)
			{
				lblStatus->Text = L"";
				lblStatus->ForeColor = Color::FromArgb(120, 120, 120);
			}

			// Mask passwords by default
			if (txtPassword != nullptr)         txtPassword->UseSystemPasswordChar = true;
			if (txtConfirmPassword != nullptr)  txtConfirmPassword->UseSystemPasswordChar = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RegisterForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panelContent;
	protected:
	private: System::Windows::Forms::Label^ lblFullName;
	private: SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
	private: System::Windows::Forms::Label^ lblTitle;
	private: SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelFooter;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtFullName;
	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtEmail;
	private: System::Windows::Forms::Label^ lblEmail;
	private: System::Windows::Forms::ComboBox^ cmbDepartment;
	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtPassword;
	private: System::Windows::Forms::Label^ lblPassword;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtUsername;
	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::Label^ lblDepartment;
	private: System::Windows::Forms::Label^ lblRole;

	private: SiticoneNetFrameworkUI::SiticoneTextBox^ txtConfirmPassword;
	private: System::Windows::Forms::Label^ lblPasswordConfirm;
	private: System::Windows::Forms::CheckBox^ chkShowPassword;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnCancel;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnRegister;

	private: SiticoneNetFrameworkUI::SiticoneRadioButton^ chkIsManager;
	private: SiticoneNetFrameworkUI::SiticoneRadioButton^ chkIsEmployee;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;
	private: SiticoneNetFrameworkUI::SiticoneRadioButton^ chkIsAdmin;
	private: System::Windows::Forms::Label^ lblStatus;

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
			this->panelContent = (gcnew System::Windows::Forms::Panel());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->chkIsAdmin = (gcnew SiticoneNetFrameworkUI::SiticoneRadioButton());
			this->chkIsManager = (gcnew SiticoneNetFrameworkUI::SiticoneRadioButton());
			this->chkIsEmployee = (gcnew SiticoneNetFrameworkUI::SiticoneRadioButton());
			this->chkShowPassword = (gcnew System::Windows::Forms::CheckBox());
			this->lblRole = (gcnew System::Windows::Forms::Label());
			this->txtConfirmPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblPasswordConfirm = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->lblDepartment = (gcnew System::Windows::Forms::Label());
			this->cmbDepartment = (gcnew System::Windows::Forms::ComboBox());
			this->txtEmail = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblEmail = (gcnew System::Windows::Forms::Label());
			this->txtFullName = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->lblFullName = (gcnew System::Windows::Forms::Label());
			this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->panelFooter = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			this->btnCancel = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->btnRegister = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->panelContent->SuspendLayout();
			this->panelHeader->SuspendLayout();
			this->panelFooter->SuspendLayout();
			this->siticonePanel1->SuspendLayout();
			this->SuspendLayout();
			//
			// panelContent
			//
			this->panelContent->BackColor = System::Drawing::Color::White;
			this->panelContent->Controls->Add(this->lblStatus);
			this->panelContent->Controls->Add(this->chkIsAdmin);
			this->panelContent->Controls->Add(this->chkIsManager);
			this->panelContent->Controls->Add(this->chkIsEmployee);
			this->panelContent->Controls->Add(this->chkShowPassword);
			this->panelContent->Controls->Add(this->lblRole);
			this->panelContent->Controls->Add(this->txtConfirmPassword);
			this->panelContent->Controls->Add(this->lblPasswordConfirm);
			this->panelContent->Controls->Add(this->txtPassword);
			this->panelContent->Controls->Add(this->lblPassword);
			this->panelContent->Controls->Add(this->txtUsername);
			this->panelContent->Controls->Add(this->lblUsername);
			this->panelContent->Controls->Add(this->lblDepartment);
			this->panelContent->Controls->Add(this->cmbDepartment);
			this->panelContent->Controls->Add(this->txtEmail);
			this->panelContent->Controls->Add(this->lblEmail);
			this->panelContent->Controls->Add(this->txtFullName);
			this->panelContent->Controls->Add(this->lblFullName);
			this->panelContent->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelContent->Location = System::Drawing::Point(2, 2);
			this->panelContent->Name = L"panelContent";
			this->panelContent->Padding = System::Windows::Forms::Padding(50, 20, 50, 20);
			this->panelContent->Size = System::Drawing::Size(911, 399);
			this->panelContent->TabIndex = 2;
			//
			// lblStatus
			//
			this->lblStatus->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblStatus->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->lblStatus->Location = System::Drawing::Point(107, 376);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(0, 15);
			this->lblStatus->TabIndex = 10;
			//
			// chkIsAdmin
			//
			this->chkIsAdmin->AccessibleName = L"Manager";
			this->chkIsAdmin->AccessibleRole = System::Windows::Forms::AccessibleRole::RadioButton;
			this->chkIsAdmin->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->chkIsAdmin->BackColor = System::Drawing::Color::Transparent;
			this->chkIsAdmin->CanBeep = true;
			this->chkIsAdmin->CanShake = true;
			this->chkIsAdmin->Checked = false;
			this->chkIsAdmin->CheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->chkIsAdmin->ContainerBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsAdmin->ContainerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsAdmin->ContainerBorderWidth = 1;
			this->chkIsAdmin->ContainerBottomLeftRadius = 8;
			this->chkIsAdmin->ContainerBottomRightRadius = 8;
			this->chkIsAdmin->ContainerCheckedBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsAdmin->ContainerCheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsAdmin->ContainerCheckedHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsAdmin->ContainerCheckedPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsAdmin->ContainerHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsAdmin->ContainerPadding = 8;
			this->chkIsAdmin->ContainerPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsAdmin->ContainerTopLeftRadius = 8;
			this->chkIsAdmin->ContainerTopRightRadius = 8;
			this->chkIsAdmin->EnableRipple = false;
			this->chkIsAdmin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->chkIsAdmin->HoverCursor = System::Windows::Forms::Cursors::Hand;
			this->chkIsAdmin->IsContained = false;
			this->chkIsAdmin->IsReadOnly = false;
			this->chkIsAdmin->Location = System::Drawing::Point(570, 89);
			this->chkIsAdmin->MinimumSize = System::Drawing::Size(178, 24);
			this->chkIsAdmin->Name = L"chkIsAdmin";
			this->chkIsAdmin->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->chkIsAdmin->RippleDuration = 0.5F;
			this->chkIsAdmin->RippleStyle = SiticoneNetFrameworkUI::SiticoneRadioButton::RippleAnimationStyle::Standard;
			this->chkIsAdmin->ShakeDuration = 0.5F;
			this->chkIsAdmin->Size = System::Drawing::Size(178, 24);
			this->chkIsAdmin->TabIndex = 10;
			this->chkIsAdmin->Text = L"Administrator";
			this->chkIsAdmin->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->chkIsAdmin->ToolTipText = L"";
			this->chkIsAdmin->UncheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(160)));
			//
			// chkIsManager
			//
			this->chkIsManager->AccessibleName = L"Manager";
			this->chkIsManager->AccessibleRole = System::Windows::Forms::AccessibleRole::RadioButton;
			this->chkIsManager->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->chkIsManager->BackColor = System::Drawing::Color::Transparent;
			this->chkIsManager->CanBeep = true;
			this->chkIsManager->CanShake = true;
			this->chkIsManager->Checked = false;
			this->chkIsManager->CheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->chkIsManager->ContainerBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsManager->ContainerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsManager->ContainerBorderWidth = 1;
			this->chkIsManager->ContainerBottomLeftRadius = 8;
			this->chkIsManager->ContainerBottomRightRadius = 8;
			this->chkIsManager->ContainerCheckedBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsManager->ContainerCheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsManager->ContainerCheckedHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsManager->ContainerCheckedPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsManager->ContainerHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsManager->ContainerPadding = 8;
			this->chkIsManager->ContainerPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsManager->ContainerTopLeftRadius = 8;
			this->chkIsManager->ContainerTopRightRadius = 8;
			this->chkIsManager->EnableRipple = false;
			this->chkIsManager->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->chkIsManager->HoverCursor = System::Windows::Forms::Cursors::Hand;
			this->chkIsManager->IsContained = false;
			this->chkIsManager->IsReadOnly = false;
			this->chkIsManager->Location = System::Drawing::Point(570, 60);
			this->chkIsManager->MinimumSize = System::Drawing::Size(178, 24);
			this->chkIsManager->Name = L"chkIsManager";
			this->chkIsManager->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->chkIsManager->RippleDuration = 0.5F;
			this->chkIsManager->RippleStyle = SiticoneNetFrameworkUI::SiticoneRadioButton::RippleAnimationStyle::Standard;
			this->chkIsManager->ShakeDuration = 0.5F;
			this->chkIsManager->Size = System::Drawing::Size(178, 24);
			this->chkIsManager->TabIndex = 9;
			this->chkIsManager->Text = L"Manager";
			this->chkIsManager->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->chkIsManager->ToolTipText = L"";
			this->chkIsManager->UncheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(160)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			//
			// chkIsEmployee
			//
			this->chkIsEmployee->AccessibleName = L"Employee";
			this->chkIsEmployee->AccessibleRole = System::Windows::Forms::AccessibleRole::RadioButton;
			this->chkIsEmployee->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->chkIsEmployee->BackColor = System::Drawing::Color::Transparent;
			this->chkIsEmployee->CanBeep = true;
			this->chkIsEmployee->CanShake = true;
			this->chkIsEmployee->Checked = false;
			this->chkIsEmployee->CheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->chkIsEmployee->ContainerBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsEmployee->ContainerBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsEmployee->ContainerBorderWidth = 1;
			this->chkIsEmployee->ContainerBottomLeftRadius = 8;
			this->chkIsEmployee->ContainerBottomRightRadius = 8;
			this->chkIsEmployee->ContainerCheckedBorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsEmployee->ContainerCheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsEmployee->ContainerCheckedHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsEmployee->ContainerCheckedPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(56)), static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->chkIsEmployee->ContainerHoverColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsEmployee->ContainerPadding = 8;
			this->chkIsEmployee->ContainerPressedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->chkIsEmployee->ContainerTopLeftRadius = 8;
			this->chkIsEmployee->ContainerTopRightRadius = 8;
			this->chkIsEmployee->EnableRipple = false;
			this->chkIsEmployee->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->chkIsEmployee->HoverCursor = System::Windows::Forms::Cursors::Hand;
			this->chkIsEmployee->IsContained = false;
			this->chkIsEmployee->IsReadOnly = false;
			this->chkIsEmployee->Location = System::Drawing::Point(570, 31);
			this->chkIsEmployee->MinimumSize = System::Drawing::Size(178, 24);
			this->chkIsEmployee->Name = L"chkIsEmployee";
			this->chkIsEmployee->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(215)));
			this->chkIsEmployee->RippleDuration = 0.5F;
			this->chkIsEmployee->RippleStyle = SiticoneNetFrameworkUI::SiticoneRadioButton::RippleAnimationStyle::Standard;
			this->chkIsEmployee->ShakeDuration = 0.5F;
			this->chkIsEmployee->Size = System::Drawing::Size(178, 24);
			this->chkIsEmployee->TabIndex = 8;
			this->chkIsEmployee->Text = L"Employee";
			this->chkIsEmployee->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->chkIsEmployee->ToolTipText = L"";
			this->chkIsEmployee->UncheckedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(160)), static_cast<System::Int32>(static_cast<System::Byte>(160)));
			//
			// chkShowPassword
			//
			this->chkShowPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->chkShowPassword->AutoSize = true;
			this->chkShowPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->chkShowPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->chkShowPassword->Location = System::Drawing::Point(107, 352);
			this->chkShowPassword->Name = L"chkShowPassword";
			this->chkShowPassword->Size = System::Drawing::Size(108, 19);
			this->chkShowPassword->TabIndex = 7;
			this->chkShowPassword->Text = L"Show password";
			this->chkShowPassword->UseVisualStyleBackColor = true;
			this->chkShowPassword->CheckedChanged += gcnew System::EventHandler(this, &RegisterForm::chkShowPassword_CheckedChanged);
			//
			// lblRole
			//
			this->lblRole->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblRole->AutoSize = true;
			this->lblRole->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblRole->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblRole->Location = System::Drawing::Point(570, 10);
			this->lblRole->Name = L"lblRole";
			this->lblRole->Size = System::Drawing::Size(70, 15);
			this->lblRole->TabIndex = 14;
			this->lblRole->Text = L"Register As";
			//
			// txtConfirmPassword
			//
			this->txtConfirmPassword->AccessibleDescription = L"A customizable text input field.";
			this->txtConfirmPassword->AccessibleName = L"Text Box";
			this->txtConfirmPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtConfirmPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->txtConfirmPassword->BackColor = System::Drawing::Color::Transparent;
			this->txtConfirmPassword->BlinkCount = 3;
			this->txtConfirmPassword->BlinkShadow = false;
			this->txtConfirmPassword->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtConfirmPassword->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtConfirmPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtConfirmPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtConfirmPassword->CanShake = true;
			this->txtConfirmPassword->ContinuousBlink = false;
			this->txtConfirmPassword->CornerRadiusBottomLeft = 6;
			this->txtConfirmPassword->CornerRadiusBottomRight = 6;
			this->txtConfirmPassword->CornerRadiusTopLeft = 6;
			this->txtConfirmPassword->CornerRadiusTopRight = 6;
			this->txtConfirmPassword->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtConfirmPassword->CursorBlinkRate = 500;
			this->txtConfirmPassword->CursorColor = System::Drawing::Color::Black;
			this->txtConfirmPassword->CursorHeight = 26;
			this->txtConfirmPassword->CursorOffset = 0;
			this->txtConfirmPassword->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtConfirmPassword->CursorWidth = 1;
			this->txtConfirmPassword->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtConfirmPassword->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtConfirmPassword->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtConfirmPassword->EnableDropShadow = false;
			this->txtConfirmPassword->FillColor1 = System::Drawing::Color::White;
			this->txtConfirmPassword->FillColor2 = System::Drawing::Color::White;
			this->txtConfirmPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtConfirmPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->txtConfirmPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtConfirmPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtConfirmPassword->IsEnabled = true;
			this->txtConfirmPassword->Location = System::Drawing::Point(107, 311);
			this->txtConfirmPassword->Name = L"txtConfirmPassword";
			this->txtConfirmPassword->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtConfirmPassword->PlaceholderText = L"Confirm password";
			this->txtConfirmPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtConfirmPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtConfirmPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtConfirmPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtConfirmPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtConfirmPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtConfirmPassword->ShadowAnimationDuration = 1;
			this->txtConfirmPassword->ShadowBlur = 10;
			this->txtConfirmPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtConfirmPassword->Size = System::Drawing::Size(300, 30);
			this->txtConfirmPassword->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtConfirmPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtConfirmPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtConfirmPassword->SolidFillColor = System::Drawing::Color::White;
			this->txtConfirmPassword->TabIndex = 6;
			this->txtConfirmPassword->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtConfirmPassword->UseSystemPasswordChar = true;
			this->txtConfirmPassword->ValidationErrorMessage = L"Invalid input.";
			this->txtConfirmPassword->ValidationFunction = nullptr;
			//
			// lblPasswordConfirm
			//
			this->lblPasswordConfirm->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblPasswordConfirm->AutoSize = true;
			this->lblPasswordConfirm->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPasswordConfirm->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblPasswordConfirm->Location = System::Drawing::Point(107, 290);
			this->lblPasswordConfirm->Name = L"lblPasswordConfirm";
			this->lblPasswordConfirm->Size = System::Drawing::Size(107, 15);
			this->lblPasswordConfirm->TabIndex = 11;
			this->lblPasswordConfirm->Text = L"Confirm Password";
			//
			// txtPassword
			//
			this->txtPassword->AccessibleDescription = L"A customizable text input field.";
			this->txtPassword->AccessibleName = L"Text Box";
			this->txtPassword->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->txtPassword->BackColor = System::Drawing::Color::Transparent;
			this->txtPassword->BlinkCount = 3;
			this->txtPassword->BlinkShadow = false;
			this->txtPassword->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtPassword->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtPassword->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtPassword->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
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
			this->txtPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->txtPassword->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtPassword->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtPassword->IsEnabled = true;
			this->txtPassword->Location = System::Drawing::Point(107, 255);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtPassword->PlaceholderText = L"Create password";
			this->txtPassword->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtPassword->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtPassword->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtPassword->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtPassword->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtPassword->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtPassword->ShadowAnimationDuration = 1;
			this->txtPassword->ShadowBlur = 10;
			this->txtPassword->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtPassword->Size = System::Drawing::Size(300, 30);
			this->txtPassword->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtPassword->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtPassword->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtPassword->SolidFillColor = System::Drawing::Color::White;
			this->txtPassword->TabIndex = 5;
			this->txtPassword->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtPassword->UseSystemPasswordChar = true;
			this->txtPassword->ValidationErrorMessage = L"Invalid input.";
			this->txtPassword->ValidationFunction = nullptr;
			//
			// lblPassword
			//
			this->lblPassword->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblPassword->AutoSize = true;
			this->lblPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPassword->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblPassword->Location = System::Drawing::Point(107, 234);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(59, 15);
			this->lblPassword->TabIndex = 9;
			this->lblPassword->Text = L"Password";
			//
			// txtUsername
			//
			this->txtUsername->AccessibleDescription = L"A customizable text input field.";
			this->txtUsername->AccessibleName = L"Text Box";
			this->txtUsername->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtUsername->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->txtUsername->BackColor = System::Drawing::Color::Transparent;
			this->txtUsername->BlinkCount = 3;
			this->txtUsername->BlinkShadow = false;
			this->txtUsername->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtUsername->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtUsername->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtUsername->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
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
			this->txtUsername->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->txtUsername->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtUsername->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtUsername->IsEnabled = true;
			this->txtUsername->Location = System::Drawing::Point(104, 31);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtUsername->PlaceholderText = L"Choose a username";
			this->txtUsername->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtUsername->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtUsername->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtUsername->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtUsername->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtUsername->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtUsername->ShadowAnimationDuration = 1;
			this->txtUsername->ShadowBlur = 10;
			this->txtUsername->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtUsername->Size = System::Drawing::Size(300, 30);
			this->txtUsername->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtUsername->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtUsername->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtUsername->SolidFillColor = System::Drawing::Color::White;
			this->txtUsername->TabIndex = 1;
			this->txtUsername->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtUsername->ValidationErrorMessage = L"Invalid input.";
			this->txtUsername->ValidationFunction = nullptr;
			//
			// lblUsername
			//
			this->lblUsername->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblUsername->AutoSize = true;
			this->lblUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUsername->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblUsername->Location = System::Drawing::Point(104, 10);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(64, 15);
			this->lblUsername->TabIndex = 7;
			this->lblUsername->Text = L"Username";
			//
			// lblDepartment
			//
			this->lblDepartment->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblDepartment->AutoSize = true;
			this->lblDepartment->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblDepartment->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblDepartment->Location = System::Drawing::Point(104, 122);
			this->lblDepartment->Name = L"lblDepartment";
			this->lblDepartment->Size = System::Drawing::Size(76, 15);
			this->lblDepartment->TabIndex = 6;
			this->lblDepartment->Text = L"Department";
			//
			// cmbDepartment
			//
			this->cmbDepartment->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->cmbDepartment->BackColor = System::Drawing::Color::White;
			this->cmbDepartment->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbDepartment->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbDepartment->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->cmbDepartment->FormattingEnabled = true;
			this->cmbDepartment->Location = System::Drawing::Point(104, 144);
			this->cmbDepartment->Name = L"cmbDepartment";
			this->cmbDepartment->Size = System::Drawing::Size(300, 23);
			this->cmbDepartment->TabIndex = 3;
			//
			// txtEmail
			//
			this->txtEmail->AccessibleDescription = L"A customizable text input field.";
			this->txtEmail->AccessibleName = L"Text Box";
			this->txtEmail->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtEmail->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->txtEmail->BackColor = System::Drawing::Color::Transparent;
			this->txtEmail->BlinkCount = 3;
			this->txtEmail->BlinkShadow = false;
			this->txtEmail->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtEmail->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtEmail->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtEmail->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtEmail->CanShake = true;
			this->txtEmail->ContinuousBlink = false;
			this->txtEmail->CornerRadiusBottomLeft = 6;
			this->txtEmail->CornerRadiusBottomRight = 6;
			this->txtEmail->CornerRadiusTopLeft = 6;
			this->txtEmail->CornerRadiusTopRight = 6;
			this->txtEmail->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtEmail->CursorBlinkRate = 500;
			this->txtEmail->CursorColor = System::Drawing::Color::Black;
			this->txtEmail->CursorHeight = 26;
			this->txtEmail->CursorOffset = 0;
			this->txtEmail->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtEmail->CursorWidth = 1;
			this->txtEmail->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtEmail->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtEmail->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtEmail->EnableDropShadow = false;
			this->txtEmail->FillColor1 = System::Drawing::Color::White;
			this->txtEmail->FillColor2 = System::Drawing::Color::White;
			this->txtEmail->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtEmail->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->txtEmail->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtEmail->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtEmail->IsEnabled = true;
			this->txtEmail->Location = System::Drawing::Point(107, 199);
			this->txtEmail->Name = L"txtEmail";
			this->txtEmail->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtEmail->PlaceholderText = L"Enter email address";
			this->txtEmail->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtEmail->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtEmail->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtEmail->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtEmail->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtEmail->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtEmail->ShadowAnimationDuration = 1;
			this->txtEmail->ShadowBlur = 10;
			this->txtEmail->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtEmail->Size = System::Drawing::Size(300, 30);
			this->txtEmail->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtEmail->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtEmail->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtEmail->SolidFillColor = System::Drawing::Color::White;
			this->txtEmail->TabIndex = 4;
			this->txtEmail->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtEmail->ValidationErrorMessage = L"Invalid input.";
			this->txtEmail->ValidationFunction = nullptr;
			//
			// lblEmail
			//
			this->lblEmail->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblEmail->AutoSize = true;
			this->lblEmail->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblEmail->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblEmail->Location = System::Drawing::Point(107, 178);
			this->lblEmail->Name = L"lblEmail";
			this->lblEmail->Size = System::Drawing::Size(83, 15);
			this->lblEmail->TabIndex = 3;
			this->lblEmail->Text = L"Email Address";
			//
			// txtFullName
			//
			this->txtFullName->AccessibleDescription = L"A customizable text input field.";
			this->txtFullName->AccessibleName = L"Text Box";
			this->txtFullName->AccessibleRole = System::Windows::Forms::AccessibleRole::Text;
			this->txtFullName->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->txtFullName->BackColor = System::Drawing::Color::Transparent;
			this->txtFullName->BlinkCount = 3;
			this->txtFullName->BlinkShadow = false;
			this->txtFullName->BorderColor1 = System::Drawing::Color::LightSlateGray;
			this->txtFullName->BorderColor2 = System::Drawing::Color::LightSlateGray;
			this->txtFullName->BorderFocusColor1 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtFullName->BorderFocusColor2 = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtFullName->CanShake = true;
			this->txtFullName->ContinuousBlink = false;
			this->txtFullName->CornerRadiusBottomLeft = 6;
			this->txtFullName->CornerRadiusBottomRight = 6;
			this->txtFullName->CornerRadiusTopLeft = 6;
			this->txtFullName->CornerRadiusTopRight = 6;
			this->txtFullName->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->txtFullName->CursorBlinkRate = 500;
			this->txtFullName->CursorColor = System::Drawing::Color::Black;
			this->txtFullName->CursorHeight = 26;
			this->txtFullName->CursorOffset = 0;
			this->txtFullName->CursorStyle = SiticoneNetFrameworkUI::Helpers::DrawingStyle::SiticoneDrawingStyle::Solid;
			this->txtFullName->CursorWidth = 1;
			this->txtFullName->DisabledBackColor = System::Drawing::Color::WhiteSmoke;
			this->txtFullName->DisabledBorderColor = System::Drawing::Color::LightGray;
			this->txtFullName->DisabledTextColor = System::Drawing::Color::Gray;
			this->txtFullName->EnableDropShadow = false;
			this->txtFullName->FillColor1 = System::Drawing::Color::White;
			this->txtFullName->FillColor2 = System::Drawing::Color::White;
			this->txtFullName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->txtFullName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->txtFullName->HoverBorderColor1 = System::Drawing::Color::Gray;
			this->txtFullName->HoverBorderColor2 = System::Drawing::Color::Gray;
			this->txtFullName->IsEnabled = true;
			this->txtFullName->Location = System::Drawing::Point(104, 87);
			this->txtFullName->Name = L"txtFullName";
			this->txtFullName->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtFullName->PlaceholderText = L"Enter full name";
			this->txtFullName->ReadOnlyBorderColor1 = System::Drawing::Color::LightGray;
			this->txtFullName->ReadOnlyBorderColor2 = System::Drawing::Color::LightGray;
			this->txtFullName->ReadOnlyFillColor1 = System::Drawing::Color::WhiteSmoke;
			this->txtFullName->ReadOnlyFillColor2 = System::Drawing::Color::WhiteSmoke;
			this->txtFullName->ReadOnlyPlaceholderColor = System::Drawing::Color::DarkGray;
			this->txtFullName->SelectionBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtFullName->ShadowAnimationDuration = 1;
			this->txtFullName->ShadowBlur = 10;
			this->txtFullName->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->txtFullName->Size = System::Drawing::Size(300, 30);
			this->txtFullName->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtFullName->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(77)),
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtFullName->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtFullName->SolidFillColor = System::Drawing::Color::White;
			this->txtFullName->TabIndex = 2;
			this->txtFullName->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtFullName->ValidationErrorMessage = L"Invalid input.";
			this->txtFullName->ValidationFunction = nullptr;
			//
			// lblFullName
			//
			this->lblFullName->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->lblFullName->AutoSize = true;
			this->lblFullName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblFullName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblFullName->Location = System::Drawing::Point(104, 66);
			this->lblFullName->Name = L"lblFullName";
			this->lblFullName->Size = System::Drawing::Size(62, 15);
			this->lblFullName->TabIndex = 1;
			this->lblFullName->Text = L"Full Name";
			//
			// panelHeader
			//
			this->panelHeader->BackColor = System::Drawing::Color::White;
			this->panelHeader->Controls->Add(this->lblTitle);
			this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelHeader->Location = System::Drawing::Point(0, 0);
			this->panelHeader->MinimumSize = System::Drawing::Size(20, 20);
			this->panelHeader->Name = L"panelHeader";
			this->panelHeader->Padding = System::Windows::Forms::Padding(15, 10, 15, 10);
			this->panelHeader->Size = System::Drawing::Size(916, 70);
			this->panelHeader->TabIndex = 0;
			//
			// lblTitle
			//
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblTitle->Location = System::Drawing::Point(20, 20);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(208, 25);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Create a New Account";
			//
			// panelFooter
			//
			this->panelFooter->BackColor = System::Drawing::Color::White;
			this->panelFooter->Controls->Add(this->btnCancel);
			this->panelFooter->Controls->Add(this->btnRegister);
			this->panelFooter->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panelFooter->ForeColor = System::Drawing::Color::Black;
			this->panelFooter->Location = System::Drawing::Point(2, 401);
			this->panelFooter->MinimumSize = System::Drawing::Size(20, 20);
			this->panelFooter->Name = L"panelFooter";
			this->panelFooter->Padding = System::Windows::Forms::Padding(15);
			this->panelFooter->Size = System::Drawing::Size(911, 70);
			this->panelFooter->TabIndex = 1;
			//
			// btnCancel
			//
			this->btnCancel->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnCancel->AccessibleName = L"Clear";
			this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
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
			this->btnCancel->Location = System::Drawing::Point(648, 15);
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
			this->btnCancel->Size = System::Drawing::Size(100, 36);
			this->btnCancel->TabIndex = 12;
			this->btnCancel->Text = L"Clear";
			this->btnCancel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCancel->TextColor = System::Drawing::Color::Black;
			this->btnCancel->TooltipText = nullptr;
			this->btnCancel->UseAdvancedRendering = true;
			this->btnCancel->UseParticles = false;
			this->btnCancel->Click += gcnew System::EventHandler(this, &RegisterForm::btnCancel_Click);
			//
			// btnRegister
			//
			this->btnRegister->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnRegister->AccessibleName = L"Create Account";
			this->btnRegister->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnRegister->AutoSizeBasedOnText = false;
			this->btnRegister->BackColor = System::Drawing::Color::Transparent;
			this->btnRegister->BadgeBackColor = System::Drawing::Color::Black;
			this->btnRegister->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnRegister->BadgeValue = 0;
			this->btnRegister->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnRegister->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnRegister->BorderWidth = 1;
			this->btnRegister->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnRegister->ButtonImage = nullptr;
			this->btnRegister->ButtonTextLeftPadding = 0;
			this->btnRegister->CanBeep = true;
			this->btnRegister->CanGlow = false;
			this->btnRegister->CanShake = true;
			this->btnRegister->ContextMenuStripEx = nullptr;
			this->btnRegister->CornerRadiusBottomLeft = 6;
			this->btnRegister->CornerRadiusBottomRight = 6;
			this->btnRegister->CornerRadiusTopLeft = 6;
			this->btnRegister->CornerRadiusTopRight = 6;
			this->btnRegister->CustomCursor = System::Windows::Forms::Cursors::Default;
			this->btnRegister->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnRegister->EnableLongPress = false;
			this->btnRegister->EnableRippleEffect = true;
			this->btnRegister->EnableShadow = false;
			this->btnRegister->EnableTextWrapping = false;
			this->btnRegister->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			this->btnRegister->ForeColor = System::Drawing::Color::White;
			this->btnRegister->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnRegister->GlowIntensity = 100;
			this->btnRegister->GlowRadius = 20;
			this->btnRegister->GradientBackground = false;
			this->btnRegister->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnRegister->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnRegister->HintText = nullptr;
			this->btnRegister->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnRegister->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnRegister->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnRegister->HoverTransitionDuration = 250;
			this->btnRegister->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnRegister->ImagePadding = 5;
			this->btnRegister->ImageSize = System::Drawing::Size(16, 16);
			this->btnRegister->IsRadial = false;
			this->btnRegister->IsReadOnly = false;
			this->btnRegister->IsToggleButton = false;
			this->btnRegister->IsToggled = false;
			this->btnRegister->Location = System::Drawing::Point(763, 15);
			this->btnRegister->LongPressDurationMS = 1000;
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnRegister->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnRegister->ParticleCount = 15;
			this->btnRegister->PressAnimationScale = 0.97F;
			this->btnRegister->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnRegister->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnRegister->PressTransitionDuration = 150;
			this->btnRegister->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnRegister->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnRegister->RippleRadiusMultiplier = 0.6F;
			this->btnRegister->ShadowBlur = 5;
			this->btnRegister->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnRegister->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnRegister->ShakeDuration = 500;
			this->btnRegister->ShakeIntensity = 5;
			this->btnRegister->Size = System::Drawing::Size(130, 36);
			this->btnRegister->TabIndex = 11;
			this->btnRegister->Text = L"Create Account";
			this->btnRegister->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRegister->TextColor = System::Drawing::Color::White;
			this->btnRegister->TooltipText = nullptr;
			this->btnRegister->UseAdvancedRendering = true;
			this->btnRegister->UseParticles = false;
			this->btnRegister->Click += gcnew System::EventHandler(this, &RegisterForm::btnRegister_Click);
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
			this->siticonePanel1->Controls->Add(this->panelContent);
			this->siticonePanel1->Controls->Add(this->panelFooter);
			this->siticonePanel1->CornerRadiusBottomLeft = 5;
			this->siticonePanel1->CornerRadiusBottomRight = 5;
			this->siticonePanel1->CornerRadiusTopLeft = 5;
			this->siticonePanel1->CornerRadiusTopRight = 5;
			this->siticonePanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->siticonePanel1->EnableAcrylicEffect = false;
			this->siticonePanel1->EnableMicaEffect = false;
			this->siticonePanel1->EnableRippleEffect = false;
			this->siticonePanel1->FillColor = System::Drawing::Color::Transparent;
			this->siticonePanel1->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->siticonePanel1->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->siticonePanel1->Location = System::Drawing::Point(0, 70);
			this->siticonePanel1->Name = L"siticonePanel1";
			this->siticonePanel1->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->siticonePanel1->RippleAlpha = 50;
			this->siticonePanel1->RippleAlphaDecrement = 3;
			this->siticonePanel1->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->siticonePanel1->RippleMaxSize = 600;
			this->siticonePanel1->RippleSpeed = 15;
			this->siticonePanel1->ShowBorder = true;
			this->siticonePanel1->Size = System::Drawing::Size(916, 473);
			this->siticonePanel1->TabIndex = 18;
			this->siticonePanel1->TabStop = true;
			this->siticonePanel1->TrackSystemTheme = false;
			this->siticonePanel1->UseBorderGradient = true;
			this->siticonePanel1->UseMultiGradient = false;
			this->siticonePanel1->UsePatternTexture = false;
			this->siticonePanel1->UseRadialGradient = false;
			//
			// RegisterForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)), static_cast<System::Int32>(static_cast<System::Byte>(247)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->ClientSize = System::Drawing::Size(916, 543);
			this->Controls->Add(this->siticonePanel1);
			this->Controls->Add(this->panelHeader);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->MaximizeBox = false;
			this->Name = L"RegisterForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RegisterForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &RegisterForm::RegisterForm_KeyDown);
			this->panelContent->ResumeLayout(false);
			this->panelContent->PerformLayout();
			this->panelHeader->ResumeLayout(false);
			this->panelHeader->PerformLayout();
			this->panelFooter->ResumeLayout(false);
			this->siticonePanel1->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion
		// ============ Helper methods ============

		void SetStatus(String^ message, bool isError)
		{
			if (lblStatus == nullptr) return;

			if (isError)
				lblStatus->ForeColor = Color::FromArgb(200, 50, 50); // red-ish
			else
				lblStatus->ForeColor = Color::FromArgb(40, 140, 60); // green-ish

			lblStatus->Text = message;
		}

		bool ValidateRegistration()
		{
			SetStatus(L"", false);

			if (String::IsNullOrWhiteSpace(txtFullName->Text) ||
				String::IsNullOrWhiteSpace(txtEmail->Text) ||
				String::IsNullOrWhiteSpace(txtUsername->Text) ||
				String::IsNullOrWhiteSpace(txtPassword->Text) ||
				String::IsNullOrWhiteSpace(txtConfirmPassword->Text))
			{
				SetStatus(L"Please fill in all required fields.", true);
				return false;
			}

			if (txtPassword->Text->Length < 6)
			{
				SetStatus(L"Password must be at least 6 characters.", true);
				return false;
			}

			if (!txtEmail->Text->Contains("@"))
			{
				SetStatus(L"Please enter a valid email address.", true);
				return false;
			}

			if (txtPassword->Text != txtConfirmPassword->Text)
			{
				SetStatus(L"Passwords do not match.", true);
				return false;
			}

			// Ensure a role is selected
			bool anyRole =
				(chkIsEmployee != nullptr && chkIsEmployee->Checked) ||
				(chkIsManager != nullptr && chkIsManager->Checked) ||
				(chkIsAdmin != nullptr && chkIsAdmin->Checked);

			if (!anyRole)
			{
				SetStatus(L"Please select a role for this employee.", true);
				return false;
			}

			return true;
		}

		void ClearFields()
		{
			if (txtFullName != nullptr) txtFullName->Text = L"";
			if (txtEmail != nullptr) txtEmail->Text = L"";
			if (txtUsername != nullptr) txtUsername->Text = L"";
			if (txtPassword != nullptr) txtPassword->Text = L"";
			if (txtConfirmPassword != nullptr) txtConfirmPassword->Text = L"";
			if (cmbDepartment != nullptr && cmbDepartment->Items->Count > 0)
				cmbDepartment->SelectedIndex = 0;
			if (chkIsEmployee != nullptr) chkIsEmployee->Checked = true;
			if (chkIsManager != nullptr) chkIsManager->Checked = false;
			if (chkIsAdmin != nullptr) chkIsAdmin->Checked = false;
		}

		// ============ Event handlers ============

	private: System::Void chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		bool show = (chkShowPassword != nullptr && chkShowPassword->Checked);

		if (txtPassword != nullptr)
			txtPassword->UseSystemPasswordChar = !show;
		if (txtConfirmPassword != nullptr)
			txtConfirmPassword->UseSystemPasswordChar = !show;
	}

	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!ValidateRegistration())
			return;

		String^ username = txtUsername->Text->Trim();
		String^ password = txtPassword->Text;
		String^ fullName = txtFullName->Text->Trim();
		String^ email = txtEmail->Text->Trim();
		String^ department = (cmbDepartment != nullptr && cmbDepartment->SelectedItem != nullptr)
			? cmbDepartment->SelectedItem->ToString()
			: String::Empty;

		// Role flags
		bool isEmployee = (chkIsEmployee != nullptr && chkIsEmployee->Checked);
		bool isManager = (chkIsManager != nullptr && chkIsManager->Checked);
		bool isAdmin = (chkIsAdmin != nullptr && chkIsAdmin->Checked);

		// Business rule: admins are also managers (optional but usually useful)
		bool flagManager = isManager || isAdmin;
		bool flagAdmin = isAdmin;

		Employee^ emp = gcnew Employee();
		emp->Username = username;
		emp->FullName = fullName;
		emp->Email = email;
		emp->Department = department;
		emp->IsManager = flagManager;
		emp->IsAdministrator = flagAdmin;
		// extended profile left empty; employee can edit later in ProfileForm

		String^ error = nullptr;
		bool ok = EmployeeManager::CreateEmployee(emp, password, error);

		if (!ok)
		{
			if (String::IsNullOrEmpty(error))
				error = L"Failed to create employee.";
			SetStatus(error, true);
			return;
		}

		// If update succeeded, keep Session::CurrentUser in sync (we already updated e)
		MessageBox::Show(
			L"Employee created successfully (ID " + emp->Id.ToString() + L").",
			L"Profile",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);

		// Optionally clear fields for the next registration
		ClearFields();
	}

	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ClearFields();
	}
	private: System::Void RegisterForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Enter) {
			btnRegister_Click(sender, e);
			e->Handled = true;
		}
	}
	};
}
