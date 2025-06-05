#pragma once
#include <vector>
#include <filesystem>
#include "domain/material.hpp"
#include "services/JsonPersistenceService.hpp"

namespace flashnotes {

class FileService {
public:
    FileService();
    Material create();
    std::vector<Material> list() const;
    void remove(std::uint64_t id);

private:
    std::vector<Material> cache_;
    int nextId() const;
    void syncFromDisk();
    void syncToDisk() const;
};

} // namespace flashnotes
