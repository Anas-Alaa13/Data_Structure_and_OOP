#pragma once

#include "DataManager.h"
#include "UserManager.h"
#include <msclr/marshal_cppstd.h>

namespace LoginGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class ForgotPasswordForm : public Form
    {
    public:
        ForgotPasswordForm(DataManager& dataManager) : dm(dataManager), userManager(new UserManager())
        {
            InitializeComponent();
            this->DoubleBuffered = true; // تقليل الرجاج في الرسم
        }

        ~ForgotPasswordForm()
        {
            delete userManager; // تنظيف الذاكرة
        }

    private:
        DataManager& dm;
        UserManager* userManager;
        Label^ infoLabel;
        Label^ usernameLabel;
        TextBox^ usernameBox;
        Label^ phoneLabel;
        TextBox^ phoneBox;
        Button^ verifyButton; // زر التحقق الجديد
        Label^ newPasswordLabel;
        TextBox^ newPasswordBox;
        Button^ resetButton;
        Button^ cancelButton;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->infoLabel = (gcnew Label());
            this->usernameLabel = (gcnew Label());
            this->usernameBox = (gcnew TextBox());
            this->phoneLabel = (gcnew Label());
            this->phoneBox = (gcnew TextBox());
            this->verifyButton = (gcnew Button());
            this->newPasswordLabel = (gcnew Label());
            this->newPasswordBox = (gcnew TextBox());
            this->resetButton = (gcnew Button());
            this->cancelButton = (gcnew Button());
            this->SuspendLayout();

            // 
            // infoLabel
            // 
            this->infoLabel->AutoSize = true;
            this->infoLabel->Font = (gcnew Drawing::Font("Arial", 12, FontStyle::Bold));
            this->infoLabel->ForeColor = Color::Black;
            this->infoLabel->BackColor = Color::Transparent;
            this->infoLabel->Location = Point(50, 20);
            this->infoLabel->Text = L"Forgot your password? Let's reset it.";

            // 
            // usernameLabel
            // 
            this->usernameLabel->AutoSize = true;
            this->usernameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->usernameLabel->ForeColor = Color::Black;
            this->usernameLabel->BackColor = Color::Transparent;
            this->usernameLabel->Location = Point(100, 60);
            this->usernameLabel->Text = L"Username:";

            // 
            // usernameBox
            // 
            this->usernameBox->Location = Point(100, 90);
            this->usernameBox->Size = Drawing::Size(200, 30);
            this->usernameBox->BackColor = Color::White;
            this->usernameBox->ForeColor = Color::Black;

            // 
            // phoneLabel
            // 
            this->phoneLabel->AutoSize = true;
            this->phoneLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->phoneLabel->ForeColor = Color::Black;
            this->phoneLabel->BackColor = Color::Transparent;
            this->phoneLabel->Location = Point(100, 130);
            this->phoneLabel->Text = L"Phone Number:";

            // 
            // phoneBox
            // 
            this->phoneBox->Location = Point(100, 160);
            this->phoneBox->Size = Drawing::Size(200, 30);
            this->phoneBox->BackColor = Color::White;
            this->phoneBox->ForeColor = Color::Black;

            // 
            // verifyButton
            // 
            this->verifyButton->Location = Point(100, 210);
            this->verifyButton->Size = Drawing::Size(200, 40);
            this->verifyButton->Text = L"Verify";
            this->verifyButton->BackColor = Color::White;
            this->verifyButton->ForeColor = Color::Black;
            this->verifyButton->FlatStyle = FlatStyle::Flat;
            this->verifyButton->FlatAppearance->BorderSize = 0;
            this->verifyButton->Click += gcnew EventHandler(this, &ForgotPasswordForm::OnVerifyClicked);

            // 
            // newPasswordLabel
            // 
            this->newPasswordLabel->AutoSize = true;
            this->newPasswordLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->newPasswordLabel->ForeColor = Color::Black;
            this->newPasswordLabel->BackColor = Color::Transparent;
            this->newPasswordLabel->Location = Point(100, 260);
            this->newPasswordLabel->Text = L"New Password:";
            this->newPasswordLabel->Visible = false; // مخفي في البداية

            // 
            // newPasswordBox
            // 
            this->newPasswordBox->Location = Point(100, 290);
            this->newPasswordBox->Size = Drawing::Size(200, 30);
            this->newPasswordBox->UseSystemPasswordChar = true;
            this->newPasswordBox->BackColor = Color::White;
            this->newPasswordBox->ForeColor = Color::Black;
            this->newPasswordBox->Visible = false; // مخفي في البداية

            // 
            // resetButton
            // 
            this->resetButton->Location = Point(100, 340);
            this->resetButton->Size = Drawing::Size(90, 40);
            this->resetButton->Text = L"Reset Password";
            this->resetButton->BackColor = Color::White;
            this->resetButton->ForeColor = Color::Black;
            this->resetButton->FlatStyle = FlatStyle::Flat;
            this->resetButton->FlatAppearance->BorderSize = 0;
            this->resetButton->Click += gcnew EventHandler(this, &ForgotPasswordForm::OnResetClicked);
            this->resetButton->Visible = false; // مخفي في البداية

            // 
            // cancelButton
            // 
            this->cancelButton->Location = Point(210, 340);
            this->cancelButton->Size = Drawing::Size(90, 40);
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->BackColor = Color::White;
            this->cancelButton->ForeColor = Color::Black;
            this->cancelButton->FlatStyle = FlatStyle::Flat;
            this->cancelButton->FlatAppearance->BorderSize = 0;
            this->cancelButton->Click += gcnew EventHandler(this, &ForgotPasswordForm::OnCancel);

            // 
            // ForgotPasswordForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(400, 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Forgot Password";
            this->Controls->Add(this->infoLabel);
            this->Controls->Add(this->usernameLabel);
            this->Controls->Add(this->usernameBox);
            this->Controls->Add(this->phoneLabel);
            this->Controls->Add(this->phoneBox);
            this->Controls->Add(this->verifyButton);
            this->Controls->Add(this->newPasswordLabel);
            this->Controls->Add(this->newPasswordBox);
            this->Controls->Add(this->resetButton);
            this->Controls->Add(this->cancelButton);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    protected:
        virtual void OnPaintBackground(System::Windows::Forms::PaintEventArgs^ e) override
        {
            int width = this->ClientSize.Width;
            int height = this->ClientSize.Height;
            System::Drawing::Rectangle rect(0, 0, width, height);
            System::Drawing::Drawing2D::LinearGradientBrush^ brush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(rect, Color::White, Color::DarkGray, System::Drawing::Drawing2D::LinearGradientMode::Vertical);
            e->Graphics->FillRectangle(brush, rect);
        }

    private:
        void OnCancel(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }

        void OnVerifyClicked(Object^ sender, EventArgs^ e)
        {
            String^ username = usernameBox->Text;
            String^ phone = phoneBox->Text;

            std::string stdUsername = msclr::interop::marshal_as<std::string>(username);
            std::string stdPhone = msclr::interop::marshal_as<std::string>(phone);

            bool isValid = false;
            for (const auto& user : dm.users) {
                if (user.Username == stdUsername && user.PhoneNumber == stdPhone) {
                    isValid = true;
                    break;
                }
            }

            if (isValid) {
                // إظهار حقل New Password وزر Reset Password
                newPasswordLabel->Visible = true;
                newPasswordBox->Visible = true;
                resetButton->Visible = true;
                verifyButton->Visible = false; // إخفاء زر Verify بعد التحقق
            }
            else {
                MessageBox::Show("Invalid username or phone number", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnResetClicked(Object^ sender, EventArgs^ e)
        {
            String^ username = usernameBox->Text;
            String^ phone = phoneBox->Text;
            String^ newPassword = newPasswordBox->Text;

            std::string stdUsername = msclr::interop::marshal_as<std::string>(username);
            std::string stdPhone = msclr::interop::marshal_as<std::string>(phone);
            std::string stdNewPassword = msclr::interop::marshal_as<std::string>(newPassword);

            bool success = userManager->forgot(dm, stdUsername, stdPhone, stdNewPassword);

            if (success) {
                MessageBox::Show("Password reset successful", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }
            else {
                MessageBox::Show("Failed to reset password", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}