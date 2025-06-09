#include "FlashcardPracticeForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <algorithm>

using namespace System::Drawing; // for ContentAlignment

namespace FlashnotesGUI {

namespace {
bool compareSuccess(const flashnotes::Flashcard& a, const flashnotes::Flashcard& b)
{
    return a.successRate < b.successRate;
}
} // namespace

FlashcardPracticeForm::FlashcardPracticeForm(flashnotes::FlashcardSetController* ctrl)
    : showingBack(false), currentIndex(0), hasSet(false), currentId(-1), currentTitle(nullptr)
{
    controller = ctrl;
    cards = new std::vector<flashnotes::Flashcard>();
    Dock = DockStyle::Fill;

    setList = gcnew ListBox();
    setList->Dock = DockStyle::Left;
    setList->Width = 150;
    setList->SelectedIndexChanged += gcnew EventHandler(this, &FlashcardPracticeForm::onSelect);

    lblFront = gcnew Label();
    lblFront->Dock = DockStyle::Top;
    lblFront->Height = 40;
    lblFront->TextAlign = ContentAlignment::MiddleCenter;

    lblBack = gcnew Label();
    lblBack->Dock = DockStyle::Top;
    lblBack->Height = 40;
    lblBack->Visible = false;
    lblBack->TextAlign = ContentAlignment::MiddleCenter;

    modeBox = gcnew ComboBox();
    modeBox->Dock = DockStyle::Top;
    modeBox->Items->Add("Flip");
    modeBox->Items->Add("Type");
    modeBox->SelectedIndex = 0;
    modeBox->SelectedIndexChanged += gcnew EventHandler(this, &FlashcardPracticeForm::onModeChanged);

    answerBox = gcnew TextBox();
    answerBox->Dock = DockStyle::Top;
    answerBox->Visible = false;

    btnCheck = gcnew Button();
    btnCheck->Text = "Check";
    btnCheck->Dock = DockStyle::Top;
    btnCheck->Visible = false;
    btnCheck->Click += gcnew EventHandler(this, &FlashcardPracticeForm::onCheck);

    lblResult = gcnew Label();
    lblResult->Dock = DockStyle::Top;
    lblResult->Height = 30;
    lblResult->Visible = false;
    lblResult->TextAlign = ContentAlignment::MiddleCenter;

    btnFlip = gcnew Button();
    btnFlip->Text = "Flip";
    btnFlip->Dock = DockStyle::Top;
    btnFlip->Click += gcnew EventHandler(this, &FlashcardPracticeForm::onFlip);

    btnNext = gcnew Button();
    btnNext->Text = "Next";
    btnNext->Dock = DockStyle::Top;
    btnNext->Click += gcnew EventHandler(this, &FlashcardPracticeForm::onNext);

    Controls->Add(btnNext);
    Controls->Add(btnCheck);
    Controls->Add(btnFlip);
    Controls->Add(lblResult);
    Controls->Add(answerBox);
    Controls->Add(lblBack);
    Controls->Add(lblFront);
    Controls->Add(modeBox);
    Controls->Add(setList);

    loadSets();
}

FlashcardPracticeForm::~FlashcardPracticeForm() {
    delete cards;
    if (currentTitle) {
        delete currentTitle;
        currentTitle = nullptr;
    }
}

void FlashcardPracticeForm::loadSets()
{
    setList->Items->Clear();
    auto res = controller->listSets();
    if (!res) { lblFront->Text = "Error"; return; }
    for (auto& s : res.value()) setList->Items->Add(gcnew String(s.title.c_str()));
    cards->clear();
    currentId = -1;
    if (currentTitle) { delete currentTitle; currentTitle = nullptr; }
    if (setList->Items->Count > 0) setList->SelectedIndex = 0;
}

void FlashcardPracticeForm::onSelect(Object^, EventArgs^)
{
    int idx = setList->SelectedIndex;
    auto res = controller->listSets();
    if (!res || idx < 0 || idx >= static_cast<int>(res.value().size())) {
        cards->clear();
        hasSet = false;
        currentId = -1;
        if (currentTitle) { delete currentTitle; currentTitle = nullptr; }
        return;
    }
    auto s = res.value()[idx];
    if (currentTitle) { delete currentTitle; }
    currentTitle = new std::string(s.title);
    currentId = s.id;
    hasSet = true;
    *cards = s.cards;
    currentIndex = 0;
    loadNext();
}

void FlashcardPracticeForm::loadNext()
{
    if (cards->empty()) {
        lblFront->Text = "No cards";
        lblBack->Visible = false;
        answerBox->Visible = false;
        btnCheck->Visible = false;
        lblResult->Visible = false;
        return;
    }
    bool typeMode = modeBox->SelectedIndex == 1;
    if (typeMode) {
        std::sort(cards->begin(), cards->end(), compareSuccess);
    }
    if (currentIndex >= static_cast<int>(cards->size())) currentIndex = 0;
    auto& c = (*cards)[currentIndex++];
    lblFront->Text = gcnew String(c.front.c_str());
    if (typeMode) {
        answerBox->Text = "";
        answerBox->Visible = true;
        btnCheck->Visible = true;
        lblBack->Visible = false;
        lblResult->Visible = false;
    } else {
        lblBack->Text = gcnew String(c.back.c_str());
        lblBack->Visible = false;
        showingBack = false;
    }
}

void FlashcardPracticeForm::onFlip(Object^ sender, EventArgs^ e)
{
    showingBack = !showingBack;
    lblBack->Visible = showingBack;
}

void FlashcardPracticeForm::onNext(Object^ sender, EventArgs^ e)
{
    loadNext();
}

void FlashcardPracticeForm::onCheck(Object^ sender, EventArgs^ e)
{
    if (cards->empty()) return;
    int idx = currentIndex - 1;
    if (idx < 0 || idx >= static_cast<int>(cards->size())) return;
    auto& c = (*cards)[idx];
    std::string ans = msclr::interop::marshal_as<std::string>(answerBox->Text);
    bool correct = ans == c.back;
    lblResult->Text = correct ? "Correct" : "Oops";
    lblResult->Visible = true;
    c.successRate = (c.successRate + (correct ? 1.0 : 0.0)) / 2.0;
    if (hasSet && currentTitle) {
        controller->updateSet(currentId, *currentTitle, *cards);
    }
}

void FlashcardPracticeForm::onModeChanged(Object^, EventArgs^)
{
    showingBack = false;
    currentIndex = 0;
    loadNext();
}

} // namespace FlashnotesGUI
