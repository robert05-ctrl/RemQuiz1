#include "services/JsonPersistenceService.hpp"
#include "domain/material.hpp"

namespace flashnotes {

namespace fs = std::filesystem;

static fs::path g_root;

const fs::path& JsonPersistenceService::dataRoot() {
    if (g_root.empty()) {
        if (const char* env = std::getenv("APPDATA")) {
            g_root = fs::path(env) / "Flashnotes";
        } else {
            g_root = fs::path("data");
        }
    }
    return g_root;
}

#ifdef UNIT_TEST
void JsonPersistenceService::setDataRoot(const fs::path& p) {
    g_root = p;
}
#endif

std::vector<Note> JsonPersistenceService::loadNotes() {
    return load<Note>("notes.json");
}

std::vector<Folder> JsonPersistenceService::loadFolders() {
    return load<Folder>("folders.json");
}

std::vector<Flashcard> JsonPersistenceService::loadFlashcards() {
    return load<Flashcard>("flashcards.json");
}

std::vector<Material> JsonPersistenceService::loadMaterials() {
    return {};
}

void JsonPersistenceService::saveNotes(const std::vector<Note>& notes) {
    save("notes.json", notes);
}

void JsonPersistenceService::saveFolders(const std::vector<Folder>& folders) {
    save("folders.json", folders);
}

void JsonPersistenceService::saveFlashcards(const std::vector<Flashcard>& cards) {
    save("flashcards.json", cards);
}

void JsonPersistenceService::saveMaterials(const std::vector<Material>&) {
    // stub
}

} // namespace flashnotes
