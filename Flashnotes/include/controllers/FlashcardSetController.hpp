#pragma once
#include <memory>
#include <filesystem>
#include <vector>
#include "domain/flashcard_set.hpp"
#include "services/FlashcardSetService.hpp"
#include "utils/Expected.hpp"

namespace flashnotes {

class FlashcardSetController {
public:
    FlashcardSetController();
    explicit FlashcardSetController(std::shared_ptr<FlashcardSetService> svc);

    Expected<FlashcardSet> createSet(const std::string& title,
                                     const std::vector<Flashcard>& cards,
                                     const std::filesystem::path& savePath);

    Expected<FlashcardSet> updateSet(std::uint64_t id,
                                     const std::string& title,
                                     const std::vector<Flashcard>& cards);

    Expected<std::vector<FlashcardSet>> listSets() const;
    Expected<void> removeSet(std::uint64_t id);

private:
    std::shared_ptr<FlashcardSetService> service_;
};

} // namespace flashnotes
