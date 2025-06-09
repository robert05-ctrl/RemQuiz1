#ifndef FLASHNOTES_DOMAIN_MATERIAL_HPP
#define FLASHNOTES_DOMAIN_MATERIAL_HPP

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace flashnotes {

struct Material {
    int id{};
    std::string title;
    std::string path;
    int folderId{-1};
};

inline void to_json(nlohmann::json& j, const Material& m) {
    j = nlohmann::json{{"id", m.id}, {"title", m.title}, {"path", m.path}, {"folderId", m.folderId}};
}

inline void from_json(const nlohmann::json& j, Material& m) {
    // ensure required keys exist before access
    if (!j.contains("id") || !j.contains("title") ||
        !j.contains("path") || !j.contains("folderId")) {
        throw std::runtime_error("Material missing fields");
    }
    j.at("id").get_to(m.id);
    j.at("title").get_to(m.title);
    j.at("path").get_to(m.path);
    j.at("folderId").get_to(m.folderId);
}

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_MATERIAL_HPP
