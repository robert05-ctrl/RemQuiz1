#pragma once
#include <vector>
#include <filesystem>
#include "domain/note.hpp"
#include "services/JsonPersistenceService.hpp"

namespace flashnotes {

class NotesService {
public:
    NotesService();

    Note create(const std::string& title,
                const std::string& body,
                const std::filesystem::path& savePath);

    Note update(std::uint64_t id,
                const std::string& title,
                const std::string& body);

    std::vector<Note> list() const;
    void remove(std::uint64_t id);

private:
    std::vector<Note> cache_;
    int nextId() const;
    void syncFromDisk();
    void syncToDisk() const;
};

} // namespace flashnotes
