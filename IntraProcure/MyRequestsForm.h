#pragma once

#include "UiStyler.h"
#include "DatabaseManager.h"
#include "Session.h"

namespace IntraProcure {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Data::SqlClient;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyRequestsForm - employee view of their own requests.
	/// Left: requests list (DataGridView). Right: details + actions.
	/// </summary>
	public ref class MyRequestsForm : public System::Windows::Forms::Form
	{
	public:
		MyRequestsForm(void)
		{
			InitializeComponent();
			// sample data for now (replace with DB fetch)
			InitializeRequests();
			UiStyler::StyleGrid(gridRequests);
			UiStyler::StylePrimaryButton(btnReopenRequest);
			UiStyler::StyleSecondaryButton(btnCancelRequest);
			UiStyler::StyleButton(btnRefresh);
			UiStyler::StyleTextBox(txtSearch);
			SetupGrid();
			ApplyFilters();
		}

	protected:
		~MyRequestsForm()
		{
			if (components)
				delete components;
		}
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnCancelRequest;
	protected:

	private: SiticoneNetFrameworkUI::SiticoneButton^ btnReopenRequest;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnRefresh;
	private: SiticoneNetFrameworkUI::SiticonePanel^ siticonePanel1;

	protected:

	private:
		// -------------------- Data model (local sample) --------------------
		ref struct ReqRow {
			int Id;
			String^ Date;
			String^ Department;
			double Total;
			String^ Status;
			String^ Summary;
		};

		List<ReqRow^>^ _allRequests;

		void InitializeRequests()
		{
			_allRequests = gcnew List<ReqRow^>();

			SqlConnection^ conn = nullptr;

			try
			{
				conn = DatabaseManager::CreateConnection();
				conn->Open();

				String^ sql =
					"SELECT Id, CreatedAt, Department, Total, Status "
					"FROM procure.Requests "
					"WHERE EmployeeId = @EmployeeId "
					"ORDER BY CreatedAt DESC;";

				SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
				cmd->Parameters->AddWithValue("@EmployeeId", Session::UserId);

				SqlDataReader^ r = cmd->ExecuteReader();
				while (r->Read())
				{
					ReqRow^ row = gcnew ReqRow();

					row->Id = r->GetInt32(0);

					DateTime created = r->GetDateTime(1);
					row->Date = created.ToString("yyyy-MM-dd");

					row->Department = r->IsDBNull(2) ? L"" : r->GetString(2);

					// Total is DECIMAL(18,2) in DB
					row->Total = r->IsDBNull(3)
						? 0.0
						: (double)r->GetDecimal(3);

					row->Status = r->IsDBNull(4) ? L"" : r->GetString(4);

					// Simple human-readable summary used for search/details
					row->Summary = String::Format(
						"Request #{0} – {1} – {2:N2} EGP",
						row->Id, row->Department, row->Total
					);

					_allRequests->Add(row);
				}

				r->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(
					L"Failed to load your requests from the database:\n" + ex->Message,
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

		// -------------------- Filtering / Binding --------------------------
		void ApplyFilters()
		{
			String^ search = txtSearch->Text->Trim()->ToLower();
			String^ status = cmbStatus->SelectedIndex >= 0 ? cmbStatus->SelectedItem->ToString() : L"All";

			gridRequests->Rows->Clear();

			for each(ReqRow ^ r in _allRequests)
			{
				bool matchStatus = (status == L"All" || r->Status == status);
				bool matchSearch = (search->Length == 0 || r->Summary->ToLower()->Contains(search) || r->Id.ToString()->Contains(search));

				if (!matchStatus || !matchSearch) continue;

				int idx = gridRequests->Rows->Add();
				DataGridViewRow^ row = gridRequests->Rows[idx];
				row->Cells[L"colSelect"]->Value = false;
				row->Cells[L"colId"]->Value = r->Id;
				row->Cells[L"colDate"]->Value = r->Date;
				row->Cells[L"colDept"]->Value = r->Department;
				row->Cells[L"colSummary"]->Value = r->Summary;
				row->Cells[L"colTotal"]->Value = r->Total.ToString("N2") + " EGP";
				row->Cells[L"colStatus"]->Value = r->Status;
			}

			// Select first row if present
			if (gridRequests->Rows->Count > 0)
				gridRequests->Rows[0]->Selected = true;
			else
				ShowDetails(nullptr);
		}

		// -------------------- Grid styling -------------------------------
		void SetupGrid()
		{
			gridRequests->Columns->Clear();
			gridRequests->AutoGenerateColumns = false;
			gridRequests->ReadOnly = false;              // we want the check column editable
			gridRequests->SelectionMode =
				DataGridViewSelectionMode::FullRowSelect;

			// checkbox column
			DataGridViewCheckBoxColumn^ colSelect = gcnew DataGridViewCheckBoxColumn();
			colSelect->Name = L"colSelect";
			colSelect->HeaderText = L"";
			colSelect->Width = 36;
			colSelect->FillWeight = 36;
			colSelect->TrueValue = true;
			colSelect->FalseValue = false;
			colSelect->ThreeState = false;
			colSelect->ValueType = bool::typeid;
			colSelect->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			colSelect->ReadOnly = false;
			gridRequests->Columns->Add(colSelect);

			DataGridViewTextBoxColumn^ colId = gcnew DataGridViewTextBoxColumn();
			colId->Name = L"colId";
			colId->HeaderText = L"ID";
			colId->FillWeight = 60;
			colId->ReadOnly = true;
			gridRequests->Columns->Add(colId);

			DataGridViewTextBoxColumn^ colDate = gcnew DataGridViewTextBoxColumn();
			colDate->Name = L"colDate";
			colDate->HeaderText = L"Date";
			colDate->FillWeight = 110;
			colDate->ReadOnly = true;
			gridRequests->Columns->Add(colDate);

			DataGridViewTextBoxColumn^ colDept = gcnew DataGridViewTextBoxColumn();
			colDept->Name = L"colDept";
			colDept->HeaderText = L"Department";
			colDept->FillWeight = 120;
			colDept->ReadOnly = true;
			gridRequests->Columns->Add(colDept);

			DataGridViewTextBoxColumn^ colSummary = gcnew DataGridViewTextBoxColumn();
			colSummary->Name = L"colSummary";
			colSummary->HeaderText = L"Summary";
			colSummary->FillWeight = 250;
			colSummary->ReadOnly = true;
			gridRequests->Columns->Add(colSummary);

			DataGridViewTextBoxColumn^ colTotal = gcnew DataGridViewTextBoxColumn();
			colTotal->Name = L"colTotal";
			colTotal->HeaderText = L"Total";
			colTotal->FillWeight = 90;
			colTotal->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
			colTotal->ReadOnly = true;
			gridRequests->Columns->Add(colTotal);

			DataGridViewTextBoxColumn^ colStatus = gcnew DataGridViewTextBoxColumn();
			colStatus->Name = L"colStatus";
			colStatus->HeaderText = L"Status";
			colStatus->FillWeight = 100;
			colStatus->ReadOnly = true;
			gridRequests->Columns->Add(colStatus);

			// neat visual tweak: row height
			gridRequests->RowTemplate->Height = 36;
		}

		// -------------------- Details view --------------------------------
		void ShowDetails(DataGridViewRow^ row)
		{
			if (row == nullptr)
			{
				lblDetailsTitle->Text = L"No request selected";
				txtDetails->Text = L"Select a request from the list to view details, add comments, or cancel.";
				btnCancelRequest->Enabled = false;
				btnReopenRequest->Enabled = false;
				return;
			}

			Object^ idVal = row->Cells[L"colId"]->Value;
			Object^ dateVal = row->Cells[L"colDate"]->Value;
			Object^ deptVal = row->Cells[L"colDept"]->Value;
			Object^ summVal = row->Cells[L"colSummary"]->Value;
			Object^ totalVal = row->Cells[L"colTotal"]->Value;
			Object^ statusVal = row->Cells[L"colStatus"]->Value;

			lblDetailsTitle->Text = String::Format(L"Request #{0} — {1}", idVal, statusVal);
			txtDetails->Text = String::Format(L"Date: {0}\r\nDepartment: {1}\r\nTotal: {2}\r\n\r\nSummary:\r\n{3}",
				dateVal, deptVal, totalVal, summVal);

			String^ status = statusVal != nullptr ? statusVal->ToString() : L"";
			btnCancelRequest->Enabled = (status == L"Pending");
			btnReopenRequest->Enabled = (status == L"Rejected");
		}

		ReqRow^ GetSelectedRequest()
		{
			if (gridRequests->SelectedRows->Count == 0)
				return nullptr;

			DataGridViewRow^ row = gridRequests->SelectedRows[0];
			if (row->Cells[L"colId"]->Value == nullptr)
				return nullptr;

			int id = safe_cast<int>(row->Cells[L"colId"]->Value);

			for each(ReqRow ^ r in _allRequests)
			{
				if (r->Id == id)
					return r;
			}
			return nullptr;
		}

		// Return list of request IDs that are checked in the "colSelect" checkbox column.
// If none are checked but a row is selected, we fall back to the selected row.
		System::Collections::Generic::List<int>^ GetCheckedRequestIds()
		{
			auto ids = gcnew System::Collections::Generic::List<int>();

			try
			{
				for each(DataGridViewRow ^ row in gridRequests->Rows)
				{
					if (row == nullptr) continue;

					DataGridViewCell^ selCell = row->Cells[L"colSelect"];
					if (selCell == nullptr) continue;

					bool isChecked = false;
					try
					{
						if (selCell->Value != nullptr)
							isChecked = System::Convert::ToBoolean(selCell->Value);
					}
					catch (...) { isChecked = false; }

					if (!isChecked) continue;

					DataGridViewCell^ idCell = row->Cells[L"colId"];
					if (idCell == nullptr || idCell->Value == nullptr) continue;

					int id = 0;
					try { id = System::Convert::ToInt32(idCell->Value); }
					catch (...) { continue; }

					ids->Add(id);
				}

				// Fallback: if nothing is checked, use the currently selected row (if any)
				if (ids->Count == 0 && gridRequests->SelectedRows->Count > 0)
				{
					DataGridViewRow^ sel = gridRequests->SelectedRows[0];
					if (sel != nullptr && sel->Cells[L"colId"] != nullptr)
					{
						DataGridViewCell^ idCell = sel->Cells[L"colId"];
						if (idCell != nullptr && idCell->Value != nullptr)
						{
							try
							{
								int id = System::Convert::ToInt32(idCell->Value);
								ids->Add(id);
							}
							catch (...) {}
						}
					}
				}
			}
			catch (...)
			{
				// swallow: we just return what we managed to collect
			}

			return ids;
		}

		// Update the in-memory sample list (_allRequests) and refresh UI
		void UpdateStatusForRequests(System::Collections::Generic::List<int>^ ids, System::String^ newStatus)
		{
			if (ids == nullptr || ids->Count == 0) return;

			try
			{
				for each(int id in ids)
				{
					for each(ReqRow ^ r in _allRequests)
					{
						if (r != nullptr && r->Id == id)
						{
							r->Status = newStatus;
							break;
						}
					}
				}

				// Rebuild the grid from _allRequests with filters
				ApplyFilters();

				// Try to re-select one of the affected requests and show its details
				for each(DataGridViewRow ^ row in gridRequests->Rows)
				{
					if (row == nullptr) continue;

					DataGridViewCell^ idCell = row->Cells[L"colId"];
					if (idCell == nullptr || idCell->Value == nullptr) continue;

					int id = 0;
					try { id = System::Convert::ToInt32(idCell->Value); }
					catch (...) { continue; }

					if (ids->Contains(id))
					{
						row->Selected = true;
						ShowDetails(row);
						break;
					}
				}
			}
			catch (System::Exception^ ex)
			{
				System::Windows::Forms::MessageBox::Show(
					L"Error updating request statuses:\n" + ex->Message,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
		}

		void DeleteFromRequestsInDb(System::Collections::Generic::List<int>^ ids)
		{
			if (ids == nullptr || ids->Count == 0) return;
			SqlConnection^ conn = nullptr;
			try
			{
				conn = DatabaseManager::CreateConnection();
				conn->Open();
				for each(int id in ids)
				{
					String^ sql = "DELETE FROM procure.Requests WHERE Id = @Id;";
					SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
					cmd->Parameters->AddWithValue("@Id", id);
					cmd->ExecuteNonQuery();
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(
					L"Error deleting requests from database:\n" + ex->Message,
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

		// -------------------- Event handlers --------------------------------
		System::Void txtSearch_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			ApplyFilters();
		}

		System::Void cmbStatus_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			ApplyFilters();
		}

		System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
		{
			InitializeRequests();   // reload from DB
			ApplyFilters();         // rebind grid with fresh data
		}

		// ensure checkbox changes commit immediately
		System::Void gridRequests_CurrentCellDirtyStateChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (gridRequests->IsCurrentCellDirty)
				gridRequests->CommitEdit(DataGridViewDataErrorContexts::Commit);
		}

		System::Void gridRequests_CellContentClick(System::Object^ sender, DataGridViewCellEventArgs^ e)
		{
			if (e->RowIndex < 0) return;
			// no extra logic needed here; the helper reads values from cells
		}

		System::Void gridRequests_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (gridRequests->SelectedRows->Count == 0)
			{
				ShowDetails(nullptr);
				return;
			}
			ShowDetails(gridRequests->SelectedRows[0]);
		}

		System::Void btnCancelRequest_Click(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				auto ids = GetCheckedRequestIds();

				if (ids == nullptr || ids->Count == 0)
				{
					MessageBox::Show(
						L"Please check at least one request in the list.",
						L"Cancel Requests",
						MessageBoxButtons::OK,
						MessageBoxIcon::Information);
					return;
				}

				System::String^ msg;
				if (ids->Count == 1)
					msg = L"Are you sure you want to cancel this request?";
				else
					msg = L"Are you sure you want to cancel the selected " + ids->Count.ToString() + L" requests?";

				auto confirm = MessageBox::Show(
					msg,
					L"Cancel Requests",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question);

				if (confirm != System::Windows::Forms::DialogResult::Yes)
					return;

				// Update sample data to "Cancelled" and refresh grid
				UpdateStatusForRequests(ids, L"Cancelled");
				DeleteFromRequestsInDb(ids);

				MessageBox::Show(
					L"Selected request(s) have been marked as Cancelled.",
					L"Cancel Requests",
					MessageBoxButtons::OK,
					MessageBoxIcon::Information);
			}
			catch (System::Exception^ ex)
			{
				MessageBox::Show(
					L"Unexpected error while cancelling requests:\n" + ex->Message,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
		}

		System::Void btnReopenRequest_Click(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				auto ids = GetCheckedRequestIds();

				if (ids == nullptr || ids->Count == 0)
				{
					MessageBox::Show(
						L"Please check at least one request in the list.",
						L"Reopen Requests",
						MessageBoxButtons::OK,
						MessageBoxIcon::Information);
					return;
				}

				System::String^ msg;
				if (ids->Count == 1)
					msg = L"Reopen this request and set its status to Pending?";
				else
					msg = L"Reopen the selected " + ids->Count.ToString() + L" requests and set them to Pending?";

				auto confirm = MessageBox::Show(
					msg,
					L"Reopen Requests",
					MessageBoxButtons::YesNo,
					MessageBoxIcon::Question);

				if (confirm != System::Windows::Forms::DialogResult::Yes)
					return;

				// Update sample data to "Pending" and refresh grid
				UpdateStatusForRequests(ids, L"Pending");

				MessageBox::Show(
					L"Selected request(s) have been reopened and set to Pending.",
					L"Reopen Requests",
					MessageBoxButtons::OK,
					MessageBoxIcon::Information);
			}
			catch (System::Exception^ ex)
			{
				MessageBox::Show(
					L"Unexpected error while reopening requests:\n" + ex->Message,
					L"Error",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
		}

	private:
		System::ComponentModel::Container^ components;

		// UI controls
		Panel^ headerPanel;
		Label^ lblHeader;
		SiticoneNetFrameworkUI::SiticoneTextBox^ txtSearch;
		ComboBox^ cmbStatus;

		SplitContainer^ splitMain;
		DataGridView^ gridRequests;
		Panel^ detailsPanel;
		Label^ lblDetailsTitle;
		TextBox^ txtDetails;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->headerPanel = (gcnew System::Windows::Forms::Panel());
			this->btnRefresh = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->lblHeader = (gcnew System::Windows::Forms::Label());
			this->txtSearch = (gcnew SiticoneNetFrameworkUI::SiticoneTextBox());
			this->cmbStatus = (gcnew System::Windows::Forms::ComboBox());
			this->splitMain = (gcnew System::Windows::Forms::SplitContainer());
			this->gridRequests = (gcnew System::Windows::Forms::DataGridView());
			this->detailsPanel = (gcnew System::Windows::Forms::Panel());
			this->lblDetailsTitle = (gcnew System::Windows::Forms::Label());
			this->txtDetails = (gcnew System::Windows::Forms::TextBox());
			this->btnCancelRequest = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->btnReopenRequest = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->siticonePanel1 = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->headerPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->BeginInit();
			this->splitMain->Panel1->SuspendLayout();
			this->splitMain->Panel2->SuspendLayout();
			this->splitMain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridRequests))->BeginInit();
			this->detailsPanel->SuspendLayout();
			this->siticonePanel1->SuspendLayout();
			this->SuspendLayout();
			//
			// headerPanel
			//
			this->headerPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->headerPanel->Controls->Add(this->btnRefresh);
			this->headerPanel->Controls->Add(this->lblHeader);
			this->headerPanel->Controls->Add(this->txtSearch);
			this->headerPanel->Controls->Add(this->cmbStatus);
			this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->headerPanel->Location = System::Drawing::Point(0, 0);
			this->headerPanel->Name = L"headerPanel";
			this->headerPanel->Padding = System::Windows::Forms::Padding(12);
			this->headerPanel->Size = System::Drawing::Size(916, 64);
			this->headerPanel->TabIndex = 5;
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
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9));
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
			this->btnRefresh->Location = System::Drawing::Point(660, 16);
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
			this->btnRefresh->Size = System::Drawing::Size(88, 28);
			this->btnRefresh->TabIndex = 15;
			this->btnRefresh->Text = L"Refresh";
			this->btnRefresh->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnRefresh->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnRefresh->TooltipText = nullptr;
			this->btnRefresh->UseAdvancedRendering = true;
			this->btnRefresh->UseParticles = false;
			this->btnRefresh->Click += gcnew EventHandler(this, &MyRequestsForm::btnRefresh_Click);
			//
			// lblHeader
			//
			this->lblHeader->AutoSize = true;
			this->lblHeader->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
			this->lblHeader->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblHeader->Location = System::Drawing::Point(12, 16);
			this->lblHeader->Name = L"lblHeader";
			this->lblHeader->Size = System::Drawing::Size(124, 25);
			this->lblHeader->TabIndex = 0;
			this->lblHeader->Text = L"My Requests";
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
			this->txtSearch->CornerRadiusBottomLeft = 5;
			this->txtSearch->CornerRadiusBottomRight = 5;
			this->txtSearch->CornerRadiusTopLeft = 5;
			this->txtSearch->CornerRadiusTopRight = 5;
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
			this->txtSearch->Location = System::Drawing::Point(180, 16);
			this->txtSearch->Name = L"txtSearch";
			this->txtSearch->PlaceholderColor = System::Drawing::Color::Gray;
			this->txtSearch->PlaceholderText = L"Search requests...";
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
			this->txtSearch->Size = System::Drawing::Size(300, 28);
			this->txtSearch->SolidBorderColor = System::Drawing::Color::LightSlateGray;
			this->txtSearch->SolidBorderFocusColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->txtSearch->SolidBorderHoverColor = System::Drawing::Color::Gray;
			this->txtSearch->SolidFillColor = System::Drawing::Color::White;
			this->txtSearch->TabIndex = 0;
			this->txtSearch->TextPadding = System::Windows::Forms::Padding(16, 0, 6, 0);
			this->txtSearch->ValidationErrorMessage = L"Invalid input.";
			this->txtSearch->ValidationFunction = nullptr;
			this->txtSearch->TextChanged += gcnew EventHandler(this, &MyRequestsForm::txtSearch_TextChanged);
			//
			// cmbStatus
			//
			this->cmbStatus->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbStatus->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cmbStatus->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->cmbStatus->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"All", L"Pending", L"Approved", L"Rejected", L"Cancelled" });
			this->cmbStatus->Location = System::Drawing::Point(500, 16);
			this->cmbStatus->Name = L"cmbStatus";
			this->cmbStatus->Size = System::Drawing::Size(140, 23);
			this->cmbStatus->TabIndex = 1;
			this->cmbStatus->SelectedIndex = 0;
			this->cmbStatus->SelectedIndexChanged += gcnew EventHandler(this, &MyRequestsForm::cmbStatus_SelectedIndexChanged);
			//
			// splitMain
			//
			this->splitMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitMain->Location = System::Drawing::Point(2, 2);
			this->splitMain->Name = L"splitMain";
			//
			// splitMain.Panel1
			//
			this->splitMain->Panel1->Controls->Add(this->gridRequests);
			//
			// splitMain.Panel2
			//
			this->splitMain->Panel2->Controls->Add(this->detailsPanel);
			this->splitMain->Size = System::Drawing::Size(911, 475);
			this->splitMain->SplitterDistance = 556;
			this->splitMain->TabIndex = 3;
			//
			// gridRequests
			//
			this->gridRequests->AllowUserToAddRows = false;
			this->gridRequests->AllowUserToDeleteRows = false;
			this->gridRequests->AllowUserToResizeRows = false;
			this->gridRequests->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->gridRequests->BackgroundColor = System::Drawing::Color::White;
			this->gridRequests->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->gridRequests->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
			this->gridRequests->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gridRequests->GridColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(249)));
			this->gridRequests->Location = System::Drawing::Point(0, 0);
			this->gridRequests->Name = L"gridRequests";
			this->gridRequests->ReadOnly = true;
			this->gridRequests->RowHeadersVisible = false;
			this->gridRequests->RowTemplate->Height = 36;
			this->gridRequests->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->gridRequests->Size = System::Drawing::Size(556, 475);
			this->gridRequests->TabIndex = 0;
			this->gridRequests->SelectionChanged += gcnew EventHandler(this, &MyRequestsForm::gridRequests_SelectionChanged);
			this->gridRequests->CurrentCellDirtyStateChanged += gcnew EventHandler(this, &MyRequestsForm::gridRequests_CurrentCellDirtyStateChanged);
			this->gridRequests->CellContentClick += gcnew DataGridViewCellEventHandler(this, &MyRequestsForm::gridRequests_CellContentClick);
			//
			// detailsPanel
			//
			this->detailsPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->detailsPanel->Controls->Add(this->lblDetailsTitle);
			this->detailsPanel->Controls->Add(this->txtDetails);
			this->detailsPanel->Controls->Add(this->btnCancelRequest);
			this->detailsPanel->Controls->Add(this->btnReopenRequest);
			this->detailsPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->detailsPanel->Location = System::Drawing::Point(0, 0);
			this->detailsPanel->Name = L"detailsPanel";
			this->detailsPanel->Padding = System::Windows::Forms::Padding(12);
			this->detailsPanel->Size = System::Drawing::Size(351, 475);
			this->detailsPanel->TabIndex = 0;
			//
			// lblDetailsTitle
			//
			this->lblDetailsTitle->AutoSize = true;
			this->lblDetailsTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			this->lblDetailsTitle->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblDetailsTitle->Location = System::Drawing::Point(12, 12);
			this->lblDetailsTitle->Name = L"lblDetailsTitle";
			this->lblDetailsTitle->Size = System::Drawing::Size(142, 19);
			this->lblDetailsTitle->TabIndex = 0;
			this->lblDetailsTitle->Text = L"No request selected";
			//
			// txtDetails
			//
			this->txtDetails->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtDetails->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->txtDetails->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtDetails->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			this->txtDetails->ForeColor = System::Drawing::Color::Black;
			this->txtDetails->Location = System::Drawing::Point(12, 44);
			this->txtDetails->Multiline = true;
			this->txtDetails->Name = L"txtDetails";
			this->txtDetails->ReadOnly = true;
			this->txtDetails->Size = System::Drawing::Size(299, 332);
			this->txtDetails->TabIndex = 1;
			//
			// btnCancelRequest
			//
			this->btnCancelRequest->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnCancelRequest->AccessibleName = L"Cancel request";
			this->btnCancelRequest->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnCancelRequest->AutoSizeBasedOnText = false;
			this->btnCancelRequest->BackColor = System::Drawing::Color::Transparent;
			this->btnCancelRequest->BadgeBackColor = System::Drawing::Color::Black;
			this->btnCancelRequest->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnCancelRequest->BadgeValue = 0;
			this->btnCancelRequest->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnCancelRequest->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnCancelRequest->BorderWidth = 1;
			this->btnCancelRequest->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->btnCancelRequest->ButtonImage = nullptr;
			this->btnCancelRequest->ButtonTextLeftPadding = 0;
			this->btnCancelRequest->CanBeep = true;
			this->btnCancelRequest->CanGlow = false;
			this->btnCancelRequest->CanShake = true;
			this->btnCancelRequest->ContextMenuStripEx = nullptr;
			this->btnCancelRequest->CornerRadiusBottomLeft = 6;
			this->btnCancelRequest->CornerRadiusBottomRight = 6;
			this->btnCancelRequest->CornerRadiusTopLeft = 6;
			this->btnCancelRequest->CornerRadiusTopRight = 6;
			this->btnCancelRequest->CustomCursor = System::Windows::Forms::Cursors::Default;
			this->btnCancelRequest->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnCancelRequest->EnableLongPress = false;
			this->btnCancelRequest->EnableRippleEffect = true;
			this->btnCancelRequest->EnableShadow = false;
			this->btnCancelRequest->EnableTextWrapping = false;
			this->btnCancelRequest->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(178)));
			this->btnCancelRequest->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnCancelRequest->GlowIntensity = 100;
			this->btnCancelRequest->GlowRadius = 20;
			this->btnCancelRequest->GradientBackground = false;
			this->btnCancelRequest->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnCancelRequest->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnCancelRequest->HintText = nullptr;
			this->btnCancelRequest->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnCancelRequest->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancelRequest->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancelRequest->HoverTransitionDuration = 250;
			this->btnCancelRequest->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnCancelRequest->ImagePadding = 5;
			this->btnCancelRequest->ImageSize = System::Drawing::Size(16, 16);
			this->btnCancelRequest->IsRadial = false;
			this->btnCancelRequest->IsReadOnly = false;
			this->btnCancelRequest->IsToggleButton = false;
			this->btnCancelRequest->IsToggled = false;
			this->btnCancelRequest->Location = System::Drawing::Point(104, 396);
			this->btnCancelRequest->LongPressDurationMS = 1000;
			this->btnCancelRequest->Name = L"btnCancelRequest";
			this->btnCancelRequest->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancelRequest->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnCancelRequest->ParticleCount = 15;
			this->btnCancelRequest->PressAnimationScale = 0.97F;
			this->btnCancelRequest->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnCancelRequest->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnCancelRequest->PressTransitionDuration = 150;
			this->btnCancelRequest->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnCancelRequest->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancelRequest->RippleRadiusMultiplier = 0.6F;
			this->btnCancelRequest->ShadowBlur = 5;
			this->btnCancelRequest->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancelRequest->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnCancelRequest->ShakeDuration = 500;
			this->btnCancelRequest->ShakeIntensity = 5;
			this->btnCancelRequest->Size = System::Drawing::Size(120, 40);
			this->btnCancelRequest->TabIndex = 6;
			this->btnCancelRequest->Text = L"Cancel request";
			this->btnCancelRequest->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnCancelRequest->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnCancelRequest->TooltipText = nullptr;
			this->btnCancelRequest->UseAdvancedRendering = true;
			this->btnCancelRequest->UseParticles = false;
			this->btnCancelRequest->Click += gcnew System::EventHandler(this, &MyRequestsForm::btnCancelRequest_Click);
			//
			// btnReopenRequest
			//
			this->btnReopenRequest->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnReopenRequest->AccessibleName = L"Reopen";
			this->btnReopenRequest->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnReopenRequest->AutoSizeBasedOnText = false;
			this->btnReopenRequest->BackColor = System::Drawing::Color::Transparent;
			this->btnReopenRequest->BadgeBackColor = System::Drawing::Color::Black;
			this->btnReopenRequest->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnReopenRequest->BadgeValue = 0;
			this->btnReopenRequest->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnReopenRequest->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)),
				static_cast<System::Int32>(static_cast<System::Byte>(216)), static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnReopenRequest->BorderWidth = 1;
			this->btnReopenRequest->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->btnReopenRequest->ButtonImage = nullptr;
			this->btnReopenRequest->ButtonTextLeftPadding = 0;
			this->btnReopenRequest->CanBeep = true;
			this->btnReopenRequest->CanGlow = false;
			this->btnReopenRequest->CanShake = true;
			this->btnReopenRequest->ContextMenuStripEx = nullptr;
			this->btnReopenRequest->CornerRadiusBottomLeft = 6;
			this->btnReopenRequest->CornerRadiusBottomRight = 6;
			this->btnReopenRequest->CornerRadiusTopLeft = 6;
			this->btnReopenRequest->CornerRadiusTopRight = 6;
			this->btnReopenRequest->CustomCursor = System::Windows::Forms::Cursors::Default;
			this->btnReopenRequest->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnReopenRequest->EnableLongPress = false;
			this->btnReopenRequest->EnableRippleEffect = true;
			this->btnReopenRequest->EnableShadow = false;
			this->btnReopenRequest->EnableTextWrapping = false;
			this->btnReopenRequest->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9));
			this->btnReopenRequest->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnReopenRequest->GlowIntensity = 100;
			this->btnReopenRequest->GlowRadius = 20;
			this->btnReopenRequest->GradientBackground = false;
			this->btnReopenRequest->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnReopenRequest->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnReopenRequest->HintText = nullptr;
			this->btnReopenRequest->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnReopenRequest->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReopenRequest->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReopenRequest->HoverTransitionDuration = 250;
			this->btnReopenRequest->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnReopenRequest->ImagePadding = 5;
			this->btnReopenRequest->ImageSize = System::Drawing::Size(16, 16);
			this->btnReopenRequest->IsRadial = false;
			this->btnReopenRequest->IsReadOnly = false;
			this->btnReopenRequest->IsToggleButton = false;
			this->btnReopenRequest->IsToggled = false;
			this->btnReopenRequest->Location = System::Drawing::Point(234, 396);
			this->btnReopenRequest->LongPressDurationMS = 1000;
			this->btnReopenRequest->Name = L"btnReopenRequest";
			this->btnReopenRequest->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReopenRequest->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnReopenRequest->ParticleCount = 15;
			this->btnReopenRequest->PressAnimationScale = 0.97F;
			this->btnReopenRequest->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnReopenRequest->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnReopenRequest->PressTransitionDuration = 150;
			this->btnReopenRequest->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnReopenRequest->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReopenRequest->RippleRadiusMultiplier = 0.6F;
			this->btnReopenRequest->ShadowBlur = 5;
			this->btnReopenRequest->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReopenRequest->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnReopenRequest->ShakeDuration = 500;
			this->btnReopenRequest->ShakeIntensity = 5;
			this->btnReopenRequest->Size = System::Drawing::Size(90, 40);
			this->btnReopenRequest->TabIndex = 14;
			this->btnReopenRequest->Text = L"Reopen";
			this->btnReopenRequest->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnReopenRequest->TextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnReopenRequest->TooltipText = nullptr;
			this->btnReopenRequest->UseAdvancedRendering = true;
			this->btnReopenRequest->UseParticles = false;
			this->btnReopenRequest->Click += gcnew System::EventHandler(this, &MyRequestsForm::btnReopenRequest_Click);
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
			this->siticonePanel1->Location = System::Drawing::Point(0, 64);
			this->siticonePanel1->Name = L"siticonePanel1";
			this->siticonePanel1->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->siticonePanel1->RippleAlpha = 50;
			this->siticonePanel1->RippleAlphaDecrement = 3;
			this->siticonePanel1->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->siticonePanel1->RippleMaxSize = 600;
			this->siticonePanel1->RippleSpeed = 15;
			this->siticonePanel1->ShowBorder = true;
			this->siticonePanel1->Size = System::Drawing::Size(916, 479);
			this->siticonePanel1->TabIndex = 15;
			this->siticonePanel1->TabStop = true;
			this->siticonePanel1->TrackSystemTheme = false;
			this->siticonePanel1->UseBorderGradient = true;
			this->siticonePanel1->UseMultiGradient = false;
			this->siticonePanel1->UsePatternTexture = false;
			this->siticonePanel1->UseRadialGradient = false;
			//
			// MyRequestsForm
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->ClientSize = System::Drawing::Size(916, 543);
			this->Controls->Add(this->siticonePanel1);
			this->Controls->Add(this->headerPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyRequestsForm";
			this->Text = L"My Requests";
			this->headerPanel->ResumeLayout(false);
			this->headerPanel->PerformLayout();
			this->splitMain->Panel1->ResumeLayout(false);
			this->splitMain->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitMain))->EndInit();
			this->splitMain->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridRequests))->EndInit();
			this->detailsPanel->ResumeLayout(false);
			this->detailsPanel->PerformLayout();
			this->siticonePanel1->ResumeLayout(false);
			this->ResumeLayout(false);
		}
#pragma endregion
	};
}
