#include "MainWindow.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

namespace FlashnotesGUI {

MainWindow::MainWindow(flashnotes::AppController* ctrl)
{
    controller = ctrl;
    Text = "Flashnotes \xE2\x80\x93 alpha"; // note: UTF-8 dash
    Width = 600;
    Height = 400;

    menu = gcnew MenuStrip();
    mainPanel = gcnew Panel();
    mainPanel->Dock = DockStyle::Fill;

    initMenu();
    Controls->Add(mainPanel);
    Controls->Add(menu);
}

MainWindow::~MainWindow() {}

void MainWindow::initMenu()
{
    auto notesItem = gcnew ToolStripMenuItem("Edit Notes");
    auto filesItem = gcnew ToolStripMenuItem("Organise Files");
    auto flashItem = gcnew ToolStripMenuItem("Practice Cards");
    auto setsItem  = gcnew ToolStripMenuItem("Edit Card Sets");
    notesItem->Click += gcnew EventHandler(this, &MainWindow::onEditNotes);
    filesItem->Click += gcnew EventHandler(this, &MainWindow::onOrganiseFiles);
    flashItem->Click += gcnew EventHandler(this, &MainWindow::onFlashcards);
    setsItem->Click  += gcnew EventHandler(this, &MainWindow::onEditSets);
    menu->Items->AddRange(gcnew cli::array<ToolStripItem^>{notesItem, filesItem, setsItem, flashItem});
}

void MainWindow::loadControl(UserControl^ c)
{
    mainPanel->Controls->Clear();
    c->Dock = DockStyle::Fill;
    mainPanel->Controls->Add(c);
}

void MainWindow::onEditNotes(Object^ sender, EventArgs^ e)
{
    if (!noteEditor)
        noteEditor = gcnew NoteEditorForm(&(controller->notes()));
    loadControl(noteEditor);
}

void MainWindow::onOrganiseFiles(Object^ sender, EventArgs^ e)
{
    if (!fileManager)
        fileManager = gcnew FileManagerForm(&(controller->files()));
    loadControl(fileManager);
}

void MainWindow::onFlashcards(Object^ sender, EventArgs^ e)
{
    if (!flashcardForm)
        flashcardForm = gcnew FlashcardPracticeForm(&(controller->flashcardSets()));
    loadControl(flashcardForm);
}

void MainWindow::onEditSets(Object^ sender, EventArgs^ e)
{
    if (!setEditor)
        setEditor = gcnew FlashcardSetEditorForm(&(controller->flashcardSets()));
    loadControl(setEditor);
}

} // namespace FlashnotesGUI
