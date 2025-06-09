#include "services/FlashcardSetService.hpp"
#include <algorithm>
#include <filesystem>

namespace flashnotes {

FlashcardSetService::FlashcardSetService() { syncFromDisk(); }

int FlashcardSetService::nextId() const {
    int id = 0;
    for (const auto& s : cache_) if (s.id > id) id = s.id;
    return id + 1;
}

FlashcardSet FlashcardSetService::create(const std::string& title,
                                         const std::vector<Flashcard>& cards,
                                         const std::filesystem::path& savePath) {
    FlashcardSet s{nextId(), title, cards, savePath.string()};
    cache_.push_back(s);
    syncToDisk();
    return s;
}

FlashcardSet FlashcardSetService::update(std::uint64_t id,
                                         const std::string& title,
                                         const std::vector<Flashcard>& cards) {
    for (auto& s : cache_) {
        if (static_cast<std::uint64_t>(s.id) == id) {
            s.title = title;
            s.cards = cards;
            syncToDisk();
            return s;
        }
    }
    throw std::runtime_error("Set not found");
}

std::vector<FlashcardSet> FlashcardSetService::list() const {
    return cache_;
}

void FlashcardSetService::remove(std::uint64_t id) {
    namespace fs = std::filesystem;
    cache_.erase(std::remove_if(cache_.begin(), cache_.end(),
                 [id](const FlashcardSet& s){
                     if (static_cast<std::uint64_t>(s.id)==id) {
                         if (!s.savedPath.empty()) {
                             fs::path p(s.savedPath);
                             if (fs::is_regular_file(p)) fs::remove(p);
                         }
                         return true;
                     }
                     return false;
                 }), cache_.end());
    syncToDisk();
}

void FlashcardSetService::syncFromDisk() {
    cache_ = JsonPersistenceService::loadFlashcardSets();
}

void FlashcardSetService::syncToDisk() const {
    JsonPersistenceService::saveFlashcardSets(cache_);
}

} // namespace flashnotes
