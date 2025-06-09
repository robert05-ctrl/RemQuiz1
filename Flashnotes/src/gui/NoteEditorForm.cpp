#include "NoteEditorForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>

namespace FlashnotesGUI {

NoteEditorForm::NoteEditorForm(flashnotes::NotesController* ctrl)
{
    controller = ctrl;
    Dock = DockStyle::Fill;

    noteList = gcnew ListBox();
    noteList->Dock = DockStyle::Left;
    noteList->Width = 150;
    noteList->SelectedIndexChanged += gcnew EventHandler(this, &NoteEditorForm::onSelect);

    noteTitle = gcnew TextBox();
    noteTitle->Dock = DockStyle::Top;

    noteBody = gcnew TextBox();
    noteBody->Multiline = true;
    noteBody->Dock = DockStyle::Fill;

    btnOpen = gcnew Button();
    btnOpen->Text = "Open";
    btnOpen->Dock = DockStyle::Bottom;
    btnOpen->Click += gcnew EventHandler(this, &NoteEditorForm::onOpen);


    btnNew = gcnew Button();
    btnNew->Text = "New";
    btnNew->Dock = DockStyle::Bottom;
    btnNew->Click += gcnew EventHandler(this, &NoteEditorForm::onNew);
    btnSave = gcnew Button();
    btnSave->Text = "Save";
    btnSave->Dock = DockStyle::Bottom;
    btnSave->Click += gcnew EventHandler(this, &NoteEditorForm::onSave);

    Controls->Add(noteBody);
    Controls->Add(btnSave);
    Controls->Add(btnOpen);
    Controls->Add(btnNew);

    Controls->Add(noteTitle);
    Controls->Add(noteList);

    loadNotes();
}

void NoteEditorForm::onSave(Object^ sender, EventArgs^ e)
{
    std::string title = msclr::interop::marshal_as<std::string>(noteTitle->Text);
    std::string body = msclr::interop::marshal_as<std::string>(noteBody->Text);

    SaveFileDialog^ dlg = gcnew SaveFileDialog();
    dlg->FileName = gcnew String(title.c_str());
    if (dlg->ShowDialog() != DialogResult::OK)
        return;
    std::string path = msclr::interop::marshal_as<std::string>(dlg->FileName);

    auto res = controller->createNote(title, body, path);
    if (!res)
        MessageBox::Show(gcnew String(res.error().c_str()));
    else
    {
        System::IO::File::WriteAllText(dlg->FileName, gcnew String(body.c_str()));
        MessageBox::Show("Saved!");
    }

    loadNotes();
}

void NoteEditorForm::loadNotes()
{
    noteList->Items->Clear();
    auto res = controller->listNotes();
    if (!res) {
        MessageBox::Show(gcnew String(res.error().c_str()));
        return;
    }
    for (const auto& n : res.value()) {
        noteList->Items->Add(gcnew String(n.title.c_str()));
    }
}

void NoteEditorForm::onSelect(Object^ sender, EventArgs^ e)
{
    int idx = noteList->SelectedIndex;
    if (idx < 0) return;
    auto res = controller->listNotes();
    if (!res || idx >= static_cast<int>(res.value().size())) return;
    auto& n = res.value()[idx];
    noteTitle->Text = gcnew String(n.title.c_str());
    noteBody->Text = gcnew String(n.body.c_str());
}

void NoteEditorForm::onOpen(Object^ sender, EventArgs^ e)
{
    int idx = noteList->SelectedIndex;
    if (idx < 0) return;
    auto res = controller->listNotes();
    if (!res || idx >= static_cast<int>(res.value().size())) return;
    auto& n = res.value()[idx];
    if (!n.savedPath.empty()) {
        System::String^ path = gcnew System::String(n.savedPath.c_str());
        if (System::IO::File::Exists(path)) {
            System::Diagnostics::Process::Start(path);
        }
    }
}

void NoteEditorForm::onNew(Object^ sender, EventArgs^ e)
{
    noteList->ClearSelected();
    noteTitle->Text = "";
    noteBody->Text = "";
}

} // namespace FlashnotesGUI
