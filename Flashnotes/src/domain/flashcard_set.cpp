#include "domain/flashcard_set.hpp"

namespace flashnotes {

void to_json(nlohmann::json& j, const FlashcardSet& s) {
    j = nlohmann::json{{"id", s.id}, {"title", s.title}, {"cards", s.cards}, {"savedPath", s.savedPath}};
}

void from_json(const nlohmann::json& j, FlashcardSet& s) {
    j.at("id").get_to(s.id);
    j.at("title").get_to(s.title);
    j.at("cards").get_to(s.cards);
    j.at("savedPath").get_to(s.savedPath);
}

} // namespace flashnotes
