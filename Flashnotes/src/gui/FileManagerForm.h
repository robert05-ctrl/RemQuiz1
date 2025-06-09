#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <controllers/FileController.hpp>

namespace FlashnotesGUI {
using namespace System;
using namespace System::Windows::Forms;

public ref class FileManagerForm : public UserControl
{
public:
    FileManagerForm(flashnotes::FileController* ctrl);

private:
    flashnotes::FileController* controller;
    ListView^ fileList;
    Button^ btnAdd;

    void onAdd(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
