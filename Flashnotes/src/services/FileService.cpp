#include "services/FileService.hpp"
#include <algorithm>
#include <filesystem>
#include <stdexcept>
#include <functional>

namespace flashnotes {

FileService::FileService() { syncFromDisk(); }

int FileService::nextId() const {
    int id = 0;
    for (const auto& m : cache_) if (m.id > id) id = m.id;
    return id + 1;
}

int FileService::nextFolderId() const {
    int id = 0;
    for (const auto& f : folders_) if (f.id > id) id = f.id;
    return id + 1;
}

Material FileService::create(const std::filesystem::path& path, int folderId) {
    Material m{nextId(), path.filename().string(), path.string(), folderId};
    cache_.push_back(m);
    syncToDisk();
    return m;
}

std::vector<Material> FileService::list() const {
    return cache_;
}

void FileService::remove(std::uint64_t id) {
    cache_.erase(std::remove_if(cache_.begin(), cache_.end(),
                 [id](const Material& m){ return static_cast<std::uint64_t>(m.id)==id; }),
                 cache_.end());
    syncToDisk();
}

Folder FileService::createFolder(const std::string& name, int parentId) {
    Folder f{nextFolderId(), parentId, name};
    folders_.push_back(f);
    syncToDisk();
    return f;
}

Folder FileService::updateFolder(std::uint64_t id, const std::string& name) {
    for (auto& f : folders_) {
        if (static_cast<std::uint64_t>(f.id) == id) {
            f.name = name;
            syncToDisk();
            return f;
        }
    }
    throw std::runtime_error("Folder not found");
}

std::vector<Folder> FileService::listFolders() const { return folders_; }

void FileService::removeFolder(std::uint64_t id) {
    folders_.erase(std::remove_if(folders_.begin(), folders_.end(),
                                 [id](const Folder& f){return static_cast<std::uint64_t>(f.id)==id;}),
                   folders_.end());
    for (auto& m : cache_) if (m.folderId == static_cast<int>(id)) m.folderId = -1;
    syncToDisk();
}

std::vector<FolderTree> FileService::folderTree() const {
    std::vector<FolderTree> roots;
    // helper lambda to recursively build tree
    std::function<FolderTree(const Folder&)> build = [&](const Folder& f) {
        FolderTree node{f};
        for (const auto& m : cache_) {
            if (m.folderId == f.id) node.files.push_back(m);
        }
        for (const auto& child : folders_) {
            if (child.parentId == f.id) {
                node.subfolders.push_back(build(child));
            }
        }
        return node;
    };

    for (const auto& f : folders_) {
        if (f.parentId == -1) {
            roots.push_back(build(f));
        }
    }
    // files not in any folder
    FolderTree rootDummy{Folder{-1, -1, ""}};
    for (const auto& m : cache_) {
        if (m.folderId == -1) rootDummy.files.push_back(m);
    }
    if (!rootDummy.files.empty()) roots.push_back(rootDummy);
    return roots;
}

void FileService::syncFromDisk() {
    cache_ = JsonPersistenceService::loadMaterials();
    folders_ = JsonPersistenceService::loadFolders();
}

void FileService::syncToDisk() const {
    JsonPersistenceService::saveMaterials(cache_);
    JsonPersistenceService::saveFolders(folders_);
}

} // namespace flashnotes
