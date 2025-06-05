#include "NoteEditorForm.h"
#include <msclr/marshal_cppstd.h>

namespace FlashnotesGUI {

NoteEditorForm::NoteEditorForm(flashnotes::NotesController* ctrl)
{
    controller = ctrl;
    Dock = DockStyle::Fill;

    noteTitle = gcnew TextBox();
    noteTitle->PlaceholderText = "Title";
    noteTitle->Dock = DockStyle::Top;

    noteBody = gcnew TextBox();
    noteBody->Multiline = true;
    noteBody->Dock = DockStyle::Fill;

    btnSave = gcnew Button();
    btnSave->Text = "Save";
    btnSave->Dock = DockStyle::Bottom;
    btnSave->Click += gcnew EventHandler(this, &NoteEditorForm::onSave);

    Controls->Add(noteBody);
    Controls->Add(btnSave);
    Controls->Add(noteTitle);
}

void NoteEditorForm::onSave(Object^ sender, EventArgs^ e)
{
    std::string title = msclr::interop::marshal_as<std::string>(noteTitle->Text);
    std::string body = msclr::interop::marshal_as<std::string>(noteBody->Text);
    auto res = controller->createNote(title, body, ".");
    if (!res)
        MessageBox::Show(gcnew String(res.error().c_str()));
    else
        MessageBox::Show("Saved!");
}

} // namespace FlashnotesGUI
