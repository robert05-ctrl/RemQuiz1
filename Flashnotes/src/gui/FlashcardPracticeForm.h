#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <controllers/FlashcardSetController.hpp>

namespace FlashnotesGUI {
using namespace System;
using namespace System::Windows::Forms;

public ref class FlashcardPracticeForm : public UserControl
{
public:
    FlashcardPracticeForm(flashnotes::FlashcardSetController* ctrl);
    ~FlashcardPracticeForm();

private:
    flashnotes::FlashcardSetController* controller;
    ListBox^ setList;
    Label^ lblFront;
    Label^ lblBack;
    Button^ btnFlip;
    Button^ btnNext;
    bool showingBack;
    int currentIndex;
    std::vector<flashnotes::Flashcard>* cards;

    void loadSets();
    void onSelect(Object^ sender, EventArgs^ e);
    void loadNext();
    void onFlip(Object^ sender, EventArgs^ e);
    void onNext(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
