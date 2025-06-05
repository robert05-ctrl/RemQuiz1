#pragma once

#include <controllers/NotesController.hpp>

using namespace System;
using namespace System::Windows::Forms;

namespace FlashnotesGUI {

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
