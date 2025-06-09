#pragma once
#include "controllers/NotesController.hpp"
#include "controllers/FileController.hpp"
#include "controllers/FlashcardController.hpp"
#include "controllers/FlashcardSetController.hpp"

namespace flashnotes {

class AppController {
public:
    AppController();

    NotesController& notes();
    FileController& files();
    FlashcardController& flashcards();
    FlashcardSetController& flashcardSets();

private:
    NotesController notes_;
    FileController files_;
    FlashcardController flashcards_;
    FlashcardSetController flashcardSets_;
};

} // namespace flashnotes
