#pragma once

#include "DataManager.h"

namespace LoginGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(DataManager& dataManager) : dm(dataManager)
        {
            InitializeComponent();
            this->DoubleBuffered = true; // تقليل الرجاج في الرسم
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
        DataManager& dm; // مرجع إلى DataManager
        System::Windows::Forms::PictureBox^ welcomeImage;
        System::Windows::Forms::Label^ welcomeLabel;
        System::Windows::Forms::Label^ descriptionLabel;
        System::Windows::Forms::Button^ loginButton;
        System::Windows::Forms::Button^ forgotPasswordButton; // غيرت الاسم عشان يكون متسق مع النوع
        System::Windows::Forms::Button^ signUpButton;        // غيرت الاسم عشان يكون متسق مع النوع
        System::Windows::Forms::Button^ exitButton;          // زر الخروج الجديد
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->welcomeImage = (gcnew System::Windows::Forms::PictureBox());
            this->welcomeLabel = (gcnew System::Windows::Forms::Label());
            this->descriptionLabel = (gcnew System::Windows::Forms::Label());
            this->loginButton = (gcnew System::Windows::Forms::Button());
            this->forgotPasswordButton = (gcnew System::Windows::Forms::Button());
            this->signUpButton = (gcnew System::Windows::Forms::Button());
            this->exitButton = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // 
            // welcomeImage
            // 
            this->welcomeImage->Location = System::Drawing::Point(900, 50); 
            this->welcomeImage->Size = System::Drawing::Size(460, 100);
            this->welcomeImage->SizeMode = PictureBoxSizeMode::Zoom;
            this->welcomeImage->BackColor = Color::Transparent;
            try {
                this->welcomeImage->Image = Image::FromFile("ASU.jpeg"); 
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading image: " + ex->Message);
            }

            // 
            // welcomeLabel
            // 
            this->welcomeLabel->AutoSize = true;
            this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Arial", 24, FontStyle::Bold));
            this->welcomeLabel->ForeColor = Color::White;
            this->welcomeLabel->BackColor = Color::Transparent;
            this->welcomeLabel->Location = System::Drawing::Point(50, 50); 
            //this->welcomeLabel->Text = L" WELCOME TO THE OUR SYSTEM";

            // 
            // descriptionLabel
            // 
            this->descriptionLabel->AutoSize = true;
            this->descriptionLabel->Font = (gcnew System::Drawing::Font(L"Arial", 10));
            this->descriptionLabel->ForeColor = Color::White;
            this->descriptionLabel->BackColor = Color::Transparent;
            this->descriptionLabel->Location = System::Drawing::Point(550, 280); // توسيط النص الوصفي
            //this->descriptionLabel->Text = L" Please Give Me The Full Mark 🙂🥺";

            // 
            // loginButton
            // 
            this->loginButton->Location = System::Drawing::Point(70, 230); // توسيط الزر
            this->loginButton->Size = System::Drawing::Size(200, 40);
            this->loginButton->Text = L"Login";
            this->loginButton->BackColor = Color::LightGray;
            this->loginButton->ForeColor = Color::Black;
            this->loginButton->FlatStyle = FlatStyle::Flat;
            this->loginButton->FlatAppearance->BorderSize = 0;
            this->loginButton->Click += gcnew System::EventHandler(this, &MainForm::OnLoginClicked);

            // 
            // forgotPasswordButton
            // 
            this->forgotPasswordButton->Location = System::Drawing::Point(70, 280); // توسيط الزر
            this->forgotPasswordButton->Size = System::Drawing::Size(200, 40);
            this->forgotPasswordButton->Text = L"Forgot Password";
            this->forgotPasswordButton->BackColor = Color::LightGray;
            this->forgotPasswordButton->ForeColor = Color::Black;
            this->forgotPasswordButton->FlatStyle = FlatStyle::Flat;
            this->forgotPasswordButton->FlatAppearance->BorderSize = 0;
            this->forgotPasswordButton->Click += gcnew System::EventHandler(this, &MainForm::OnForgotClicked);

            // 
            // signUpButton
            // 
            this->signUpButton->Location = System::Drawing::Point(70, 330); // توسيط الزر
            this->signUpButton->Size = System::Drawing::Size(200, 40);
            this->signUpButton->Text = L"Sign Up";
            this->signUpButton->BackColor = Color::LightGray;
            this->signUpButton->ForeColor = Color::Black;
            this->signUpButton->FlatStyle = FlatStyle::Flat;
            this->signUpButton->FlatAppearance->BorderSize = 0;
            this->signUpButton->Click += gcnew System::EventHandler(this, &MainForm::OnRegisterClicked);

            // 
            // exitButton
            // 
            this->exitButton->Location = System::Drawing::Point(70, 380); // زر الخروج تحت signUpButton
            this->exitButton->Size = System::Drawing::Size(200, 40);
            this->exitButton->Text = L"Exit";
            this->exitButton->BackColor = Color::LightGray;
            this->exitButton->ForeColor = Color::Black;
            this->exitButton->FlatStyle = FlatStyle::Flat;
            this->exitButton->FlatAppearance->BorderSize = 0;
            this->exitButton->Click += gcnew System::EventHandler(this, &MainForm::OnExitClicked);

            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1200, 600); // حجم أصغر ومناسب
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle; // حدود ثابتة
            this->MaximizeBox = false; // منع التكبير
            this->StartPosition = FormStartPosition::CenterScreen; // توسيط النافذة على الشاشة
            this->Controls->Add(this->welcomeImage);
            this->Controls->Add(this->welcomeLabel);
            this->Controls->Add(this->descriptionLabel);
            this->Controls->Add(this->loginButton);
            this->Controls->Add(this->forgotPasswordButton);
            this->Controls->Add(this->signUpButton);
            this->Controls->Add(this->exitButton);
            this->Name = L"MainForm";
            this->Text = L"Main Form";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    protected:
        virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override
        {
            try {
                // تحميل الصورة كخلفية
                System::Drawing::Image^ backgroundImage = System::Drawing::Image::FromFile("CC.jpg");

                // رسم الصورة لتملأ الخلفية بالكامل
                e->Graphics->DrawImage(backgroundImage, System::Drawing::Rectangle(0, 0, this->ClientSize.Width, this->ClientSize.Height));
            }
            catch (Exception^ ex) {
                // في حالة فشل تحميل الصورة، يمكنك طباعة رسالة أو الرجوع لتدرج لوني بديل
                MessageBox::Show("Error loading background image: " + ex->Message);
                // (اختياري) رسم خلفية بلون ثابت
                e->Graphics->Clear(System::Drawing::Color::LightGray);
            }
        }

    private:
        System::Void OnRegisterClicked(System::Object^ sender, System::EventArgs^ e);
        System::Void OnLoginClicked(System::Object^ sender, System::EventArgs^ e);
        System::Void OnForgotClicked(System::Object^ sender, System::EventArgs^ e);
        System::Void OnExitClicked(System::Object^ sender, System::EventArgs^ e); // دالة زر الخروج
    };
}