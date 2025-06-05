#include "services/FlashcardService.hpp"
#include <algorithm>

namespace flashnotes {

FlashcardService::FlashcardService() { syncFromDisk(); }

int FlashcardService::nextId() const {
    int id = 0;
    for (const auto& c : cache_) if (c.id > id) id = c.id;
    return id + 1;
}

Flashcard FlashcardService::create(const std::string& front,
                                   const std::string& back) {
    Flashcard c{nextId(), front, back};
    cache_.push_back(c);
    syncToDisk();
    return c;
}

std::vector<Flashcard> FlashcardService::list() const {
    return cache_;
}

void FlashcardService::remove(std::uint64_t id) {
    cache_.erase(std::remove_if(cache_.begin(), cache_.end(),
                 [id](const Flashcard& c){ return static_cast<std::uint64_t>(c.id)==id; }),
                 cache_.end());
    syncToDisk();
}

std::vector<Flashcard> FlashcardService::getNextCards(std::size_t n) const {
    std::vector<Flashcard> result;
    for (std::size_t i = 0; i < n && i < cache_.size(); ++i) {
        result.push_back(cache_[i]);
    }
    return result;
}

void FlashcardService::syncFromDisk() {
    cache_ = JsonPersistenceService::loadFlashcards();
}

void FlashcardService::syncToDisk() const {
    JsonPersistenceService::saveFlashcards(cache_);
}

} // namespace flashnotes
