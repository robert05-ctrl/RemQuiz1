#ifndef FLASHNOTES_DOMAIN_NOTE_HPP
#define FLASHNOTES_DOMAIN_NOTE_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace flashnotes {

struct Note {
    int id{};
    std::string title;
    std::string body;
    std::string savedPath;
};

void to_json(nlohmann::json& j, const Note& n);
void from_json(const nlohmann::json& j, Note& n);

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_NOTE_HPP
