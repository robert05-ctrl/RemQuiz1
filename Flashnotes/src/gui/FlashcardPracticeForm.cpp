#include "FlashcardPracticeForm.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include <msclr/marshal_cppstd.h>


namespace FlashnotesGUI {

FlashcardPracticeForm::FlashcardPracticeForm(flashnotes::FlashcardController* ctrl)
    : showingBack(false)
{
    controller = ctrl;
    Dock = DockStyle::Fill;

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

    loadNext();
}

void FlashcardPracticeForm::loadNext()
{
    auto res = controller->getNextCards(1);
    if (!res || res.value().empty()) {
        lblFront->Text = "No cards";
        lblBack->Text = "";
        lblBack->Visible = false;
    } else {
        auto& c = res.value().front();
        lblFront->Text = gcnew String(c.front.c_str());
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

} // namespace FlashnotesGUI
