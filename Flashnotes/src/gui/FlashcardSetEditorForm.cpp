#include "FlashcardSetEditorForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>
#include <nlohmann/json.hpp>

namespace FlashnotesGUI {

FlashcardSetEditorForm::FlashcardSetEditorForm(flashnotes::FlashcardSetController* ctrl)
{
    controller = ctrl;
    Dock = DockStyle::Fill;
    currentId = -1;

    setList = gcnew ListBox();
    setList->Dock = DockStyle::Left;
    setList->Width = 150;
    setList->SelectedIndexChanged += gcnew EventHandler(this, &FlashcardSetEditorForm::onSelect);

    titleBox = gcnew TextBox();
    titleBox->Dock = DockStyle::Top;

    grid = gcnew DataGridView();
    grid->Dock = DockStyle::Fill;
    grid->AllowUserToAddRows = false;
    grid->Columns->Add("Front", "Front");
    grid->Columns->Add("Back", "Back");

    btnNew = gcnew Button(); btnNew->Text = "New"; btnNew->AutoSize = true; btnNew->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onNew);
    btnOpen = gcnew Button(); btnOpen->Text = "Open"; btnOpen->AutoSize = true; btnOpen->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onOpen);
    btnSave = gcnew Button(); btnSave->Text = "Save"; btnSave->AutoSize = true; btnSave->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onSave);
    btnUpdate = gcnew Button(); btnUpdate->Text = "Update"; btnUpdate->AutoSize = true; btnUpdate->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onUpdate);
    btnDelete = gcnew Button(); btnDelete->Text = "Delete"; btnDelete->AutoSize = true; btnDelete->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onDelete);
    btnAddCard = gcnew Button(); btnAddCard->Text = "Add"; btnAddCard->AutoSize = true; btnAddCard->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onAddCard);
    btnRemoveCard = gcnew Button(); btnRemoveCard->Text = "Remove"; btnRemoveCard->AutoSize = true; btnRemoveCard->Click += gcnew EventHandler(this, &FlashcardSetEditorForm::onRemoveCard);

    FlowLayoutPanel^ bar = gcnew FlowLayoutPanel();
    bar->Dock = DockStyle::Top;
    bar->AutoSize = true;
    bar->Controls->AddRange(gcnew cli::array<Control^>{btnNew, btnOpen, btnSave, btnUpdate, btnDelete, btnAddCard, btnRemoveCard});

    Controls->Add(grid);
    Controls->Add(bar);
    Controls->Add(titleBox);
    Controls->Add(setList);

    loadSets();
}

void FlashcardSetEditorForm::loadSets()
{
    setList->Items->Clear();
    auto res = controller->listSets();
    if (!res) { MessageBox::Show(gcnew String(res.error().c_str())); return; }
    for (const auto& s : res.value())
        setList->Items->Add(gcnew String(s.title.c_str()));
}

void FlashcardSetEditorForm::onSelect(Object^, EventArgs^)
{
    int idx = setList->SelectedIndex;
    if (idx < 0) { currentId = -1; grid->Rows->Clear(); titleBox->Text=""; return; }
    auto res = controller->listSets();
    if (!res || idx >= static_cast<int>(res.value().size())) return;
    auto s = res.value()[idx];
    currentId = s.id;
    titleBox->Text = gcnew String(s.title.c_str());
    grid->Rows->Clear();
    for (auto& c : s.cards) {
        grid->Rows->Add(gcnew String(c.front.c_str()), gcnew String(c.back.c_str()));
    }
}

void FlashcardSetEditorForm::onNew(Object^, EventArgs^)
{
    setList->ClearSelected();
    titleBox->Text="";
    grid->Rows->Clear();
    currentId = -1;
}

void FlashcardSetEditorForm::onAddCard(Object^, EventArgs^)
{
    grid->Rows->Add("",");
}

void FlashcardSetEditorForm::onRemoveCard(Object^, EventArgs^)
{
    if (grid->CurrentRow)
        grid->Rows->Remove(grid->CurrentRow);
}

static std::vector<flashnotes::Flashcard> collectCards(DataGridView^ grid)
{
    std::vector<flashnotes::Flashcard> cards;
    for each (DataGridViewRow^ row in grid->Rows) {
        if (row->IsNewRow) continue;
        System::String^ f = row->Cells[0]->Value ? row->Cells[0]->Value->ToString() : "";
        System::String^ b = row->Cells[1]->Value ? row->Cells[1]->Value->ToString() : "";
        cards.push_back({0, msclr::interop::marshal_as<std::string>(f), msclr::interop::marshal_as<std::string>(b)});
    }
    return cards;
}

void FlashcardSetEditorForm::onSave(Object^, EventArgs^)
{
    std::string title = msclr::interop::marshal_as<std::string>(titleBox->Text);
    auto cards = collectCards(grid);
    SaveFileDialog^ dlg = gcnew SaveFileDialog();
    dlg->FileName = gcnew String(title.c_str());
    if (dlg->ShowDialog() != DialogResult::OK) return;
    std::string path = msclr::interop::marshal_as<std::string>(dlg->FileName);
    auto res = controller->createSet(title, cards, path);
    if (!res) { MessageBox::Show(gcnew String(res.error().c_str())); return; }
    nlohmann::json j = cards;
    System::IO::File::WriteAllText(dlg->FileName, gcnew String(j.dump(4).c_str()));
    currentId = res.value().id;
    loadSets();
}

void FlashcardSetEditorForm::onOpen(Object^, EventArgs^)
{
    int idx = setList->SelectedIndex;
    if (idx < 0) return;
    auto listRes = controller->listSets();
    if (!listRes || idx >= static_cast<int>(listRes.value().size())) return;
    auto s = listRes.value()[idx];
    if (!s.savedPath.empty()) {
        System::String^ p = gcnew System::String(s.savedPath.c_str());
        if (System::IO::File::Exists(p)) {
            std::string json = msclr::interop::marshal_as<std::string>(System::IO::File::ReadAllText(p));
            auto j = nlohmann::json::parse(json);
            std::vector<flashnotes::Flashcard> cards = j.get<std::vector<flashnotes::Flashcard>>();
            grid->Rows->Clear();
            for (auto& c : cards) grid->Rows->Add(gcnew String(c.front.c_str()), gcnew String(c.back.c_str()));
        }
    }
}

void FlashcardSetEditorForm::onUpdate(Object^, EventArgs^)
{
    if (currentId < 0) return;
    auto cards = collectCards(grid);
    std::string title = msclr::interop::marshal_as<std::string>(titleBox->Text);
    auto res = controller->updateSet(currentId, title, cards);
    if (!res) { MessageBox::Show(gcnew String(res.error().c_str())); return; }
    if (!res.value().savedPath.empty()) {
        nlohmann::json j = cards;
        System::IO::File::WriteAllText(gcnew String(res.value().savedPath.c_str()), gcnew String(j.dump(4).c_str()));
    }
    loadSets();
}

void FlashcardSetEditorForm::onDelete(Object^, EventArgs^)
{
    int idx = setList->SelectedIndex;
    if (idx < 0) return;
    auto listRes = controller->listSets();
    if (!listRes || idx >= static_cast<int>(listRes.value().size())) return;
    auto s = listRes.value()[idx];
    controller->removeSet(s.id);
    setList->ClearSelected();
    titleBox->Text="";
    grid->Rows->Clear();
    currentId = -1;
    loadSets();
}

} // namespace FlashnotesGUI
