#pragma once

#include <controllers/FlashcardController.hpp>

using namespace System;
using namespace System::Windows::Forms;

namespace FlashnotesGUI {

public ref class FlashcardPracticeForm : public UserControl
{
public:
    FlashcardPracticeForm(flashnotes::FlashcardController* ctrl);

private:
    flashnotes::FlashcardController* controller;
    Label^ lblFront;
    Label^ lblBack;
    Button^ btnFlip;
    Button^ btnNext;
    bool showingBack;

    void loadNext();
    void onFlip(Object^ sender, EventArgs^ e);
    void onNext(Object^ sender, EventArgs^ e);
};

} // namespace FlashnotesGUI
