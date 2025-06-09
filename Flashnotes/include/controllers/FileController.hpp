#pragma once
#include <memory>
#include <vector>
#include "domain/material.hpp"
#include "domain/folder.hpp"
#include "domain/folder_tree.hpp"
#include "services/FileService.hpp"
#include <filesystem>
#include <string>
#include "utils/Expected.hpp"

namespace flashnotes {

class FileController {
public:
    FileController();
    explicit FileController(std::shared_ptr<FileService> svc);

    Expected<Material> createFile(const std::filesystem::path& path, int folderId = -1);
    Expected<std::vector<Material>> listFiles() const;
    Expected<void> removeFile(std::uint64_t id);

    Expected<Folder> createFolder(const std::string& name, int parentId = -1);
    Expected<Folder> updateFolder(std::uint64_t id, const std::string& name);
    Expected<std::vector<Folder>> listFolders() const;
    Expected<void> removeFolder(std::uint64_t id);
    Expected<std::vector<FolderTree>> folderTree() const;

private:
    std::shared_ptr<FileService> service_;
};

} // namespace flashnotes
