#pragma once
#include <vector>
#include <filesystem>
#include "domain/flashcard_set.hpp"
#include "services/JsonPersistenceService.hpp"

namespace flashnotes {

class FlashcardSetService {
public:
    FlashcardSetService();

    FlashcardSet create(const std::string& title,
                        const std::vector<Flashcard>& cards,
                        const std::filesystem::path& savePath);

    FlashcardSet update(std::uint64_t id,
                        const std::string& title,
                        const std::vector<Flashcard>& cards);

    std::vector<FlashcardSet> list() const;
    void remove(std::uint64_t id);

private:
    std::vector<FlashcardSet> cache_;
    int nextId() const;
    void syncFromDisk();
    void syncToDisk() const;
};

} // namespace flashnotes
