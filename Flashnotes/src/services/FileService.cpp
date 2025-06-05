#include "services/FileService.hpp"
#include <algorithm>

namespace flashnotes {

FileService::FileService() { syncFromDisk(); }

int FileService::nextId() const {
    int id = 0;
    for (const auto& m : cache_) if (m.id > id) id = m.id;
    return id + 1;
}

Material FileService::create() {
    Material m{nextId()};
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

void FileService::syncFromDisk() {
    cache_ = JsonPersistenceService::loadMaterials();
}

void FileService::syncToDisk() const {
    JsonPersistenceService::saveMaterials(cache_);
}

} // namespace flashnotes
