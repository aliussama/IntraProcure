#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace SiticoneNetFrameworkUI;

namespace IntraProcure {
	public ref class UiStyler abstract sealed
	{
	public:
		// -------------------------
		// Palette (purple theme)
		// -------------------------
		static Color Primary() { return Color::FromArgb(36, 31, 110); }      // deep purple
		static Color PrimaryDark() { return Color::FromArgb(56, 50, 140); }
		static Color Accent() { return Color::FromArgb(0, 200, 120); }
		static Color BgWindow() { return Color::FromArgb(239, 242, 250); }
		static Color BgCard() { return Color::FromArgb(255, 255, 255); }
		static Color TextMain() { return Color::FromArgb(40, 40, 40); }
		static Color TextMuted() { return Color::FromArgb(120, 120, 120); }
		static Color MutedGray() { return Color::FromArgb(193, 190, 191); }
		static Color SoftCard() { return Color::FromArgb(210, 223, 249); }

		// -------------------------
		// Base form styling
		// -------------------------
		static void StyleFormBackground(Form^ f)
		{
			if (!f) return;
			f->BackColor = BgWindow();
			f->Font = gcnew Drawing::Font(L"Segoe UI", 9.0f);
			f->ForeColor = TextMain();
		}

		// -------------------------
		// Header strip (top bar in child forms)
		// -------------------------
		static void StyleHeaderPanel(SiticoneFlatPanel^ header, Label^ title)
		{
			if (header)
			{
				header->BackColor = BgCard();
				header->Padding = Padding(15, 10, 15, 10);
			}
			if (title)
			{
				title->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 12.0f);
				title->ForeColor = TextMain();
			}
		}

		// -------------------------
		// Sidebar navigation buttons
		// -------------------------
		static void StyleNavButton(SiticoneButton^ btn)
		{
			if (!btn) return;

			btn->ButtonBackColor = Color::FromArgb(240, 244, 248);
			btn->HoverBackColor = Color::FromArgb(230, 238, 245);
			btn->PressedBackColor = PrimaryDark();
			btn->TextColor = Color::FromArgb(60, 60, 60);
			btn->CornerRadiusTopLeft = 6;
			btn->CornerRadiusTopRight = 6;
			btn->CornerRadiusBottomLeft = 6;
			btn->CornerRadiusBottomRight = 6;
			btn->TextAlign = ContentAlignment::MiddleLeft;
		}

		// -------------------------
		// Primary filled button (Submit, Add, Approve…)
		// -------------------------
		static void StylePrimaryButton(SiticoneButton^ btn)
		{
			if (!btn) return;

			btn->ButtonBackColor = Primary();
			btn->HoverBackColor = PrimaryDark();
			btn->PressedBackColor = Color::FromArgb(26, 22, 100);
			btn->TextColor = Color::White;

			btn->CornerRadiusTopLeft = 8;
			btn->CornerRadiusTopRight = 8;
			btn->CornerRadiusBottomLeft = 8;
			btn->CornerRadiusBottomRight = 8;
		}

		// -------------------------
		// Secondary outlined / neutral button (Cancel, Clear…)
		// -------------------------
		static void StyleSecondaryButton(SiticoneButton^ btn)
		{
			if (!btn) return;

			btn->ButtonBackColor = Color::FromArgb(240, 240, 240);
			btn->HoverBackColor = Color::FromArgb(230, 230, 230);
			btn->PressedBackColor = Color::FromArgb(210, 210, 210);
			btn->TextColor = TextMain();

			btn->CornerRadiusTopLeft = 8;
			btn->CornerRadiusTopRight = 8;
			btn->CornerRadiusBottomLeft = 8;
			btn->CornerRadiusBottomRight = 8;
		}

		// -------------------------
		// NEUTRAL BUTTON (Refresh / small toolbar)
		// -------------------------
		static void StyleButton(SiticoneButton^ btn)
		{
			if (!btn) return;

			btn->ButtonBackColor = MutedGray();
			btn->HoverBackColor = Color::FromArgb(210, 208, 214);
			btn->PressedBackColor = Color::FromArgb(195, 192, 198);
			btn->TextColor = Color::Black;

			btn->CornerRadiusTopLeft = 8;
			btn->CornerRadiusTopRight = 8;
			btn->CornerRadiusBottomLeft = 8;
			btn->CornerRadiusBottomRight = 8;

			// subtle border for neutral buttons
			try { btn->BorderColor = Color::FromArgb(180, 180, 180); }
			catch (...) {}
		}

		// -------------------------
		// DANGER BUTTON  (Red Delete Button)
		// -------------------------
		static void StyleDangerButton(SiticoneButton^ btn)
		{
			if (!btn) return;

			btn->ButtonBackColor = Color::FromArgb(220, 53, 69); // red
			btn->HoverBackColor = Color::FromArgb(200, 30, 50);
			btn->PressedBackColor = Color::FromArgb(180, 20, 40);
			btn->TextColor = Color::White;

			btn->CornerRadiusTopLeft = 8;
			btn->CornerRadiusTopRight = 8;
			btn->CornerRadiusBottomLeft = 8;
			btn->CornerRadiusBottomRight = 8;
		}

		// -------------------------
		// Siticone text box
		// -------------------------
		static void StyleTextBox(SiticoneTextBox^ txt)
		{
			if (!txt) return;

			txt->FillColor1 = Color::White;
			txt->FillColor2 = Color::White;
			txt->BorderColor1 = Color::LightGray;
			txt->BorderColor2 = Color::LightGray;
			txt->BorderFocusColor1 = Primary();
			txt->BorderFocusColor2 = Primary();

			txt->CornerRadiusTopLeft = 8;
			txt->CornerRadiusTopRight = 8;
			txt->CornerRadiusBottomLeft = 8;
			txt->CornerRadiusBottomRight = 8;

			txt->TextPadding = Padding(12, 0, 8, 0);
		}

		// -------------------------
		// Product cards container
		// -------------------------
		static void StyleFlowPanel(SiticoneFlowPanel^ fp)
		{
			if (!fp) return;

			fp->BackColor = BgWindow();
			fp->AutoScroll = true;
			fp->Padding = Padding(10);
			fp->ItemSpacing = 6;
			fp->EnableAnimations = true;
			fp->EnableSmoothScrolling = true;
		}

		// -------------------------
		// DataGridView styling (Manager, MyRequests, Cart…)
		// -------------------------
		static void StyleGrid(DataGridView^ grid)
		{
			if (grid == nullptr) return;

			// ----- BASIC LAYOUT -----
			grid->BorderStyle = BorderStyle::None;
			grid->BackgroundColor = BgWindow();      // light page bg
			grid->RowHeadersVisible = false;
			grid->AllowUserToAddRows = false;
			grid->AllowUserToDeleteRows = false;
			grid->AllowUserToResizeRows = false;
			grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			grid->MultiSelect = false;
			grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			grid->GridColor = SoftCard();            // very light line
			grid->RowTemplate->Height = 36;

			// ----- COLUMN HEADER STYLE -----
			grid->EnableHeadersVisualStyles = false;
			grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
			grid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			grid->ColumnHeadersHeight = 40;

			DataGridViewCellStyle^ headerStyle = gcnew DataGridViewCellStyle();
			headerStyle->BackColor = BgWindow();
			headerStyle->ForeColor = Primary();
			headerStyle->Font = gcnew Drawing::Font(L"Segoe UI Semibold", 9, FontStyle::Bold);
			headerStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
			headerStyle->Padding = System::Windows::Forms::Padding(8, 0, 8, 0);
			headerStyle->SelectionBackColor = headerStyle->BackColor;
			headerStyle->SelectionForeColor = headerStyle->ForeColor;
			headerStyle->WrapMode = DataGridViewTriState::False;

			grid->ColumnHeadersDefaultCellStyle = headerStyle;

			// ----- NORMAL ROW STYLE -----
			DataGridViewCellStyle^ cellStyle = gcnew DataGridViewCellStyle();
			cellStyle->BackColor = Color::White;
			cellStyle->ForeColor = Color::FromArgb(0, 0, 0);
			cellStyle->Font = gcnew Drawing::Font(L"Segoe UI", 9, FontStyle::Regular);
			cellStyle->SelectionBackColor = SoftCard();      // light purple highlight
			cellStyle->SelectionForeColor = Primary();        // dark text on selection
			cellStyle->Padding = System::Windows::Forms::Padding(8, 0, 8, 0);

			grid->DefaultCellStyle = cellStyle;

			// ----- ALTERNATING ROWS (subtle banding) -----
			DataGridViewCellStyle^ altStyle = gcnew DataGridViewCellStyle(cellStyle);
			altStyle->BackColor = Color::FromArgb(248, 249, 255);                // very light tint
			altStyle->SelectionBackColor = cellStyle->SelectionBackColor;
			altStyle->SelectionForeColor = cellStyle->SelectionForeColor;

			grid->AlternatingRowsDefaultCellStyle = altStyle;

			// ----- COLUMN / ROW BEHAVIOUR -----
			grid->ColumnHeadersDefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
			grid->ColumnHeadersDefaultCellStyle->Padding = System::Windows::Forms::Padding(12, 0, 8, 0);

			grid->RowsDefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;

			// allow user to toggle checkboxes with mouse
			grid->EditMode = DataGridViewEditMode::EditOnEnter;
		}
	};
}
