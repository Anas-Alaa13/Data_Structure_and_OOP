#include "MainForm.h"
#include "DataManager.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    DataManager dm; 
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew LoginGUI::MainForm(dm));
    dm.saveAllData(); 
    return 0;
}