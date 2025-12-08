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

    public ref class RegisterForm : public Form
    {
    public:
        RegisterForm(DataManager& dataManager) : dm(dataManager), userManager(new UserManager())
        {
            InitializeComponent();
            this->DoubleBuffered = true; // تقليل الرجاج في الرسم
        }

        ~RegisterForm()
        {
            delete userManager; // تنظيف الذاكرة
        }

    private:
        DataManager& dm;
        UserManager* userManager;
        Label^ titleLabel; // ليبل ترحيبي جديد
        Label^ firstNameLabel;
        TextBox^ firstNameBox;
        Label^ lastNameLabel;
        TextBox^ lastNameBox;
        Label^ phoneLabel;
        TextBox^ phoneBox;
        Label^ emailLabel;
        TextBox^ emailBox;
        Label^ usernameLabel;
        TextBox^ usernameBox;
        Label^ passwordLabel;
        TextBox^ passwordBox;
        Label^ confirmLabel;
        TextBox^ confirmBox;
        Button^ registerButton;
        Button^ cancelButton;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->titleLabel = (gcnew Label());
            this->firstNameLabel = (gcnew Label());
            this->firstNameBox = (gcnew TextBox());
            this->lastNameLabel = (gcnew Label());
            this->lastNameBox = (gcnew TextBox());
            this->phoneLabel = (gcnew Label());
            this->phoneBox = (gcnew TextBox());
            this->emailLabel = (gcnew Label());
            this->emailBox = (gcnew TextBox());
            this->usernameLabel = (gcnew Label());
            this->usernameBox = (gcnew TextBox());
            this->passwordLabel = (gcnew Label());
            this->passwordBox = (gcnew TextBox());
            this->confirmLabel = (gcnew Label());
            this->confirmBox = (gcnew TextBox());
            this->registerButton = (gcnew Button());
            this->cancelButton = (gcnew Button());
            this->SuspendLayout();

            // 
            // titleLabel
            // 
            this->titleLabel->AutoSize = true;
            this->titleLabel->Font = (gcnew Drawing::Font("Arial", 16, FontStyle::Bold));
            this->titleLabel->ForeColor = Color::Black;
            this->titleLabel->BackColor = Color::Transparent;
            this->titleLabel->Location = Point(100, 20);
            this->titleLabel->Text = L"Register New Account";

            // 
            // firstNameLabel
            // 
            this->firstNameLabel->AutoSize = true;
            this->firstNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->firstNameLabel->ForeColor = Color::Black;
            this->firstNameLabel->BackColor = Color::Transparent;
            this->firstNameLabel->Location = Point(100, 60);
            this->firstNameLabel->Text = L"First Name:";

            // 
            // firstNameBox
            // 
            this->firstNameBox->Location = Point(100, 90);
            this->firstNameBox->Size = Drawing::Size(200, 30);
            this->firstNameBox->BackColor = Color::White;
            this->firstNameBox->ForeColor = Color::Black;

            // 
            // lastNameLabel
            // 
            this->lastNameLabel->AutoSize = true;
            this->lastNameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->lastNameLabel->ForeColor = Color::Black;
            this->lastNameLabel->BackColor = Color::Transparent;
            this->lastNameLabel->Location = Point(100, 130);
            this->lastNameLabel->Text = L"Last Name:";

            // 
            // lastNameBox
            // 
            this->lastNameBox->Location = Point(100, 160);
            this->lastNameBox->Size = Drawing::Size(200, 30);
            this->lastNameBox->BackColor = Color::White;
            this->lastNameBox->ForeColor = Color::Black;

            // 
            // phoneLabel
            // 
            this->phoneLabel->AutoSize = true;
            this->phoneLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->phoneLabel->ForeColor = Color::Black;
            this->phoneLabel->BackColor = Color::Transparent;
            this->phoneLabel->Location = Point(100, 200);
            this->phoneLabel->Text = L"Phone:";

            // 
            // phoneBox
            // 
            this->phoneBox->Location = Point(100, 230);
            this->phoneBox->Size = Drawing::Size(200, 30);
            this->phoneBox->BackColor = Color::White;
            this->phoneBox->ForeColor = Color::Black;

            // 
            // emailLabel
            // 
            this->emailLabel->AutoSize = true;
            this->emailLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->emailLabel->ForeColor = Color::Black;
            this->emailLabel->BackColor = Color::Transparent;
            this->emailLabel->Location = Point(100, 270);
            this->emailLabel->Text = L"Email:";

            // 
            // emailBox
            // 
            this->emailBox->Location = Point(100, 300);
            this->emailBox->Size = Drawing::Size(200, 30);
            this->emailBox->BackColor = Color::White;
            this->emailBox->ForeColor = Color::Black;

            // 
            // usernameLabel
            // 
            this->usernameLabel->AutoSize = true;
            this->usernameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->usernameLabel->ForeColor = Color::Black;
            this->usernameLabel->BackColor = Color::Transparent;
            this->usernameLabel->Location = Point(100, 340);
            this->usernameLabel->Text = L"Username:";

            // 
            // usernameBox
            // 
            this->usernameBox->Location = Point(100, 370);
            this->usernameBox->Size = Drawing::Size(200, 30);
            this->usernameBox->BackColor = Color::White;
            this->usernameBox->ForeColor = Color::Black;

            // 
            // passwordLabel
            // 
            this->passwordLabel->AutoSize = true;
            this->passwordLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->passwordLabel->ForeColor = Color::Black;
            this->passwordLabel->BackColor = Color::Transparent;
            this->passwordLabel->Location = Point(100, 410);
            this->passwordLabel->Text = L"Password:";

            // 
            // passwordBox
            // 
            this->passwordBox->Location = Point(100, 440);
            this->passwordBox->Size = Drawing::Size(200, 30);
            this->passwordBox->UseSystemPasswordChar = true;
            this->passwordBox->BackColor = Color::White;
            this->passwordBox->ForeColor = Color::Black;

            // 
            // confirmLabel
            // 
            this->confirmLabel->AutoSize = true;
            this->confirmLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->confirmLabel->ForeColor = Color::Black;
            this->confirmLabel->BackColor = Color::Transparent;
            this->confirmLabel->Location = Point(100, 480);
            this->confirmLabel->Text = L"Confirm Password:";

            // 
            // confirmBox
            // 
            this->confirmBox->Location = Point(100, 510);
            this->confirmBox->Size = Drawing::Size(200, 30);
            this->confirmBox->UseSystemPasswordChar = true;
            this->confirmBox->BackColor = Color::White;
            this->confirmBox->ForeColor = Color::Black;

            // 
            // registerButton
            // 
            this->registerButton->Location = Point(100, 560);
            this->registerButton->Size = Drawing::Size(90, 40);
            this->registerButton->Text = L"Register";
            this->registerButton->BackColor = Color::White;
            this->registerButton->ForeColor = Color::Black;
            this->registerButton->FlatStyle = FlatStyle::Flat;
            this->registerButton->FlatAppearance->BorderSize = 0;
            this->registerButton->Click += gcnew EventHandler(this, &RegisterForm::OnRegisterClicked);
            this->registerButton->MouseEnter += gcnew EventHandler(this, &RegisterForm::OnButtonHover);
            this->registerButton->MouseLeave += gcnew EventHandler(this, &RegisterForm::OnButtonLeave);

            // 
            // cancelButton
            // 
            this->cancelButton->Location = Point(210, 560);
            this->cancelButton->Size = Drawing::Size(90, 40);
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->BackColor = Color::White;
            this->cancelButton->ForeColor = Color::Black;
            this->cancelButton->FlatStyle = FlatStyle::Flat;
            this->cancelButton->FlatAppearance->BorderSize = 0;
            this->cancelButton->Click += gcnew EventHandler(this, &RegisterForm::OnCancel);
            this->cancelButton->MouseEnter += gcnew EventHandler(this, &RegisterForm::OnButtonHover);
            this->cancelButton->MouseLeave += gcnew EventHandler(this, &RegisterForm::OnButtonLeave);

            // 
            // RegisterForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(400, 620);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Register";
            this->Controls->Add(this->titleLabel);
            this->Controls->Add(this->firstNameLabel);
            this->Controls->Add(this->firstNameBox);
            this->Controls->Add(this->lastNameLabel);
            this->Controls->Add(this->lastNameBox);
            this->Controls->Add(this->phoneLabel);
            this->Controls->Add(this->phoneBox);
            this->Controls->Add(this->emailLabel);
            this->Controls->Add(this->emailBox);
            this->Controls->Add(this->usernameLabel);
            this->Controls->Add(this->usernameBox);
            this->Controls->Add(this->passwordLabel);
            this->Controls->Add(this->passwordBox);
            this->Controls->Add(this->confirmLabel);
            this->Controls->Add(this->confirmBox);
            this->Controls->Add(this->registerButton);
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
            // فواصل بين الحقول
            using namespace System::Drawing::Drawing2D;
            Pen^ pen = gcnew Pen(Color::White, 1);
            e->Graphics->DrawLine(pen, 50, 120, 350, 120);
            e->Graphics->DrawLine(pen, 50, 190, 350, 190);
            e->Graphics->DrawLine(pen, 50, 260, 350, 260);
            e->Graphics->DrawLine(pen, 50, 330, 350, 330);
            e->Graphics->DrawLine(pen, 50, 400, 350, 400);
            e->Graphics->DrawLine(pen, 50, 470, 350, 470);
            delete pen;
        }

    private:
        void OnCancel(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show("Are you sure you want to cancel?", "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                this->Close();
            }
        }

        void OnRegisterClicked(Object^ sender, EventArgs^ e)
        {
            String^ firstName = firstNameBox->Text;
            String^ lastName = lastNameBox->Text;
            String^ phone = phoneBox->Text;
            String^ email = emailBox->Text;
            String^ username = usernameBox->Text;
            String^ password = passwordBox->Text;
            String^ confirmPassword = confirmBox->Text;

            if (password != confirmPassword) {
                MessageBox::Show("Passwords do not match!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (String::IsNullOrEmpty(firstName) || String::IsNullOrEmpty(lastName) ||
                String::IsNullOrEmpty(phone) || String::IsNullOrEmpty(email) ||
                String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password)) {
                MessageBox::Show("All fields are required!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            int id = dm.users.empty() ? 1 : dm.users.back().ID + 1;

            std::string stdFirstName = msclr::interop::marshal_as<std::string>(firstName);
            std::string stdLastName = msclr::interop::marshal_as<std::string>(lastName);
            std::string stdPhone = msclr::interop::marshal_as<std::string>(phone);
            std::string stdEmail = msclr::interop::marshal_as<std::string>(email);
            std::string stdUsername = msclr::interop::marshal_as<std::string>(username);
            std::string stdPassword = msclr::interop::marshal_as<std::string>(password);

            bool success = userManager->registerUser(dm, id, stdFirstName, stdLastName, stdPhone, stdUsername, stdPassword, stdEmail);

            if (success) {
                MessageBox::Show("Registration Successful", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }
            else {
                MessageBox::Show("Username already exists. Please try another one.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnButtonHover(Object^ sender, EventArgs^ e)
        {
            Button^ btn = safe_cast<Button^>(sender);
            btn->BackColor = Color::White;
        }

        void OnButtonLeave(Object^ sender, EventArgs^ e)
        {
            Button^ btn = safe_cast<Button^>(sender);
            btn->BackColor = Color::White;
        }
    };
}