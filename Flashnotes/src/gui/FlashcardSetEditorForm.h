#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <controllers/FlashcardSetController.hpp>

namespace FlashnotesGUI {
using namespace System;
using namespace System::Windows::Forms;

public ref class FlashcardSetEditorForm : public UserControl
{
public:
    FlashcardSetEditorForm(flashnotes::FlashcardSetController* ctrl);

private:
    flashnotes::FlashcardSetController* controller;
    ListBox^ setList;
    TextBox^ titleBox;
    DataGridView^ grid;
    Button^ btnSave;
    Button^ btnOpen;
    Button^ btnNew;
    Button^ btnUpdate;
    Button^ btnDelete;
    Button^ btnAddCard;
    Button^ btnRemoveCard;
    int currentId;

    void loadSets();
    void onSelect(Object^ sender, EventArgs^ e);
    void onSave(Object^ sender, EventArgs^ e);
    void onOpen(Object^ sender, EventArgs^ e);
    void onNew(Object^ sender, EventArgs^ e);
    void onUpdate(Object^ sender, EventArgs^ e);
    void onDelete(Object^ sender, EventArgs^ e);
    void onAddCard(Object^ sender, EventArgs^ e);
    void onRemoveCard(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
