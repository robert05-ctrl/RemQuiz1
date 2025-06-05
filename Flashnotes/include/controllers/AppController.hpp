#pragma once
#include "controllers/NotesController.hpp"
#include "controllers/FileController.hpp"
#include "controllers/FlashcardController.hpp"

namespace flashnotes {

class AppController {
public:
    AppController();

    NotesController& notes();
    FileController& files();
    FlashcardController& flashcards();

private:
    NotesController notes_;
    FileController files_;
    FlashcardController flashcards_;
};

} // namespace flashnotes
