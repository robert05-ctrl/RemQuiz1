#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include <controllers/FlashcardSetController.hpp>
#include <string>

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
    Button^ btnCheck;
    TextBox^ answerBox;
    ComboBox^ modeBox;
    Label^ lblResult;
    bool showingBack;
    int currentIndex;
    bool hasSet;
    int currentId;
    std::string* currentTitle;
    std::vector<flashnotes::Flashcard>* cards;

    void loadSets();
    void onSelect(Object^ sender, EventArgs^ e);
    void loadNext();
    void onFlip(Object^ sender, EventArgs^ e);
    void onNext(Object^ sender, EventArgs^ e);
    void onCheck(Object^ sender, EventArgs^ e);
    void onModeChanged(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
