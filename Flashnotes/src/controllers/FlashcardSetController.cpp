#include "controllers/FlashcardSetController.hpp"

namespace flashnotes {

FlashcardSetController::FlashcardSetController()
    : service_(std::make_shared<FlashcardSetService>()) {}

FlashcardSetController::FlashcardSetController(std::shared_ptr<FlashcardSetService> svc)
    : service_(std::move(svc)) {}

Expected<FlashcardSet> FlashcardSetController::createSet(const std::string& title,
                                                         const std::vector<Flashcard>& cards,
                                                         const std::filesystem::path& savePath) {
    if (title.empty()) {
        return Expected<FlashcardSet>("Title must not be empty");
    }
    try {
        return service_->create(title, cards, savePath);
    } catch (const std::exception& e) {
        return Expected<FlashcardSet>(e.what());
    }
}

Expected<FlashcardSet> FlashcardSetController::updateSet(std::uint64_t id,
                                                         const std::string& title,
                                                         const std::vector<Flashcard>& cards) {
    if (title.empty()) return Expected<FlashcardSet>("Title must not be empty");
    try {
        return service_->update(id, title, cards);
    } catch (const std::exception& e) {
        return Expected<FlashcardSet>(e.what());
    }
}

Expected<std::vector<FlashcardSet>> FlashcardSetController::listSets() const {
    try {
        return service_->list();
    } catch (const std::exception& e) {
        return Expected<std::vector<FlashcardSet>>(e.what());
    }
}

Expected<void> FlashcardSetController::removeSet(std::uint64_t id) {
    try {
        service_->remove(id);
        return Expected<void>();
    } catch (const std::exception& e) {
        return Expected<void>(e.what());
    }
}

} // namespace flashnotes
