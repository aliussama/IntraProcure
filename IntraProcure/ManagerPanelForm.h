#pragma once

#include "UiStyler.h"
#include "Session.h"
#include "RequestManager.h"
#include "DatabaseManager.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for ManagerPanelForm
	/// </summary>
	public ref class ManagerPanelForm : public System::Windows::Forms::Form
	{
	public:
		ManagerPanelForm(void)
		{
			InitializeComponent();

			// Apply shared styles
			UiStyler::StyleGrid(gridRequests);
			UiStyler::StylePrimaryButton(btnApprove);
			UiStyler::StyleSecondaryButton(btnReject);
			UiStyler::StyleButton(btnRefresh);

			_allRequests = gcnew List<RequestRow^>();

			InitializeRequests();
			InitializeFilters();   // sets SelectedIndex etc. (fires events once)
			SetupGrid();
			ApplyCurrentFilters(); // instead of PopulateGrid(_allRequests);
			RefreshDetails();
			UpdateKpis();
			SetRoleVisibility();
		}

	protected:
		~ManagerPanelForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: SiticoneNetFrameworkUI::SiticoneFlatPanel^ panelHeader;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::ComboBox^ cmbStatusFilter;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnRefresh;
	private: System::Windows::Forms::ComboBox^ cmbEmployeeFilter;
	private: System::Windows::Forms::Panel^ panelKpis;
	private: SiticoneNetFrameworkUI::SiticonePanel^ panelKpiPending;
	private: System::Windows::Forms::Label^ lblKpiPendingValue;
	private: System::Windows::Forms::Label^ lblKpiPendingTitle;
	private: SiticoneNetFrameworkUI::SiticonePanel^ panelKpiApproved;
	private: System::Windows::Forms::Label^ lblKpiApprovedValue;
	private: System::Windows::Forms::Label^ lblKpiApprovedTitle;
	private: SiticoneNetFrameworkUI::SiticonePanel^ panelKpiSpend;
	private: System::Windows::Forms::Label^ lblKpiSpendValue;
	private: System::Windows::Forms::Label^ lblKpiSpendTitle;
	private: System::Windows::Forms::SplitContainer^ splitMain;
	private: System::Windows::Forms::Panel^ panelGrid;
	private: System::Windows::Forms::DataGridView^ gridRequests;
	private: System::Windows::Forms::Panel^ panelDetails;
	private: System::Windows::Forms::Label^ lblDetailsTitle;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnReject;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnApprove;
	private: System::Windows::Forms::Label^ lblDetails;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;

	private:
		System::ComponentModel::Container^ components;

		// backing model for the grid
		ref struct RequestRow
		{
			int Id;
			int EmployeeId;
			String^ EmployeeName;
			String^ Department;
			double TotalAmount;
			String^ Status; // Pending, Approved, Rejected
		};

		List<RequestRow^>^ _allRequests;
		int _hoverRowIndex = -1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panelHeader = (gcnew SiticoneNetFrameworkUI::SiticoneFlatPanel());
			this->cmbEmployeeFilter = (gcnew System::Windows::Forms::ComboBox());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->cmbStatusFilter = (gcnew System::Windows::Forms::ComboBox());
			this->btnRefresh = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->panelKpis = (gcnew System::Windows::Forms::Panel());
			this->panelKpiSpend = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->lblKpiSpendValue = (gcnew System::Windows::Forms::Label());
			this->lblKpiSpendTitle = (gcnew System::Windows::Forms::Label());
			this->panelKpiApproved = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->lblKpiApprovedValue = (gcnew System::Windows::Forms::Label());
			this->lblKpiApprovedTitle = (gcnew System::Windows::Forms::Label());
			this->panelKpiPending = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->lblKpiPendingValue = (gcnew System::Windows::Forms::Label());
			this->lblKpiPendingTitle = (gcnew System::Windows::Forms::Label());
			this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			this->panelGrid = (gcnew System::Windows::Forms::Panel());
			this->gridRequests = (gcnew System::Windows::Forms::DataGridView());
			this->panelDetails = (gcnew System::Windows::Forms::Panel());
			this->btnReject = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->btnApprove = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->lblDetails = (gcnew System::Windows::Forms::Label());
			this->lblDetailsTitle = (gcnew System::Windows::Forms::Label());
			this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->panelHeader->SuspendLayout();
			this->panelKpis->SuspendLayout();
			this->panelKpiSpend->SuspendLayout();
			this->panelKpiApproved->SuspendLayout();
			this->panelKpiPending->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->BeginInit();
			this->splitMain->Panel1->SuspendLayout();
			this->splitMain->Panel2->SuspendLayout();
			this->splitMain->SuspendLayout();
			this->panelGrid->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridRequests))->BeginInit();
			this->panelDetails->SuspendLayout();
			this->siticonePanel1->SuspendLayout();
			this->SuspendLayout();
			//
			// panelHeader
			//
			this->panelHeader->BackColor = System::Drawing::Color::White;
			this->panelHeader->Controls->Add(this->cmbEmployeeFilter);
			this->panelHeader->Controls->Add(this->lblTitle);
			this->panelHeader->Controls->Add(this->cmbStatusFilter);
			this->panelHeader->Controls->Add(this->btnRefresh);
			this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelHeader->Location = System::Drawing::Point(0, 0);
			this->panelHeader->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->panelHeader->MinimumSize = System::Drawing::Size(20, 60);
			this->panelHeader->Name = L"panelHeader";
			this->panelHeader->Padding = System::Windows::Forms::Padding(15, 10, 15, 10);
			this->panelHeader->Size = System::Drawing::Size(916, 60);
			this->panelHeader->TabIndex = 0;
			//
			// cmbEmployeeFilter
			//
			this->cmbEmployeeFilter->BackColor = System::Drawing::Color::White;
			this->cmbEmployeeFilter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbEmployeeFilter->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbEmployeeFilter->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cmbEmployeeFilter->FormattingEnabled = true;
			this->cmbEmployeeFilter->Location = System::Drawing::Point(450, 18);
			this->cmbEmployeeFilter->Name = L"cmbEmployeeFilter";
			this->cmbEmployeeFilter->Size = System::Drawing::Size(150, 23);
			this->cmbEmployeeFilter->TabIndex = 3;
			this->cmbEmployeeFilter->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerPanelForm::cmbEmployeeFilter_SelectedIndexChanged);
			//
			// lblTitle
			//
			this->lblTitle->AutoSize = true;
			this->lblTitle->BackColor = System::Drawing::Color::Transparent;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblTitle->Location = System::Drawing::Point(15, 18);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(194, 25);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Manager Dashboard";
			//
			// cmbStatusFilter
			//
			this->cmbStatusFilter->BackColor = System::Drawing::Color::White;
			this->cmbStatusFilter->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbStatusFilter->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbStatusFilter->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->cmbStatusFilter->FormattingEnabled = true;
			this->cmbStatusFilter->Location = System::Drawing::Point(320, 18);
			this->cmbStatusFilter->Name = L"cmbStatusFilter";
			this->cmbStatusFilter->Size = System::Drawing::Size(120, 23);
			this->cmbStatusFilter->TabIndex = 2;
			this->cmbStatusFilter->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerPanelForm::cmbStatusFilter_SelectedIndexChanged);
			//
			// btnRefresh
			//
			this->btnRefresh->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnRefresh->AccessibleName = L"Refresh";
			this->btnRefresh->AutoSizeBasedOnText = false;
			this->btnRefresh->BackColor = System::Drawing::Color::Transparent;
			this->btnRefresh->BadgeBackColor = System::Drawing::Color::Black;
			this->btnRefresh->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->BadgeValue = 0;
			this->btnRefresh->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnRefresh->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnRefresh->BorderWidth = 1;
			this->btnRefresh->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(117)),
				static_cast<System::Int32>(static_cast<System::Byte>(189)));
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
			this->btnRefresh->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnRefresh->CustomCursor = System::Windows::Forms::Cursors::Hand;
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
			this->btnRefresh->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(15)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(140)));
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
			this->btnRefresh->Location = System::Drawing::Point(627, 16);
			this->btnRefresh->LongPressDurationMS = 1000;
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnRefresh->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnRefresh->ParticleCount = 15;
			this->btnRefresh->PressAnimationScale = 0.97F;
			this->btnRefresh->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
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
			this->btnRefresh->Size = System::Drawing::Size(80, 28);
			this->btnRefresh->TabIndex = 5;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRefresh->TextColor = System::Drawing::Color::White;
			this->btnRefresh->TooltipText = nullptr;
			this->btnRefresh->UseAdvancedRendering = true;
			this->btnRefresh->UseParticles = false;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &ManagerPanelForm::btnRefresh_Click);
			//
			// panelKpis
			//
			this->panelKpis->BackColor = System::Drawing::Color::Transparent;
			this->panelKpis->Controls->Add(this->panelKpiSpend);
			this->panelKpis->Controls->Add(this->panelKpiApproved);
			this->panelKpis->Controls->Add(this->panelKpiPending);
			this->panelKpis->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelKpis->Location = System::Drawing::Point(2, 2);
			this->panelKpis->Name = L"panelKpis";
			this->panelKpis->Padding = System::Windows::Forms::Padding(15, 10, 15, 10);
			this->panelKpis->Size = System::Drawing::Size(911, 80);
			this->panelKpis->TabIndex = 1;
			//
			// panelKpiSpend
			//
			this->panelKpiSpend->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiSpend->BackColor = System::Drawing::Color::Transparent;
			this->panelKpiSpend->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			this->panelKpiSpend->BorderDashPattern = nullptr;
			this->panelKpiSpend->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiSpend->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiSpend->BorderThickness = 2;
			this->panelKpiSpend->Controls->Add(this->lblKpiSpendValue);
			this->panelKpiSpend->Controls->Add(this->lblKpiSpendTitle);
			this->panelKpiSpend->CornerRadiusBottomLeft = 8;
			this->panelKpiSpend->CornerRadiusBottomRight = 8;
			this->panelKpiSpend->CornerRadiusTopLeft = 8;
			this->panelKpiSpend->CornerRadiusTopRight = 8;
			this->panelKpiSpend->EnableAcrylicEffect = false;
			this->panelKpiSpend->EnableMicaEffect = false;
			this->panelKpiSpend->EnableRippleEffect = false;
			this->panelKpiSpend->FillColor = System::Drawing::Color::White;
			this->panelKpiSpend->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->panelKpiSpend->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->panelKpiSpend->Location = System::Drawing::Point(405, 10);
			this->panelKpiSpend->Name = L"panelKpiSpend";
			this->panelKpiSpend->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->panelKpiSpend->RippleAlpha = 50;
			this->panelKpiSpend->RippleAlphaDecrement = 3;
			this->panelKpiSpend->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiSpend->RippleMaxSize = 600;
			this->panelKpiSpend->RippleSpeed = 15;
			this->panelKpiSpend->ShowBorder = true;
			this->panelKpiSpend->Size = System::Drawing::Size(220, 60);
			this->panelKpiSpend->TabIndex = 5;
			this->panelKpiSpend->TabStop = true;
			this->panelKpiSpend->TrackSystemTheme = false;
			this->panelKpiSpend->UseBorderGradient = true;
			this->panelKpiSpend->UseMultiGradient = false;
			this->panelKpiSpend->UsePatternTexture = false;
			this->panelKpiSpend->UseRadialGradient = false;
			//
			// lblKpiSpendValue
			//
			this->lblKpiSpendValue->AutoSize = true;
			this->lblKpiSpendValue->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiSpendValue->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold));
			this->lblKpiSpendValue->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblKpiSpendValue->Location = System::Drawing::Point(10, 25);
			this->lblKpiSpendValue->MaximumSize = System::Drawing::Size(205, 0);
			this->lblKpiSpendValue->Name = L"lblKpiSpendValue";
			this->lblKpiSpendValue->Size = System::Drawing::Size(99, 30);
			this->lblKpiSpendValue->TabIndex = 2;
			this->lblKpiSpendValue->Text = L"0.00 EGP";
			//
			// lblKpiSpendTitle
			//
			this->lblKpiSpendTitle->AutoSize = true;
			this->lblKpiSpendTitle->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiSpendTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblKpiSpendTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->lblKpiSpendTitle->Location = System::Drawing::Point(10, 8);
			this->lblKpiSpendTitle->Name = L"lblKpiSpendTitle";
			this->lblKpiSpendTitle->Size = System::Drawing::Size(111, 15);
			this->lblKpiSpendTitle->TabIndex = 1;
			this->lblKpiSpendTitle->Text = L"This Month\'s Spend";
			//
			// panelKpiApproved
			//
			this->panelKpiApproved->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiApproved->BackColor = System::Drawing::Color::Transparent;
			this->panelKpiApproved->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			this->panelKpiApproved->BorderDashPattern = nullptr;
			this->panelKpiApproved->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiApproved->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiApproved->BorderThickness = 2;
			this->panelKpiApproved->Controls->Add(this->lblKpiApprovedValue);
			this->panelKpiApproved->Controls->Add(this->lblKpiApprovedTitle);
			this->panelKpiApproved->CornerRadiusBottomLeft = 8;
			this->panelKpiApproved->CornerRadiusBottomRight = 8;
			this->panelKpiApproved->CornerRadiusTopLeft = 8;
			this->panelKpiApproved->CornerRadiusTopRight = 8;
			this->panelKpiApproved->EnableAcrylicEffect = false;
			this->panelKpiApproved->EnableMicaEffect = false;
			this->panelKpiApproved->EnableRippleEffect = false;
			this->panelKpiApproved->FillColor = System::Drawing::Color::White;
			this->panelKpiApproved->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->panelKpiApproved->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->panelKpiApproved->Location = System::Drawing::Point(210, 10);
			this->panelKpiApproved->Name = L"panelKpiApproved";
			this->panelKpiApproved->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->panelKpiApproved->RippleAlpha = 50;
			this->panelKpiApproved->RippleAlphaDecrement = 3;
			this->panelKpiApproved->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiApproved->RippleMaxSize = 600;
			this->panelKpiApproved->RippleSpeed = 15;
			this->panelKpiApproved->ShowBorder = true;
			this->panelKpiApproved->Size = System::Drawing::Size(180, 60);
			this->panelKpiApproved->TabIndex = 4;
			this->panelKpiApproved->TabStop = true;
			this->panelKpiApproved->TrackSystemTheme = false;
			this->panelKpiApproved->UseBorderGradient = true;
			this->panelKpiApproved->UseMultiGradient = false;
			this->panelKpiApproved->UsePatternTexture = false;
			this->panelKpiApproved->UseRadialGradient = false;
			//
			// lblKpiApprovedValue
			//
			this->lblKpiApprovedValue->AutoSize = true;
			this->lblKpiApprovedValue->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiApprovedValue->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold));
			this->lblKpiApprovedValue->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblKpiApprovedValue->Location = System::Drawing::Point(10, 25);
			this->lblKpiApprovedValue->Name = L"lblKpiApprovedValue";
			this->lblKpiApprovedValue->Size = System::Drawing::Size(25, 30);
			this->lblKpiApprovedValue->TabIndex = 2;
			this->lblKpiApprovedValue->Text = L"0";
			//
			// lblKpiApprovedTitle
			//
			this->lblKpiApprovedTitle->AutoSize = true;
			this->lblKpiApprovedTitle->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiApprovedTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblKpiApprovedTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->lblKpiApprovedTitle->Location = System::Drawing::Point(10, 8);
			this->lblKpiApprovedTitle->Name = L"lblKpiApprovedTitle";
			this->lblKpiApprovedTitle->Size = System::Drawing::Size(93, 15);
			this->lblKpiApprovedTitle->TabIndex = 1;
			this->lblKpiApprovedTitle->Text = L"Approved Today";
			//
			// panelKpiPending
			//
			this->panelKpiPending->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiPending->BackColor = System::Drawing::Color::Transparent;
			this->panelKpiPending->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			this->panelKpiPending->BorderDashPattern = nullptr;
			this->panelKpiPending->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiPending->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)),
				static_cast<System::Int32>(static_cast<System::Byte>(223)), static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->panelKpiPending->BorderThickness = 2;
			this->panelKpiPending->Controls->Add(this->lblKpiPendingValue);
			this->panelKpiPending->Controls->Add(this->lblKpiPendingTitle);
			this->panelKpiPending->CornerRadiusBottomLeft = 8;
			this->panelKpiPending->CornerRadiusBottomRight = 8;
			this->panelKpiPending->CornerRadiusTopLeft = 8;
			this->panelKpiPending->CornerRadiusTopRight = 8;
			this->panelKpiPending->EnableAcrylicEffect = false;
			this->panelKpiPending->EnableMicaEffect = false;
			this->panelKpiPending->EnableRippleEffect = false;
			this->panelKpiPending->FillColor = System::Drawing::Color::White;
			this->panelKpiPending->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->panelKpiPending->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->panelKpiPending->Location = System::Drawing::Point(15, 10);
			this->panelKpiPending->Name = L"panelKpiPending";
			this->panelKpiPending->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->panelKpiPending->RippleAlpha = 50;
			this->panelKpiPending->RippleAlphaDecrement = 3;
			this->panelKpiPending->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelKpiPending->RippleMaxSize = 600;
			this->panelKpiPending->RippleSpeed = 15;
			this->panelKpiPending->ShowBorder = true;
			this->panelKpiPending->Size = System::Drawing::Size(180, 60);
			this->panelKpiPending->TabIndex = 3;
			this->panelKpiPending->TabStop = true;
			this->panelKpiPending->TrackSystemTheme = false;
			this->panelKpiPending->UseBorderGradient = true;
			this->panelKpiPending->UseMultiGradient = false;
			this->panelKpiPending->UsePatternTexture = false;
			this->panelKpiPending->UseRadialGradient = false;
			//
			// lblKpiPendingValue
			//
			this->lblKpiPendingValue->AutoSize = true;
			this->lblKpiPendingValue->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiPendingValue->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 16, System::Drawing::FontStyle::Bold));
			this->lblKpiPendingValue->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblKpiPendingValue->Location = System::Drawing::Point(10, 25);
			this->lblKpiPendingValue->Name = L"lblKpiPendingValue";
			this->lblKpiPendingValue->Size = System::Drawing::Size(25, 30);
			this->lblKpiPendingValue->TabIndex = 2;
			this->lblKpiPendingValue->Text = L"0";
			//
			// lblKpiPendingTitle
			//
			this->lblKpiPendingTitle->AutoSize = true;
			this->lblKpiPendingTitle->BackColor = System::Drawing::Color::Transparent;
			this->lblKpiPendingTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblKpiPendingTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->lblKpiPendingTitle->Location = System::Drawing::Point(10, 8);
			this->lblKpiPendingTitle->Name = L"lblKpiPendingTitle";
			this->lblKpiPendingTitle->Size = System::Drawing::Size(51, 15);
			this->lblKpiPendingTitle->TabIndex = 1;
			this->lblKpiPendingTitle->Text = L"Pending";
			//
			// splitMain
			//
			this->splitMain->BackColor = System::Drawing::Color::Transparent;
			this->splitMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitMain->Location = System::Drawing::Point(2, 82);
			this->splitMain->Name = L"splitMain";
			//
			// splitMain.Panel1
			//
			this->splitMain->Panel1->Controls->Add(this->panelGrid);
			this->splitMain->Panel1MinSize = 300;
			//
			// splitMain.Panel2
			//
			this->splitMain->Panel2->Controls->Add(this->panelDetails);
			this->splitMain->Panel2MinSize = 200;
			this->splitMain->Size = System::Drawing::Size(911, 399);
			this->splitMain->SplitterDistance = 603;
			this->splitMain->TabIndex = 2;
			//
			// panelGrid
			//
			this->panelGrid->Controls->Add(this->gridRequests);
			this->panelGrid->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelGrid->Location = System::Drawing::Point(0, 0);
			this->panelGrid->Name = L"panelGrid";
			this->panelGrid->Padding = System::Windows::Forms::Padding(15, 10, 15, 10);
			this->panelGrid->Size = System::Drawing::Size(603, 399);
			this->panelGrid->TabIndex = 0;
			//
			// gridRequests
			//
			this->gridRequests->AllowUserToAddRows = false;
			this->gridRequests->AllowUserToDeleteRows = false;
			this->gridRequests->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->gridRequests->BackgroundColor = System::Drawing::Color::White;
			this->gridRequests->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->gridRequests->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridRequests->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gridRequests->Location = System::Drawing::Point(15, 10);
			this->gridRequests->MultiSelect = false;
			this->gridRequests->Name = L"gridRequests";
			this->gridRequests->ReadOnly = true;
			this->gridRequests->RowHeadersVisible = false;
			this->gridRequests->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->gridRequests->Size = System::Drawing::Size(573, 379);
			this->gridRequests->TabIndex = 0;
			this->gridRequests->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ManagerPanelForm::gridRequests_CellContentClick);
			this->gridRequests->CellMouseEnter += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ManagerPanelForm::gridRequests_CellMouseEnter);
			this->gridRequests->CellMouseLeave += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ManagerPanelForm::gridRequests_CellMouseLeave);
			this->gridRequests->CurrentCellDirtyStateChanged += gcnew System::EventHandler(this, &ManagerPanelForm::gridRequests_CurrentCellDirtyStateChanged);
			this->gridRequests->SelectionChanged += gcnew System::EventHandler(this, &ManagerPanelForm::gridRequests_SelectionChanged);
			//
			// panelDetails
			//
			this->panelDetails->BackColor = System::Drawing::Color::White;
			this->panelDetails->Controls->Add(this->btnReject);
			this->panelDetails->Controls->Add(this->btnApprove);
			this->panelDetails->Controls->Add(this->lblDetails);
			this->panelDetails->Controls->Add(this->lblDetailsTitle);
			this->panelDetails->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelDetails->Location = System::Drawing::Point(0, 0);
			this->panelDetails->Name = L"panelDetails";
			this->panelDetails->Padding = System::Windows::Forms::Padding(10);
			this->panelDetails->Size = System::Drawing::Size(304, 399);
			this->panelDetails->TabIndex = 0;
			//
			// btnReject
			//
			this->btnReject->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnReject->AccessibleName = L"Reject";
			this->btnReject->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnReject->AutoSizeBasedOnText = false;
			this->btnReject->BackColor = System::Drawing::Color::Transparent;
			this->btnReject->BadgeBackColor = System::Drawing::Color::Black;
			this->btnReject->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnReject->BadgeValue = 0;
			this->btnReject->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnReject->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnReject->BorderWidth = 1;
			this->btnReject->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(50)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->btnReject->ButtonImage = nullptr;
			this->btnReject->ButtonTextLeftPadding = 0;
			this->btnReject->CanBeep = true;
			this->btnReject->CanGlow = false;
			this->btnReject->CanShake = true;
			this->btnReject->ContextMenuStripEx = nullptr;
			this->btnReject->CornerRadiusBottomLeft = 6;
			this->btnReject->CornerRadiusBottomRight = 6;
			this->btnReject->CornerRadiusTopLeft = 6;
			this->btnReject->CornerRadiusTopRight = 6;
			this->btnReject->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnReject->CustomCursor = System::Windows::Forms::Cursors::Hand;
			this->btnReject->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnReject->EnableLongPress = false;
			this->btnReject->EnableRippleEffect = true;
			this->btnReject->EnableShadow = false;
			this->btnReject->EnableTextWrapping = false;
			this->btnReject->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			this->btnReject->ForeColor = System::Drawing::Color::White;
			this->btnReject->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnReject->GlowIntensity = 100;
			this->btnReject->GlowRadius = 20;
			this->btnReject->GradientBackground = false;
			this->btnReject->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnReject->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnReject->HintText = nullptr;
			this->btnReject->HoverBackColor = System::Drawing::Color::DarkRed;
			this->btnReject->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReject->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReject->HoverTransitionDuration = 250;
			this->btnReject->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnReject->ImagePadding = 5;
			this->btnReject->ImageSize = System::Drawing::Size(16, 16);
			this->btnReject->IsRadial = false;
			this->btnReject->IsReadOnly = false;
			this->btnReject->IsToggleButton = false;
			this->btnReject->IsToggled = false;
			this->btnReject->Location = System::Drawing::Point(181, 356);
			this->btnReject->LongPressDurationMS = 1000;
			this->btnReject->Name = L"btnReject";
			this->btnReject->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReject->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnReject->ParticleCount = 15;
			this->btnReject->PressAnimationScale = 0.97F;
			this->btnReject->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnReject->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReject->PressTransitionDuration = 150;
			this->btnReject->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnReject->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReject->RippleRadiusMultiplier = 0.6F;
			this->btnReject->ShadowBlur = 5;
			this->btnReject->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReject->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnReject->ShakeDuration = 500;
			this->btnReject->ShakeIntensity = 5;
			this->btnReject->Size = System::Drawing::Size(110, 30);
			this->btnReject->TabIndex = 3;
			this->btnReject->Text = L"Reject";
			this->btnReject->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnReject->TextColor = System::Drawing::Color::White;
			this->btnReject->TooltipText = nullptr;
			this->btnReject->UseAdvancedRendering = true;
			this->btnReject->UseParticles = false;
			this->btnReject->Click += gcnew System::EventHandler(this, &ManagerPanelForm::btnReject_Click);
			//
			// btnApprove
			//
			this->btnApprove->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnApprove->AccessibleName = L"Approve";
			this->btnApprove->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnApprove->AutoSizeBasedOnText = false;
			this->btnApprove->BackColor = System::Drawing::Color::Transparent;
			this->btnApprove->BadgeBackColor = System::Drawing::Color::Black;
			this->btnApprove->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnApprove->BadgeValue = 0;
			this->btnApprove->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnApprove->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnApprove->BorderWidth = 1;
			this->btnApprove->ButtonBackColor = System::Drawing::Color::ForestGreen;
			this->btnApprove->ButtonImage = nullptr;
			this->btnApprove->ButtonTextLeftPadding = 0;
			this->btnApprove->CanBeep = true;
			this->btnApprove->CanGlow = false;
			this->btnApprove->CanShake = true;
			this->btnApprove->ContextMenuStripEx = nullptr;
			this->btnApprove->CornerRadiusBottomLeft = 6;
			this->btnApprove->CornerRadiusBottomRight = 6;
			this->btnApprove->CornerRadiusTopLeft = 6;
			this->btnApprove->CornerRadiusTopRight = 6;
			this->btnApprove->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnApprove->CustomCursor = System::Windows::Forms::Cursors::Hand;
			this->btnApprove->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnApprove->EnableLongPress = false;
			this->btnApprove->EnableRippleEffect = true;
			this->btnApprove->EnableShadow = false;
			this->btnApprove->EnableTextWrapping = false;
			this->btnApprove->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold));
			this->btnApprove->ForeColor = System::Drawing::Color::White;
			this->btnApprove->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnApprove->GlowIntensity = 100;
			this->btnApprove->GlowRadius = 20;
			this->btnApprove->GradientBackground = false;
			this->btnApprove->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnApprove->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnApprove->HintText = nullptr;
			this->btnApprove->HoverBackColor = System::Drawing::Color::DarkGreen;
			this->btnApprove->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnApprove->HoverTextColor = System::Drawing::Color::White;
			this->btnApprove->HoverTransitionDuration = 250;
			this->btnApprove->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnApprove->ImagePadding = 5;
			this->btnApprove->ImageSize = System::Drawing::Size(16, 16);
			this->btnApprove->IsRadial = false;
			this->btnApprove->IsReadOnly = false;
			this->btnApprove->IsToggleButton = false;
			this->btnApprove->IsToggled = false;
			this->btnApprove->Location = System::Drawing::Point(61, 356);
			this->btnApprove->LongPressDurationMS = 1000;
			this->btnApprove->Name = L"btnApprove";
			this->btnApprove->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnApprove->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnApprove->ParticleCount = 15;
			this->btnApprove->PressAnimationScale = 0.97F;
			this->btnApprove->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnApprove->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnApprove->PressTransitionDuration = 150;
			this->btnApprove->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnApprove->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnApprove->RippleRadiusMultiplier = 0.6F;
			this->btnApprove->ShadowBlur = 5;
			this->btnApprove->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnApprove->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnApprove->ShakeDuration = 500;
			this->btnApprove->ShakeIntensity = 5;
			this->btnApprove->Size = System::Drawing::Size(110, 30);
			this->btnApprove->TabIndex = 2;
			this->btnApprove->Text = L"Approve";
			this->btnApprove->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnApprove->TextColor = System::Drawing::Color::White;
			this->btnApprove->TooltipText = nullptr;
			this->btnApprove->UseAdvancedRendering = true;
			this->btnApprove->UseParticles = false;
			this->btnApprove->Click += gcnew System::EventHandler(this, &ManagerPanelForm::btnApprove_Click);
			//
			// lblDetails
			//
			this->lblDetails->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lblDetails->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->lblDetails->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(80)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->lblDetails->Location = System::Drawing::Point(10, 35);
			this->lblDetails->Name = L"lblDetails";
			this->lblDetails->Size = System::Drawing::Size(250, 303);
			this->lblDetails->TabIndex = 1;
			//
			// lblDetailsTitle
			//
			this->lblDetailsTitle->AutoSize = true;
			this->lblDetailsTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.5F, System::Drawing::FontStyle::Bold));
			this->lblDetailsTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblDetailsTitle->Location = System::Drawing::Point(10, 10);
			this->lblDetailsTitle->Name = L"lblDetailsTitle";
			this->lblDetailsTitle->Size = System::Drawing::Size(111, 19);
			this->lblDetailsTitle->TabIndex = 0;
			this->lblDetailsTitle->Text = L"Request Details";
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
			this->siticonePanel1->Controls->Add(this->splitMain);
			this->siticonePanel1->Controls->Add(this->panelKpis);
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
			this->siticonePanel1->TabIndex = 4;
			this->siticonePanel1->TabStop = true;
			this->siticonePanel1->TrackSystemTheme = false;
			this->siticonePanel1->UseBorderGradient = true;
			this->siticonePanel1->UseMultiGradient = false;
			this->siticonePanel1->UsePatternTexture = false;
			this->siticonePanel1->UseRadialGradient = false;
			//
			// ManagerPanelForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->ClientSize = System::Drawing::Size(916, 543);
			this->Controls->Add(this->siticonePanel1);
			this->Controls->Add(this->panelHeader);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4, 3, 4, 3);
			this->Name = L"ManagerPanelForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Manager Dashboard - IntraProcure";
			this->panelHeader->ResumeLayout(false);
			this->panelHeader->PerformLayout();
			this->panelKpis->ResumeLayout(false);
			this->panelKpiSpend->ResumeLayout(false);
			this->panelKpiSpend->PerformLayout();
			this->panelKpiApproved->ResumeLayout(false);
			this->panelKpiApproved->PerformLayout();
			this->panelKpiPending->ResumeLayout(false);
			this->panelKpiPending->PerformLayout();
			this->splitMain->Panel1->ResumeLayout(false);
			this->splitMain->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->EndInit();
			this->splitMain->ResumeLayout(false);
			this->panelGrid->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridRequests))->EndInit();
			this->panelDetails->ResumeLayout(false);
			this->panelDetails->PerformLayout();
			this->siticonePanel1->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion

		// --------------------- Data loading & grid setup ---------------------

		void InitializeRequests()
		{
			_allRequests->Clear();

			SqlConnection^ conn = DatabaseManager::CreateConnection();
			try
			{
				conn->Open();

				String^ sql =
					"SELECT R.Id, "
					"       ISNULL(E.FullName, E.Username) AS EmployeeName, "
					"       ISNULL(R.EmployeeId, 0) AS EmployeeId, "
					"       ISNULL(R.Department, '') AS Department, "
					"       ISNULL(SUM(RI.Quantity * RI.UnitPrice), 0) AS TotalAmount, "
					"       R.Status "
					"FROM procure.Requests R "
					"LEFT JOIN procure.Employees E     ON R.EmployeeId = E.Id "
					"LEFT JOIN procure.RequestItems RI ON R.Id = RI.RequestId "
					"GROUP BY R.Id, R.EmployeeId, ISNULL(E.FullName, E.Username), ISNULL(R.Department, ''), R.Status "
					"ORDER BY R.Id DESC;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				SqlDataReader^ r = cmd->ExecuteReader();

				while (r->Read())
				{
					RequestRow^ row = gcnew RequestRow();
					row->Id = safe_cast<int>(r["Id"]);
					row->EmployeeId = safe_cast<int>(r["EmployeeId"]);
					row->EmployeeName = r["EmployeeName"]->ToString();
					row->Department = r["Department"]->ToString();
					row->TotalAmount = System::Convert::ToDouble(r["TotalAmount"]);
					row->Status = r["Status"]->ToString();
					_allRequests->Add(row);
				}
				r->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(
					L"Error loading requests:\n" + ex->Message,
					L"Manager Panel",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			finally
			{
				if (conn != nullptr && conn->State == ConnectionState::Open)
					conn->Close();
			}
		}

		bool _isInitializingFilters = false;

		void InitializeFilters()
		{
			_isInitializingFilters = true;

			cmbStatusFilter->Items->Clear();
			cmbStatusFilter->Items->Add(L"All");
			cmbStatusFilter->Items->Add(L"Pending");
			cmbStatusFilter->Items->Add(L"Approved");
			cmbStatusFilter->Items->Add(L"Rejected");
			cmbStatusFilter->SelectedIndex = 0;

			// Employee filter
			auto names = gcnew System::Collections::Generic::HashSet<String^>();
			for each(RequestRow ^ r in _allRequests)
			{
				if (!String::IsNullOrWhiteSpace(r->EmployeeName))
					names->Add(r->EmployeeName);
			}

			cmbEmployeeFilter->Items->Clear();
			cmbEmployeeFilter->Items->Add(L"All");
			for each(String ^ n in names)
				cmbEmployeeFilter->Items->Add(n);
			cmbEmployeeFilter->SelectedIndex = 0;

			_isInitializingFilters = false;
		}

		void SetupGrid()
		{
			gridRequests->Columns->Clear();
			gridRequests->AutoGenerateColumns = false;
			gridRequests->ReadOnly = false; // checkbox must be editable
			gridRequests->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			gridRequests->MultiSelect = false;

			// Checkbox column
			DataGridViewCheckBoxColumn^ colSelect = gcnew DataGridViewCheckBoxColumn();
			colSelect->Name = L"Select";
			colSelect->HeaderText = L"";
			colSelect->Width = 35;
			colSelect->FillWeight = 40;
			colSelect->ThreeState = false;
			colSelect->TrueValue = true;
			colSelect->FalseValue = false;
			colSelect->ValueType = bool::typeid;
			colSelect->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			colSelect->ReadOnly = false;
			gridRequests->Columns->Add(colSelect);

			// ID
			DataGridViewTextBoxColumn^ colId = gcnew DataGridViewTextBoxColumn();
			colId->Name = L"Id";
			colId->HeaderText = L"ID";
			colId->Width = 35;
			colId->ReadOnly = true;
			gridRequests->Columns->Add(colId);

			// ID
			DataGridViewTextBoxColumn^ colEmpId = gcnew DataGridViewTextBoxColumn();
			colEmpId->Name = L"EmpId";
			colEmpId->HeaderText = L"Employee ID";
			colEmpId->Width = 35;
			colEmpId->ReadOnly = true;
			gridRequests->Columns->Add(colEmpId);

			// Employee
			DataGridViewTextBoxColumn^ colEmp = gcnew DataGridViewTextBoxColumn();
			colEmp->Name = L"Employee";
			colEmp->HeaderText = L"Employee";
			colEmp->Width = 200;
			colEmp->ReadOnly = true;
			gridRequests->Columns->Add(colEmp);

			// Department
			DataGridViewTextBoxColumn^ colDept = gcnew DataGridViewTextBoxColumn();
			colDept->Name = L"Department";
			colDept->HeaderText = L"Department";
			colDept->Width = 120;
			colDept->ReadOnly = true;
			gridRequests->Columns->Add(colDept);

			// Total
			DataGridViewTextBoxColumn^ colTotal = gcnew DataGridViewTextBoxColumn();
			colTotal->Name = L"Total";
			colTotal->HeaderText = L"Total";
			colTotal->Width = 90;
			colTotal->ReadOnly = true;
			gridRequests->Columns->Add(colTotal);

			// Status
			DataGridViewTextBoxColumn^ colStatus = gcnew DataGridViewTextBoxColumn();
			colStatus->Name = L"Status";
			colStatus->HeaderText = L"Status";
			colStatus->Width = 90;
			colStatus->ReadOnly = true;
			gridRequests->Columns->Add(colStatus);
		}

		void PopulateGrid(List<RequestRow^>^ list)
		{
			gridRequests->Rows->Clear();

			for each(RequestRow ^ r in list)
			{
				int idx = gridRequests->Rows->Add();
				DataGridViewRow^ row = gridRequests->Rows[idx];

				row->Cells[L"Select"]->Value = false;
				row->Cells[L"Id"]->Value = r->Id;
				row->Cells[L"EmpId"]->Value = r->EmployeeId;
				row->Cells[L"Employee"]->Value = r->EmployeeName;
				row->Cells[L"Department"]->Value = r->Department;
				row->Cells[L"Total"]->Value = r->TotalAmount.ToString(L"N2") + " EGP";
				row->Cells[L"Status"]->Value = r->Status;
			}

			lblDetails->Text = L"None selected";
		}

		RequestRow^ GetSelectedRequest()
		{
			if (gridRequests->SelectedRows->Count == 0)
				return nullptr;

			int rowIndex = gridRequests->SelectedRows[0]->Index;
			if (rowIndex < 0 || rowIndex >= gridRequests->Rows->Count)
				return nullptr;

			Object^ idVal = gridRequests->Rows[rowIndex]->Cells[L"Id"]->Value;
			if (idVal == nullptr) return nullptr;
			int id = System::Convert::ToInt32(idVal);

			for each(RequestRow ^ r in _allRequests)
				if (r->Id == id) return r;

			return nullptr;
		}

		void RefreshDetails()
		{
			RequestRow^ r = GetSelectedRequest();
			if (r == nullptr)
			{
				lblDetails->Text = L"None selected";
				return;
			}

			lblDetails->Text =
				L"ID " + r->Id +
				L" | Employee ID: " + r->EmployeeId +
				L" | " + r->EmployeeName +
				L" | Dept: " + r->Department +
				L" | Total: " + r->TotalAmount.ToString(L"N2") + L" EGP" +
				L" | Status: " + r->Status;
		}

		void UpdateKpis()
		{
			int pending = 0;
			int approved = 0;
			double totalSpend = 0.0;

			for each(RequestRow ^ r in _allRequests)
			{
				if (r->Status == L"Pending")   pending++;
				if (r->Status == L"Approved")
				{
					approved++;
					totalSpend += r->TotalAmount;
				}
			}

			lblKpiPendingValue->Text = pending.ToString();
			lblKpiApprovedValue->Text = approved.ToString();
			lblKpiSpendValue->Text = totalSpend.ToString(L"N2") + L" EGP";
		}

		// -------------------- Selection helpers & role visibility --------------------

		// Collect selected request IDs. Prefer checkboxes; if none checked, fall back to selected row.
		List<int>^ GetSelectedRequestIds()
		{
			List<int>^ ids = gcnew List<int>();

			// From checkbox column "Select"
			for each(DataGridViewRow ^ row in gridRequests->Rows)
			{
				if (row->IsNewRow) continue;

				bool isChecked = false;
				Object^ cellVal = row->Cells[L"Select"]->Value;
				if (cellVal != nullptr)
				{
					try { isChecked = System::Convert::ToBoolean(cellVal); }
					catch (...) { isChecked = false; }
				}

				if (!isChecked) continue;

				Object^ idVal = row->Cells[L"Id"]->Value;
				if (idVal != nullptr)
				{
					try { ids->Add(System::Convert::ToInt32(idVal)); }
					catch (...) {}
				}
			}

			// If nothing checked, fall back to selected row
			if (ids->Count == 0 && gridRequests->SelectedRows->Count > 0)
			{
				DataGridViewRow^ row = gridRequests->SelectedRows[0];
				Object^ idVal = row->Cells[L"Id"]->Value;
				if (idVal != nullptr)
				{
					try { ids->Add(System::Convert::ToInt32(idVal)); }
					catch (...) {}
				}
			}

			return ids;
		}

		void SetRoleVisibility()
		{
			try
			{
				bool allowApproval = Session::IsManager || Session::IsAdministrator;
				btnApprove->Visible = allowApproval;
				btnReject->Visible = allowApproval;
			}
			catch (Exception^)
			{
				btnApprove->Visible = false;
				btnReject->Visible = false;
			}
		}

		// Rebuild employee filter items but try to preserve previous selection
		void UpdateEmployeeFilterPreserve(String^ previousSelection)
		{
			System::Collections::Generic::HashSet<String^>^ names = gcnew System::Collections::Generic::HashSet<String^>();
			for each(RequestRow ^ r in _allRequests)
			{
				if (!String::IsNullOrWhiteSpace(r->EmployeeName))
					names->Add(r->EmployeeName);
			}

			cmbEmployeeFilter->Items->Clear();
			cmbEmployeeFilter->Items->Add(L"All");
			for each(String ^ n in names)
				cmbEmployeeFilter->Items->Add(n);

			if (!String::IsNullOrEmpty(previousSelection))
			{
				int idx = cmbEmployeeFilter->Items->IndexOf(previousSelection);
				cmbEmployeeFilter->SelectedIndex = (idx >= 0) ? idx : 0;
			}
			else if (cmbEmployeeFilter->SelectedIndex < 0)
			{
				cmbEmployeeFilter->SelectedIndex = 0;
			}
		}

		// Reload data from DB then apply current filters and update UI
		void ReloadAll()
		{
			// Load fresh data
			InitializeRequests();

			// Preserve current employee selection if any
			String^ prevEmp = nullptr;
			if (cmbEmployeeFilter->SelectedIndex >= 0 && cmbEmployeeFilter->SelectedItem != nullptr)
				prevEmp = cmbEmployeeFilter->SelectedItem->ToString();

			// Update employee filter items (preserve selection)
			UpdateEmployeeFilterPreserve(prevEmp);

			// Ensure status combo has a valid selection
			if (cmbStatusFilter->SelectedIndex < 0)
				cmbStatusFilter->SelectedIndex = 0;

			ApplyCurrentFilters();
		}

		// Return a filtered view of _allRequests based on the current combo boxes
		List<RequestRow^>^ GetFilteredRequests()
		{
			List<RequestRow^>^ filtered = gcnew List<RequestRow^>();

			String^ statusFilter = nullptr;
			if (cmbStatusFilter != nullptr && cmbStatusFilter->SelectedItem != nullptr)
				statusFilter = cmbStatusFilter->SelectedItem->ToString();

			String^ empFilter = nullptr;
			if (cmbEmployeeFilter != nullptr && cmbEmployeeFilter->SelectedItem != nullptr)
				empFilter = cmbEmployeeFilter->SelectedItem->ToString();

			for each(RequestRow ^ r in _allRequests)
			{
				// --- Status filter ---
				if (!String::IsNullOrEmpty(statusFilter) && statusFilter != L"All")
				{
					if (!r->Status->Equals(statusFilter, StringComparison::OrdinalIgnoreCase))
						continue;
				}

				// --- Employee filter ---
				if (!String::IsNullOrEmpty(empFilter) && empFilter != L"All")
				{
					if (!r->EmployeeName->Equals(empFilter, StringComparison::OrdinalIgnoreCase))
						continue;
				}

				filtered->Add(r);
			}

			return filtered;
		}

		void ApplyCurrentFilters()
		{
			// Filter the in-memory list and show it
			List<RequestRow^>^ filtered = GetFilteredRequests();
			PopulateGrid(filtered);
			RefreshDetails();
			UpdateKpis();
		}

		bool UpdateRequestStatusInDb(int requestId, String^ newStatus)
		{
			try
			{
				String^ error = nullptr;

				bool ok = RequestManager::SetRequestStatus(
					requestId,
					newStatus,
					Session::UserId,
					error
				);

				if (!ok)
				{
					String^ msg = L"Failed to update request status.";
					if (!String::IsNullOrEmpty(error))
						msg += L"\n\n" + error;

					MessageBox::Show(msg, L"Error",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					return false;
				}

				return true;
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(L"Error updating request status:\n" + ex->Message,
					L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return false;
			}
		}

		void ApplyStatusToSelectedRows(String^ newStatus)
		{
			List<int>^ ids = GetSelectedRequestIds();

			if (ids->Count == 0)
			{
				MessageBox::Show(L"No requests selected.",
					L"Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			String^ msg = (newStatus == L"Approved")
				? L"Approve selected requests?"
				: L"Reject selected requests?";

			auto res = MessageBox::Show(msg,
				L"Confirm",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Question);

			if (res != System::Windows::Forms::DialogResult::Yes)
				return;

			// Optional: here you could prompt for a rejection reason and later extend SetRequestStatus to store it.
			for each(int id in ids)
			{
				if (!UpdateRequestStatusInDb(id, newStatus))
					break; // stop on first failure
			}

			ReloadAll();
		}

		// -------------------------- Event handlers --------------------------

	private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (_isInitializingFilters) return;
		ApplyCurrentFilters();
	}

	private: System::Void btnApprove_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ApplyStatusToSelectedRows(L"Approved");
	}

	private: System::Void btnReject_Click(System::Object^ sender, System::EventArgs^ e)
	{
		ApplyStatusToSelectedRows(L"Rejected");
	}

	private: System::Void gridRequests_CurrentCellDirtyStateChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (gridRequests->IsCurrentCellDirty)
		{
			gridRequests->CommitEdit(DataGridViewDataErrorContexts::Commit);
		}
	}

	private: System::Void gridRequests_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex >= 0)
		{
			try
			{
				gridRequests->ClearSelection();
				gridRequests->Rows[e->RowIndex]->Selected = true;
			}
			catch (...) {}
		}
		RefreshDetails();
	}

	private: System::Void gridRequests_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RefreshDetails();
	}

	private: System::Void gridRequests_CellMouseEnter(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		_hoverRowIndex = e->RowIndex;
	}

	private: System::Void gridRequests_CellMouseLeave(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		_hoverRowIndex = -1;
	}
	private: System::Void cmbEmployeeFilter_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (_isInitializingFilters) return;
		ApplyCurrentFilters();
	}
	private: System::Void cmbStatusFilter_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (_isInitializingFilters) return;
		ApplyCurrentFilters();
	}
	};
}