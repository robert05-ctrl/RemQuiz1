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
    ListBox^ noteList;
    TextBox^ noteTitle;
    TextBox^ noteBody;
    Button^ btnSave;
    Button^ btnUpdate;
    Button^ btnOpen;
    Button^ btnNew;
    Button^ btnDelete;
    int currentId;

    void loadNotes();
    void onSelect(Object^ sender, EventArgs^ e);
    void onOpen(Object^ sender, EventArgs^ e);
    void onNew(Object^ sender, EventArgs^ e);
    void onSave(Object^ sender, EventArgs^ e);
    void onUpdate(Object^ sender, EventArgs^ e);
    void onDelete(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
