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
    currentId = -1;

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
    btnOpen->AutoSize = true;
    btnOpen->Click += gcnew EventHandler(this, &NoteEditorForm::onOpen);

    btnUpdate = gcnew Button();
    btnUpdate->Text = "Update";
    btnUpdate->AutoSize = true;
    btnUpdate->Click += gcnew EventHandler(this, &NoteEditorForm::onUpdate);

    btnNew = gcnew Button();
    btnNew->Text = "New";
    btnNew->AutoSize = true;
    btnNew->Click += gcnew EventHandler(this, &NoteEditorForm::onNew);

    btnDelete = gcnew Button();
    btnDelete->Text = "Delete";
    btnDelete->AutoSize = true;
    btnDelete->Click += gcnew EventHandler(this, &NoteEditorForm::onDelete);

    btnSave = gcnew Button();
    btnSave->Text = "Save";
    btnSave->AutoSize = true;
    btnSave->Click += gcnew EventHandler(this, &NoteEditorForm::onSave);

    FlowLayoutPanel^ bar = gcnew FlowLayoutPanel();
    bar->Dock = DockStyle::Top;
    bar->AutoSize = true;
    bar->Controls->AddRange(gcnew cli::array<Control^>{btnNew, btnOpen, btnSave, btnUpdate, btnDelete});

    Controls->Add(noteBody);
    Controls->Add(noteTitle);
    Controls->Add(bar);
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
        currentId = res.value().id;
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
    if (idx < 0) { currentId = -1; return; }
    auto res = controller->listNotes();
    if (!res || idx >= static_cast<int>(res.value().size())) return;
    auto& n = res.value()[idx];
    currentId = n.id;
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
    currentId = n.id;
    if (!n.savedPath.empty()) {
        System::String^ path = gcnew System::String(n.savedPath.c_str());
        if (System::IO::File::Exists(path)) {
            noteTitle->Text = gcnew String(n.title.c_str());
            noteBody->Text = System::IO::File::ReadAllText(path);
        } else {
            MessageBox::Show("File not found");
        }
    }
}

void NoteEditorForm::onNew(Object^ sender, EventArgs^ e)
{
    noteList->ClearSelected();
    noteTitle->Text = "";
    noteBody->Text = "";
    currentId = -1;
}

void NoteEditorForm::onUpdate(Object^ sender, EventArgs^ e)
{
    int idx = noteList->SelectedIndex;
    if (idx < 0) return;
    auto listRes = controller->listNotes();
    if (!listRes || idx >= static_cast<int>(listRes.value().size())) return;
    auto n = listRes.value()[idx];
    std::string title = msclr::interop::marshal_as<std::string>(noteTitle->Text);
    std::string body  = msclr::interop::marshal_as<std::string>(noteBody->Text);
    auto res = controller->updateNote(n.id, title, body);
    if (!res) {
        MessageBox::Show(gcnew String(res.error().c_str()));
        return;
    }
    System::String^ path = gcnew System::String(n.savedPath.c_str());
    if (System::IO::File::Exists(path)) {
        System::IO::File::WriteAllText(path, gcnew String(body.c_str()));
    }
    currentId = n.id;
    MessageBox::Show("Updated!");
    loadNotes();
}

void NoteEditorForm::onDelete(Object^ sender, EventArgs^ e)
{
    int idx = noteList->SelectedIndex;
    if (idx < 0) return;
    auto listRes = controller->listNotes();
    if (!listRes || idx >= static_cast<int>(listRes.value().size())) return;
    auto n = listRes.value()[idx];
    auto res = controller->removeNote(n.id);
    if (!res) {
        MessageBox::Show(gcnew String(res.error().c_str()));
    }
    noteList->ClearSelected();
    noteTitle->Text = "";
    noteBody->Text = "";
    currentId = -1;
    loadNotes();
}

} // namespace FlashnotesGUI
