#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <controllers/NotesController.hpp>

namespace FlashnotesGUI {
using namespace System;
using namespace System::Windows::Forms;

public ref class NoteEditorForm : public UserControl
{
public:
    NoteEditorForm(flashnotes::NotesController* ctrl);

private:
    flashnotes::NotesController* controller;
    TextBox^ noteTitle;
    TextBox^ noteBody;
    Button^ btnSave;

    void onSave(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
