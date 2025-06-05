#include "domain/note.hpp"

namespace flashnotes {

void to_json(nlohmann::json& j, const Note& n) {
    j = nlohmann::json{{"id", n.id}, {"title", n.title}, {"body", n.body}, {"savedPath", n.savedPath}};
}

void from_json(const nlohmann::json& j, Note& n) {
    j.at("id").get_to(n.id);
    j.at("title").get_to(n.title);
    j.at("body").get_to(n.body);
    j.at("savedPath").get_to(n.savedPath);
}

} // namespace flashnotes
