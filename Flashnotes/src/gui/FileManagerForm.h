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
    TreeView^ tree;
    Button^ btnAddFile;
    Button^ btnAddFolder;
    Button^ btnOpen;
    Button^ btnDelete;

    void loadData();
    void onAddFile(Object^ sender, EventArgs^ e);
    void onAddFolder(Object^ sender, EventArgs^ e);
    void onOpen(Object^ sender, EventArgs^ e);
    void onDelete(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
