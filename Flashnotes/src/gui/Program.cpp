#include "MainWindow.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>


using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
    flashnotes::AppController app;
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew FlashnotesGUI::MainWindow(&app));
    return 0;
}
