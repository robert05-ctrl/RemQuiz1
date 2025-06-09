#ifndef FLASHNOTES_DOMAIN_FOLDER_TREE_HPP
#define FLASHNOTES_DOMAIN_FOLDER_TREE_HPP

#include "domain/folder.hpp"
#include "domain/material.hpp"
#include <vector>

namespace flashnotes {

struct FolderTree {
    Folder folder;
    std::vector<Material> files;
    std::vector<FolderTree> subfolders;
};

} // namespace flashnotes

#endif // FLASHNOTES_DOMAIN_FOLDER_TREE_HPP
