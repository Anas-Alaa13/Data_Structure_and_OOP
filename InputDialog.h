// InputDialog.h
#pragma once

namespace LoginGUI {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class InputDialog : public Form
    {
    public:
        TextBox^ inputBox;
        InputDialog(String^ prompt, String^ title)
        {
            this->Text = title;
            this->Size = Drawing::Size(300, 150);
            this->StartPosition = FormStartPosition::CenterScreen;

            Label^ label = gcnew Label();
            label->Text = prompt;
            label->Location = Point(20, 20);
            label->Size = Drawing::Size(260, 20);

            inputBox = gcnew TextBox();
            inputBox->Location = Point(20, 50);
            inputBox->Size = Drawing::Size(240, 20);

            Button^ okButton = gcnew Button();
            okButton->Text = "OK";
            okButton->Location = Point(80, 80);
            okButton->Click += gcnew EventHandler(this, &InputDialog::OnOkClicked);

            Button^ cancelButton = gcnew Button();
            cancelButton->Text = "Cancel";
            cancelButton->Location = Point(160, 80);
            cancelButton->Click += gcnew EventHandler(this, &InputDialog::OnCancelClicked);

            this->Controls->Add(label);
            this->Controls->Add(inputBox);
            this->Controls->Add(okButton);
            this->Controls->Add(cancelButton);
        }

    private:
        void OnOkClicked(Object^ sender, EventArgs^ e)
        {
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        void OnCancelClicked(Object^ sender, EventArgs^ e)
        {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }
    };
}