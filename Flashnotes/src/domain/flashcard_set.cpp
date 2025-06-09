#include "domain/flashcard_set.hpp"
#include <stdexcept>

namespace flashnotes {

void to_json(nlohmann::json& j, const FlashcardSet& s) {
    j = nlohmann::json{{"id", s.id}, {"title", s.title}, {"cards", s.cards}, {"savedPath", s.savedPath}};
}

void from_json(const nlohmann::json& j, FlashcardSet& s) {
    // validate required keys before accessing
    if (!j.contains("id") || !j.contains("title") ||
        !j.contains("cards") || !j.contains("savedPath")) {
        throw std::runtime_error("FlashcardSet missing fields");
    }
    j.at("id").get_to(s.id);
    j.at("title").get_to(s.title);
    j.at("cards").get_to(s.cards);
    j.at("savedPath").get_to(s.savedPath);
}

} // namespace flashnotes
