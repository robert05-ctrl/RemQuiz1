#ifndef FLASHNOTES_DOMAIN_FLASHCARD_SET_HPP
#define FLASHNOTES_DOMAIN_FLASHCARD_SET_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "flashcard.hpp"

namespace flashnotes {

struct FlashcardSet {
    int id{};
    std::string title;
    std::vector<Flashcard> cards;
    std::string savedPath;
};

void to_json(nlohmann::json& j, const FlashcardSet& s);
void from_json(const nlohmann::json& j, FlashcardSet& s);

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_FLASHCARD_SET_HPP
