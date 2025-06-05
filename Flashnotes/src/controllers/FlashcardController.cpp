#include "controllers/FlashcardController.hpp"

namespace flashnotes {

FlashcardController::FlashcardController()
    : service_(std::make_shared<FlashcardService>()) {}

FlashcardController::FlashcardController(std::shared_ptr<FlashcardService> svc)
    : service_(std::move(svc)) {}

Expected<Flashcard> FlashcardController::createFlashcard(const std::string& front,
                                                         const std::string& back) {
    if (front.empty()) {
        return Expected<Flashcard>("Front must not be empty");
    }
    try {
        return service_->create(front, back);
    } catch (const std::exception& e) {
        return Expected<Flashcard>(e.what());
    }
}

Expected<std::vector<Flashcard>> FlashcardController::listFlashcards() const {
    try {
        return service_->list();
    } catch (const std::exception& e) {
        return Expected<std::vector<Flashcard>>(e.what());
    }
}

Expected<void> FlashcardController::removeFlashcard(std::uint64_t id) {
    try {
        service_->remove(id);
        return Expected<void>();
    } catch (const std::exception& e) {
        return Expected<void>(e.what());
    }
}

Expected<std::vector<Flashcard>> FlashcardController::getNextCards(std::size_t n) const {
    try {
        return service_->getNextCards(n);
    } catch (const std::exception& e) {
        return Expected<std::vector<Flashcard>>(e.what());
    }
}

} // namespace flashnotes
