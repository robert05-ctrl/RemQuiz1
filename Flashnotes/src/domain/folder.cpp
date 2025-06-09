#include "domain/folder.hpp"

namespace flashnotes {

void to_json(nlohmann::json& j, const Folder& f) {
    j = nlohmann::json{{"id", f.id}, {"parentId", f.parentId}, {"name", f.name}};
}

void from_json(const nlohmann::json& j, Folder& f) {
    j.at("id").get_to(f.id);
    j.at("parentId").get_to(f.parentId);
    j.at("name").get_to(f.name);
}

} // namespace flashnotes
