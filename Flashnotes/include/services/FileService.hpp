#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include "domain/material.hpp"
#include "domain/folder.hpp"
#include "services/JsonPersistenceService.hpp"

namespace flashnotes {

class FileService {
public:
    FileService();
    Material create(const std::filesystem::path& path, int folderId = -1);
    std::vector<Material> list() const;
    void remove(std::uint64_t id);

    Folder createFolder(const std::string& name, int parentId = -1);
    Folder updateFolder(std::uint64_t id, const std::string& name);
    std::vector<Folder> listFolders() const;
    void removeFolder(std::uint64_t id);

private:
    std::vector<Material> cache_;
    std::vector<Folder> folders_;
    int nextId() const;
    int nextFolderId() const;
    void syncFromDisk();
    void syncToDisk() const;
};

} // namespace flashnotes
