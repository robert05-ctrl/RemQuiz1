#include "MainWindow.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <controllers/AppController.hpp>
#include <Windows.h>

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

// MSVC expects a WinMain entry point when building a WIN32
// subsystem executable. Provide a thin wrapper that forwards
// to the CLI main function so linking succeeds.
[STAThreadAttribute]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main(Environment::GetCommandLineArgs());
}
