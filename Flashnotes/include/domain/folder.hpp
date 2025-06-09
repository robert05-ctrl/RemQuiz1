#ifndef FLASHNOTES_DOMAIN_FOLDER_HPP
#define FLASHNOTES_DOMAIN_FOLDER_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace flashnotes {

struct Folder {
    int id{};
    int parentId{-1};
    std::string name;
};

void to_json(nlohmann::json& j, const Folder& f);
void from_json(const nlohmann::json& j, Folder& f);

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_FOLDER_HPP
