#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "NoteEditorForm.h"
#include "FileManagerForm.h"
#include "FlashcardPracticeForm.h"
#include "FlashcardSetEditorForm.h"
#include <controllers/AppController.hpp>

namespace FlashnotesGUI {
using namespace System;
using namespace System::Windows::Forms;

public ref class MainWindow : public Form
{
public:
    MainWindow(flashnotes::AppController* ctrl);

protected:
    ~MainWindow();

private:
    flashnotes::AppController* controller;
    MenuStrip^ menu;
    Panel^ mainPanel;
    NoteEditorForm^ noteEditor;
    FileManagerForm^ fileManager;
    FlashcardPracticeForm^ flashcardForm;
    FlashcardSetEditorForm^ setEditor;

    void initMenu();
    void loadControl(UserControl^ c);
    void onEditNotes(Object^ sender, EventArgs^ e);
    void onOrganiseFiles(Object^ sender, EventArgs^ e);
    void onFlashcards(Object^ sender, EventArgs^ e);
    void onEditSets(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
