#include "services/NotesService.hpp"
#include <filesystem>

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

Note NotesService::update(std::uint64_t id,
                          const std::string& title,
                          const std::string& body) {
    for (auto& n : cache_) {
        if (static_cast<std::uint64_t>(n.id) == id) {
            n.title = title;
            n.body  = body;
            syncToDisk();
            return n;
        }
    }
    throw std::runtime_error("Note not found");
}

std::vector<Note> NotesService::list() const {
    return cache_;
}

void NotesService::remove(std::uint64_t id) {
    namespace fs = std::filesystem;
    cache_.erase(std::remove_if(cache_.begin(), cache_.end(),
                 [id](const Note& n){
                     if (static_cast<std::uint64_t>(n.id) == id) {
                         if (!n.savedPath.empty()) {
                             fs::path p(n.savedPath);
                             if (fs::is_regular_file(p)) {
                                 fs::remove(p);
                             }
                         }
                         return true;
                     }
                     return false;
                 }),
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
