#ifndef FLASHNOTES_DOMAIN_MATERIAL_HPP
#define FLASHNOTES_DOMAIN_MATERIAL_HPP

#include <nlohmann/json.hpp>

namespace flashnotes {

struct Material {
    int id{};
};

inline void to_json(nlohmann::json& j, const Material& m) { j = nlohmann::json{{"id", m.id}}; }
inline void from_json(const nlohmann::json& j, Material& m) { j.at("id").get_to(m.id); }

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_MATERIAL_HPP
