#include "domain/folder.hpp"

namespace flashnotes {

void to_json(nlohmann::json& j, const Folder& f) {
    j = nlohmann::json{{"id", f.id}, {"name", f.name}, {"childrenIds", f.childrenIds}};
}

void from_json(const nlohmann::json& j, Folder& f) {
    j.at("id").get_to(f.id);
    j.at("name").get_to(f.name);
    j.at("childrenIds").get_to(f.childrenIds);
}

} // namespace flashnotes
