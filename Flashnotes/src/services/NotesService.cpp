#include "services/NotesService.hpp"

namespace flashnotes {

NotesService::NotesService() { syncFromDisk(); }

int NotesService::nextId() const {
    int id = 0;
    for (const auto& n : cache_) if (n.id > id) id = n.id;
    return id + 1;
}

Note NotesService::create(const std::string& title,
                          const std::string& body,
                          const std::filesystem::path& savePath) {
    Note n{nextId(), title, body, savePath.string()};
    cache_.push_back(n);
    syncToDisk();
    return n;
}

std::vector<Note> NotesService::list() const {
    return cache_;
}

void NotesService::remove(std::uint64_t id) {
    cache_.erase(std::remove_if(cache_.begin(), cache_.end(),
                 [id](const Note& n){ return static_cast<std::uint64_t>(n.id)==id; }),
                 cache_.end());
    syncToDisk();
}

void NotesService::syncFromDisk() {
    cache_ = JsonPersistenceService::loadNotes();
}

void NotesService::syncToDisk() const {
    JsonPersistenceService::saveNotes(cache_);
}

} // namespace flashnotes
