#pragma once

#include "DataManager.h"
#include "UserManager.h"
#include "StudentForm.h"
#include "AdminForm.h"
#include <msclr/marshal_cppstd.h>
#include "Student.h"

namespace LoginGUI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class LoginForm : public Form
    {
    public:
        LoginForm(DataManager& dataManager) : dm(dataManager), userManager(new UserManager())
        {
            InitializeComponent();
            this->DoubleBuffered = true; // تقليل الرجاج في الرسم
        }

        ~LoginForm()
        {
            delete userManager;
        }

    private:
        DataManager& dm;
        UserManager* userManager;
        Label^ usernameLabel;
        TextBox^ usernameTextBox;
        Label^ passwordLabel;
        TextBox^ passwordTextBox;
        Button^ loginButton;
        Button^ cancelButton;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->usernameLabel = (gcnew Label());
            this->usernameTextBox = (gcnew TextBox());
            this->passwordLabel = (gcnew Label());
            this->passwordTextBox = (gcnew TextBox());
            this->loginButton = (gcnew Button());
            this->cancelButton = (gcnew Button());
            this->SuspendLayout();

            // 
            // usernameLabel
            // 
            this->usernameLabel->AutoSize = true;
            this->usernameLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->usernameLabel->ForeColor = Color::Black;
            this->usernameLabel->BackColor = Color::Transparent;
            this->usernameLabel->Location = Point(100, 50); // توسيط الليبل
            this->usernameLabel->Text = L"Username:";

            // 
            // usernameTextBox
            // 
            this->usernameTextBox->Location = Point(100, 80); // توسيط التكست بوكس
            this->usernameTextBox->Size = Drawing::Size(200, 30);
            this->usernameTextBox->BackColor = Color::White;
            this->usernameTextBox->ForeColor = Color::Black;

            // 
            // passwordLabel
            // 
            this->passwordLabel->AutoSize = true;
            this->passwordLabel->Font = (gcnew System::Drawing::Font(L"Arial", 12, FontStyle::Bold));
            this->passwordLabel->ForeColor = Color::Black;
            this->passwordLabel->BackColor = Color::Transparent;
            this->passwordLabel->Location = Point(100, 120);
            this->passwordLabel->Text = L"Password:";

            // 
            // passwordTextBox
            // 
            this->passwordTextBox->Location = Point(100, 150);
            this->passwordTextBox->Size = Drawing::Size(200, 30);
            this->passwordTextBox->UseSystemPasswordChar = true;
            this->passwordTextBox->BackColor = Color::White;
            this->passwordTextBox->ForeColor = Color::Black;

            // 
            // loginButton
            // 
            this->loginButton->Location = Point(100, 200);
            this->loginButton->Size = Drawing::Size(90, 40);
            this->loginButton->Text = L"Login";
            this->loginButton->BackColor = Color::White;
            this->loginButton->ForeColor = Color::Black;
            this->loginButton->FlatStyle = FlatStyle::Flat;
            this->loginButton->FlatAppearance->BorderSize = 0;
            this->loginButton->Click += gcnew EventHandler(this, &LoginForm::OnLoginClicked);

            // 
            // cancelButton
            // 
            this->cancelButton->Location = Point(210, 200);
            this->cancelButton->Size = Drawing::Size(90, 40);
            this->cancelButton->Text = L"Cancel";
            this->cancelButton->BackColor = Color::White;
            this->cancelButton->ForeColor = Color::Black;
            this->cancelButton->FlatStyle = FlatStyle::Flat;
            this->cancelButton->FlatAppearance->BorderSize = 0;
            this->cancelButton->Click += gcnew EventHandler(this, &LoginForm::OnCancel);

            // 
            // LoginForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(400, 400); // حجم أكبر ومناسب
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Login";
            this->Controls->Add(this->usernameLabel);
            this->Controls->Add(this->usernameTextBox);
            this->Controls->Add(this->passwordLabel);
            this->Controls->Add(this->passwordTextBox);
            this->Controls->Add(this->loginButton);
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

        void OnLoginClicked(Object^ sender, EventArgs^ e)
        {
            String^ username = usernameTextBox->Text;
            String^ password = passwordTextBox->Text;

            std::string stdUsername = msclr::interop::marshal_as<std::string>(username);
            std::string stdPassword = msclr::interop::marshal_as<std::string>(password);
            std::string userType;

            bool success = userManager->login(dm, stdUsername, stdPassword, userType);

            if (success) {
                MessageBox::Show("Login Successful", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                if (userType == "student") {
                    int studentID = 0;
                    for (const auto& user : dm.users) {
                        if (user.Username == stdUsername) {
                            studentID = user.ID;
                            break;
                        }
                    }
                    StudentForm^ studentForm = gcnew StudentForm(dm, studentID, username);
                    studentForm->ShowDialog();
                }
                else if (userType == "admin") {
                    AdminForm^ adminForm = gcnew AdminForm(dm);
                    adminForm->ShowDialog();
                }
                this->Close();
            }
            else {
                MessageBox::Show("Invalid username or password", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}