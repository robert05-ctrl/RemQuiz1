#pragma once
#include <vector>
#include <filesystem>
#include "domain/flashcard.hpp"
#include "services/JsonPersistenceService.hpp"

namespace flashnotes {

class FlashcardService {
public:
    FlashcardService();
    Flashcard create(const std::string& front,
                     const std::string& back);
    std::vector<Flashcard> list() const;
    void remove(std::uint64_t id);
    std::vector<Flashcard> getNextCards(std::size_t n) const;

private:
    std::vector<Flashcard> cache_;
    int nextId() const;
    void syncFromDisk();
    void syncToDisk() const;
};

} // namespace flashnotes
