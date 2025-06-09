#include "FlashcardPracticeForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>
#include <vector>

using namespace System::Drawing; // for ContentAlignment

namespace FlashnotesGUI {

FlashcardPracticeForm::FlashcardPracticeForm(flashnotes::FlashcardSetController* ctrl)
    : showingBack(false), currentIndex(0)
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

    btnFlip = gcnew Button();
    btnFlip->Text = "Flip";
    btnFlip->Dock = DockStyle::Top;
    btnFlip->Click += gcnew EventHandler(this, &FlashcardPracticeForm::onFlip);

    btnNext = gcnew Button();
    btnNext->Text = "Next";
    btnNext->Dock = DockStyle::Top;
    btnNext->Click += gcnew EventHandler(this, &FlashcardPracticeForm::onNext);

    Controls->Add(btnNext);
    Controls->Add(btnFlip);
    Controls->Add(lblBack);
    Controls->Add(lblFront);
    Controls->Add(setList);

    loadSets();
}

FlashcardPracticeForm::~FlashcardPracticeForm() {
    delete cards;
}

void FlashcardPracticeForm::loadSets()
{
    setList->Items->Clear();
    auto res = controller->listSets();
    if (!res) { lblFront->Text = "Error"; return; }
    for (auto& s : res.value()) setList->Items->Add(gcnew String(s.title.c_str()));
    cards->clear();
    if (setList->Items->Count > 0) setList->SelectedIndex = 0;
}

void FlashcardPracticeForm::onSelect(Object^, EventArgs^)
{
    int idx = setList->SelectedIndex;
    auto res = controller->listSets();
    if (!res || idx < 0 || idx >= static_cast<int>(res.value().size())) { cards->clear(); return; }
    auto s = res.value()[idx];
    *cards = s.cards;
    currentIndex = 0;
    loadNext();
}

void FlashcardPracticeForm::loadNext()
{
    if (cards->empty()) { lblFront->Text = "No cards"; lblBack->Visible=false; return; }
    if (currentIndex >= static_cast<int>(cards->size())) currentIndex = 0;
    auto& c = (*cards)[currentIndex++];
    lblFront->Text = gcnew String(c.front.c_str());
    lblBack->Text = gcnew String(c.back.c_str());
    lblBack->Visible = false;
    showingBack = false;
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

} // namespace FlashnotesGUI
