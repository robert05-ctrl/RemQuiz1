#ifndef FLASHNOTES_DOMAIN_FLASHCARD_HPP
#define FLASHNOTES_DOMAIN_FLASHCARD_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace flashnotes {

struct Flashcard {
    int id{};
    std::string front;
    std::string back;
    double successRate{0.5};
};

void to_json(nlohmann::json& j, const Flashcard& c);
void from_json(const nlohmann::json& j, Flashcard& c);

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_FLASHCARD_HPP
