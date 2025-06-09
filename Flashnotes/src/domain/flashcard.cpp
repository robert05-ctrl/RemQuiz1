#include "domain/flashcard.hpp"
#include <stdexcept>

namespace flashnotes {

void to_json(nlohmann::json& j, const Flashcard& c) {
    j = nlohmann::json{{"id", c.id}, {"front", c.front}, {"back", c.back}, {"successRate", c.successRate}};
}

void from_json(const nlohmann::json& j, Flashcard& c) {
    // required keys validation
    if (!j.contains("id") || !j.contains("front") || !j.contains("back")) {
        throw std::runtime_error("Flashcard missing fields");
    }
    j.at("id").get_to(c.id);
    j.at("front").get_to(c.front);
    j.at("back").get_to(c.back);
    if (j.contains("successRate")) { // optional
        j.at("successRate").get_to(c.successRate);
    }
}

} // namespace flashnotes
