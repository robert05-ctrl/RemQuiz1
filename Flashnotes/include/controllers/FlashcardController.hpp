#pragma once
#include <memory>
#include <vector>
#include "domain/flashcard.hpp"
#include "services/FlashcardService.hpp"
#include "utils/Expected.hpp"

namespace flashnotes {

class FlashcardController {
public:
    FlashcardController();
    explicit FlashcardController(std::shared_ptr<FlashcardService> svc);

    Expected<Flashcard> createFlashcard(const std::string& front,
                                        const std::string& back);
    Expected<std::vector<Flashcard>> listFlashcards() const;
    Expected<void> removeFlashcard(std::uint64_t id);
    Expected<std::vector<Flashcard>> getNextCards(std::size_t n) const;

private:
    std::shared_ptr<FlashcardService> service_;
};

} // namespace flashnotes
