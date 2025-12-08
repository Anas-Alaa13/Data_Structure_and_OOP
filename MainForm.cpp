#include "MainForm.h"
#include "RegisterForm.h"
#include "LoginForm.h"
#include "ForgotPasswordForm.h"

namespace LoginGUI {

    System::Void MainForm::OnRegisterClicked(System::Object^ sender, System::EventArgs^ e) {
        RegisterForm^ registerForm = gcnew RegisterForm(dm);
        registerForm->ShowDialog();
    }

    System::Void MainForm::OnLoginClicked(System::Object^ sender, System::EventArgs^ e) {
        LoginForm^ loginForm = gcnew LoginForm(dm);
        loginForm->ShowDialog();
    }

    System::Void MainForm::OnForgotClicked(System::Object^ sender, System::EventArgs^ e) {
        ForgotPasswordForm^ forgotForm = gcnew ForgotPasswordForm(dm);
        forgotForm->ShowDialog();
    }

    System::Void MainForm::OnExitClicked(System::Object^ sender, System::EventArgs^ e) {
        this->Close(); // بتغلق النافذة وبتخلص البرنامج
    }
}