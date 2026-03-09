#include "Product.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace SiticoneNetFrameworkUI;

namespace IntraProcure {
	public ref class ProductCardControl : public System::Windows::Forms::UserControl
	{
	public:
		ProductCardControl(void)
		{
			InitializeComponent();
			// Default styling adjustments
			this->BackColor = Color::White;
			this->Padding = System::Windows::Forms::Padding(8);
		}

	protected:
		~ProductCardControl()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		// Public properties
		property int ProductId;
		property String^ ImagePath;

		// populate control
		void SetData(int id, String^ name, String^ category, double price, String^ stockText, String^ imagePath)
		{
			this->ProductId = id;
			lblName->Text = name;
			lblCategory->Text = category;
			lblPrice->Text = String::Format("{0:N2} EGP", price);
			lblStock->Text = stockText;
			this->ImagePath = imagePath;

			// try load image (safe)
			try
			{
				if (!String::IsNullOrEmpty(imagePath) && System::IO::File::Exists(imagePath))
				{
					// load from file into a new Bitmap to avoid file lock
					Image^ img = Image::FromFile(imagePath);
					picImage->Image = gcnew Bitmap(img);
					delete img;
				}
				else
				{
					picImage->Image = nullptr;
				}
			}
			catch (...)
			{
				picImage->Image = nullptr;
			}
		}

		// Event - raised when Add to cart clicked
		System::EventHandler^ AddToCartClicked;

		// Add this public property to expose the price value safely
	public:
		property System::Decimal UnitPrice
		{
			System::Decimal get()
			{
				// Assuming lblPrice->Text is in the format "$123.45"
				System::String^ priceText = lblPrice->Text->Replace(L" EGP", L"")->Trim();
				System::Decimal price = 0;
				System::Decimal::TryParse(priceText, price);
				return price;
			}
		}

	private: SiticoneNetFrameworkUI::SiticonePanel^ panelCard;
	private: SiticoneNetFrameworkUI::SiticonePictureBox^ picImage;
	private: SiticoneNetFrameworkUI::SiticoneButton^ btnAddToCart;

	private: System::Windows::Forms::Label^ lblStock;
	private: System::Windows::Forms::Label^ lblPrice;
	private: System::Windows::Forms::Label^ lblCategory;
	private: System::Windows::Forms::Label^ lblName;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ProductCardControl::typeid));
			this->panelCard = (gcnew SiticoneNetFrameworkUI::SiticonePanel());
			this->btnAddToCart = (gcnew SiticoneNetFrameworkUI::SiticoneButton());
			this->lblStock = (gcnew System::Windows::Forms::Label());
			this->lblPrice = (gcnew System::Windows::Forms::Label());
			this->lblCategory = (gcnew System::Windows::Forms::Label());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->picImage = (gcnew SiticoneNetFrameworkUI::SiticonePictureBox());
			this->panelCard->SuspendLayout();
			this->SuspendLayout();
			//
			// panelCard
			//
			this->panelCard->AcrylicTintColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelCard->BackColor = System::Drawing::Color::Transparent;
			this->panelCard->BorderAlignment = System::Drawing::Drawing2D::PenAlignment::Center;
			this->panelCard->BorderDashPattern = nullptr;
			this->panelCard->BorderGradientEndColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(232)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->panelCard->BorderGradientStartColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(232)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->panelCard->BorderThickness = 2;
			this->panelCard->Controls->Add(this->btnAddToCart);
			this->panelCard->Controls->Add(this->lblStock);
			this->panelCard->Controls->Add(this->lblPrice);
			this->panelCard->Controls->Add(this->lblCategory);
			this->panelCard->Controls->Add(this->lblName);
			this->panelCard->Controls->Add(this->picImage);
			this->panelCard->CornerRadiusBottomLeft = 10;
			this->panelCard->CornerRadiusBottomRight = 10;
			this->panelCard->CornerRadiusTopLeft = 10;
			this->panelCard->CornerRadiusTopRight = 10;
			this->panelCard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelCard->EnableAcrylicEffect = false;
			this->panelCard->EnableMicaEffect = false;
			this->panelCard->EnableRippleEffect = false;
			this->panelCard->FillColor = System::Drawing::Color::White;
			this->panelCard->GradientColors = gcnew cli::array< System::Drawing::Color >(3) {
				System::Drawing::Color::White, System::Drawing::Color::LightGray,
					System::Drawing::Color::Gray
			};
			this->panelCard->GradientPositions = gcnew cli::array< System::Single >(3) { 0, 0.5F, 1 };
			this->panelCard->Location = System::Drawing::Point(0, 0);
			this->panelCard->Name = L"panelCard";
			this->panelCard->Padding = System::Windows::Forms::Padding(10);
			this->panelCard->PatternStyle = System::Drawing::Drawing2D::HatchStyle::LargeGrid;
			this->panelCard->RippleAlpha = 50;
			this->panelCard->RippleAlphaDecrement = 3;
			this->panelCard->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(50)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->panelCard->RippleMaxSize = 600;
			this->panelCard->RippleSpeed = 15;
			this->panelCard->ShowBorder = true;
			this->panelCard->Size = System::Drawing::Size(240, 130);
			this->panelCard->TabIndex = 0;
			this->panelCard->TabStop = true;
			this->panelCard->TrackSystemTheme = false;
			this->panelCard->UseBorderGradient = true;
			this->panelCard->UseMultiGradient = false;
			this->panelCard->UsePatternTexture = false;
			this->panelCard->UseRadialGradient = false;
			//
			// btnAddToCart
			//
			this->btnAddToCart->AccessibleDescription = L"The default button control that accept input though the mouse, touch and keyboard"
				L"";
			this->btnAddToCart->AccessibleName = L"Add to cart";
			this->btnAddToCart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnAddToCart->AutoSizeBasedOnText = false;
			this->btnAddToCart->BackColor = System::Drawing::Color::Transparent;
			this->btnAddToCart->BadgeBackColor = System::Drawing::Color::Black;
			this->btnAddToCart->BadgeFont = (gcnew System::Drawing::Font(L"Segoe UI", 8, System::Drawing::FontStyle::Bold));
			this->btnAddToCart->BadgeValue = 0;
			this->btnAddToCart->BadgeValueForeColor = System::Drawing::Color::White;
			this->btnAddToCart->BorderColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(213)), static_cast<System::Int32>(static_cast<System::Byte>(216)),
				static_cast<System::Int32>(static_cast<System::Byte>(220)));
			this->btnAddToCart->BorderWidth = 1;
			this->btnAddToCart->ButtonBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->btnAddToCart->ButtonImage = nullptr;
			this->btnAddToCart->ButtonTextLeftPadding = 0;
			this->btnAddToCart->CanBeep = true;
			this->btnAddToCart->CanGlow = false;
			this->btnAddToCart->CanShake = true;
			this->btnAddToCart->ContextMenuStripEx = nullptr;
			this->btnAddToCart->CornerRadiusBottomLeft = 6;
			this->btnAddToCart->CornerRadiusBottomRight = 6;
			this->btnAddToCart->CornerRadiusTopLeft = 6;
			this->btnAddToCart->CornerRadiusTopRight = 6;
			this->btnAddToCart->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnAddToCart->CustomCursor = System::Windows::Forms::Cursors::Hand;
			this->btnAddToCart->DisabledTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->btnAddToCart->EnableLongPress = false;
			this->btnAddToCart->EnableRippleEffect = true;
			this->btnAddToCart->EnableShadow = false;
			this->btnAddToCart->EnableTextWrapping = false;
			this->btnAddToCart->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 8.75F));
			this->btnAddToCart->ForeColor = System::Drawing::Color::White;
			this->btnAddToCart->GlowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnAddToCart->GlowIntensity = 100;
			this->btnAddToCart->GlowRadius = 20;
			this->btnAddToCart->GradientBackground = false;
			this->btnAddToCart->GradientColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->btnAddToCart->GradientMode = System::Drawing::Drawing2D::LinearGradientMode::Vertical;
			this->btnAddToCart->HintText = nullptr;
			this->btnAddToCart->HoverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->btnAddToCart->HoverFontStyle = System::Drawing::FontStyle::Regular;
			this->btnAddToCart->HoverTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnAddToCart->HoverTransitionDuration = 250;
			this->btnAddToCart->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btnAddToCart->ImagePadding = 5;
			this->btnAddToCart->ImageSize = System::Drawing::Size(16, 16);
			this->btnAddToCart->IsRadial = false;
			this->btnAddToCart->IsReadOnly = false;
			this->btnAddToCart->IsToggleButton = false;
			this->btnAddToCart->IsToggled = false;
			this->btnAddToCart->Location = System::Drawing::Point(120, 96);
			this->btnAddToCart->LongPressDurationMS = 1000;
			this->btnAddToCart->Name = L"btnAddToCart";
			this->btnAddToCart->NormalFontStyle = System::Drawing::FontStyle::Regular;
			this->btnAddToCart->ParticleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
			this->btnAddToCart->ParticleCount = 15;
			this->btnAddToCart->PressAnimationScale = 0.97F;
			this->btnAddToCart->PressedBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)),
				static_cast<System::Int32>(static_cast<System::Byte>(227)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->btnAddToCart->PressedFontStyle = System::Drawing::FontStyle::Regular;
			this->btnAddToCart->PressTransitionDuration = 150;
			this->btnAddToCart->ReadOnlyTextColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(100)));
			this->btnAddToCart->RippleColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnAddToCart->RippleRadiusMultiplier = 0.6F;
			this->btnAddToCart->ShadowBlur = 5;
			this->btnAddToCart->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->btnAddToCart->ShadowOffset = System::Drawing::Point(0, 2);
			this->btnAddToCart->ShakeDuration = 500;
			this->btnAddToCart->ShakeIntensity = 5;
			this->btnAddToCart->Size = System::Drawing::Size(110, 26);
			this->btnAddToCart->TabIndex = 0;
			this->btnAddToCart->Text = L"Add to cart";
			this->btnAddToCart->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->btnAddToCart->TextColor = System::Drawing::Color::White;
			this->btnAddToCart->TooltipText = nullptr;
			this->btnAddToCart->UseAdvancedRendering = true;
			this->btnAddToCart->UseParticles = false;
			this->btnAddToCart->Click += gcnew System::EventHandler(this, &ProductCardControl::btnAddToCart_Click);
			//
			// lblStock
			//
			this->lblStock->AutoEllipsis = true;
			this->lblStock->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblStock->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(140)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lblStock->Location = System::Drawing::Point(100, 76);
			this->lblStock->Name = L"lblStock";
			this->lblStock->Size = System::Drawing::Size(130, 18);
			this->lblStock->TabIndex = 4;
			this->lblStock->Text = L"In stock";
			//
			// lblPrice
			//
			this->lblPrice->AutoSize = true;
			this->lblPrice->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10, System::Drawing::FontStyle::Bold));
			this->lblPrice->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(110)));
			this->lblPrice->Location = System::Drawing::Point(100, 56);
			this->lblPrice->MaximumSize = System::Drawing::Size(140, 20);
			this->lblPrice->Name = L"lblPrice";
			this->lblPrice->Size = System::Drawing::Size(65, 19);
			this->lblPrice->TabIndex = 3;
			this->lblPrice->Text = L"0.00 EGP";
			//
			// lblCategory
			//
			this->lblCategory->AutoEllipsis = true;
			this->lblCategory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.5F));
			this->lblCategory->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->lblCategory->Location = System::Drawing::Point(100, 34);
			this->lblCategory->Name = L"lblCategory";
			this->lblCategory->Size = System::Drawing::Size(130, 18);
			this->lblCategory->TabIndex = 2;
			this->lblCategory->Text = L"Category";
			//
			// lblName
			//
			this->lblName->AutoEllipsis = true;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 9.75F, System::Drawing::FontStyle::Bold));
			this->lblName->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblName->Location = System::Drawing::Point(100, 12);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(130, 22);
			this->lblName->TabIndex = 1;
			this->lblName->Text = L"Product name";
			//
			// picImage
			//
			this->picImage->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(242)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->picImage->BorderColor = System::Drawing::Color::Transparent;
			this->picImage->BorderWidth = 1;
			this->picImage->Brightness = 1;
			this->picImage->Contrast = 1;
			this->picImage->CornerRadius = 8;
			this->picImage->DraggingSpeed = 3.15F;
			this->picImage->EnableAsyncLoading = false;
			this->picImage->EnableCaching = false;
			this->picImage->EnableDragDrop = false;
			this->picImage->EnableExtendedImageSources = false;
			this->picImage->EnableFilters = false;
			this->picImage->EnableFlipping = false;
			this->picImage->EnableGlow = false;
			this->picImage->EnableHighDpiSupport = false;
			this->picImage->EnableMouseInteraction = false;
			this->picImage->EnablePlaceholder = false;
			this->picImage->EnableRotation = false;
			this->picImage->EnableShadow = false;
			this->picImage->EnableSlideshow = false;
			this->picImage->FlipHorizontal = false;
			this->picImage->FlipVertical = false;
			this->picImage->Grayscale = false;
			this->picImage->Image = nullptr;
			this->picImage->ImageOpacity = 1;
			this->picImage->Images = (cli::safe_cast<System::Collections::Generic::List<System::Drawing::Image^ >^>(resources->GetObject(L"picImage.Images")));
			this->picImage->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
			this->picImage->IsCircular = false;
			this->picImage->Location = System::Drawing::Point(10, 15);
			this->picImage->MaintainAspectRatio = true;
			this->picImage->Name = L"picImage";
			this->picImage->PlaceholderImage = nullptr;
			this->picImage->RotationAngle = 0;
			this->picImage->Saturation = 1;
			this->picImage->ShowBorder = false;
			this->picImage->Size = System::Drawing::Size(80, 80);
			this->picImage->SizeMode = SiticoneNetFrameworkUI::Helpers::Enum::SiticonePictureBoxSizeMode::Zoom;
			this->picImage->TabIndex = 0;
			this->picImage->TabStop = false;
			//
			// ProductCardControl
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Transparent;
			this->Controls->Add(this->panelCard);
			this->Name = L"ProductCardControl";
			this->Size = System::Drawing::Size(240, 130);
			this->panelCard->ResumeLayout(false);
			this->panelCard->PerformLayout();
			this->ResumeLayout(false);
		}
#pragma endregion

	private:
		// ------------- Event handlers -------------
		System::Void btnAddToCart_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->AddToCartClicked != nullptr)
				this->AddToCartClicked(this, gcnew System::EventArgs());
		}
	};
}