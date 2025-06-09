#include "controllers/AppController.hpp"

namespace flashnotes {

AppController::AppController() = default;

NotesController& AppController::notes() { return notes_; }
FileController& AppController::files() { return files_; }
FlashcardController& AppController::flashcards() { return flashcards_; }
FlashcardSetController& AppController::flashcardSets() { return flashcardSets_; }

} // namespace flashnotes
