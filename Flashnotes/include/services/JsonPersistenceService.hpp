#pragma once
#include <filesystem>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <nlohmann/json.hpp>

#include "domain/note.hpp"
#include "domain/folder.hpp"
#include "domain/flashcard.hpp"
#include "domain/flashcard_set.hpp"
#include "utils/Logger.hpp"

namespace flashnotes {

struct Material; // forward declaration

class JsonPersistenceService final {
public:
    template <typename T>
    static std::vector<T> load(const std::filesystem::path& file);

    template <typename T>
    static void save(const std::filesystem::path& file, const std::vector<T>& data);

    static std::vector<Note>      loadNotes();
    static std::vector<Folder>    loadFolders();
    static std::vector<Flashcard> loadFlashcards();
    static std::vector<FlashcardSet> loadFlashcardSets();
    static std::vector<Material>  loadMaterials();

    static void saveNotes     (const std::vector<Note>&);
    static void saveFolders   (const std::vector<Folder>&);
    static void saveFlashcards(const std::vector<Flashcard>&);
    static void saveFlashcardSets(const std::vector<FlashcardSet>&);
    static void saveMaterials (const std::vector<Material>&);

#ifdef UNIT_TEST
    static void setDataRoot(const std::filesystem::path&);
#endif

private:
    static const std::filesystem::path& dataRoot();
};

// Template implementations

template <typename T>
std::vector<T> JsonPersistenceService::load(const std::filesystem::path& file) {
    namespace fs = std::filesystem;
    fs::path path = dataRoot() / file;
    std::vector<T> result;
    if (!fs::exists(path)) {
        return result;
    }
    try {
        std::ifstream in(path);
        if (!in) {
            return result;
        }
        nlohmann::json j; in >> j;
        result = j.get<std::vector<T>>();
    } catch (const std::exception& e) {
        Logger::error(e.what());
        throw;
    }
    return result;
}

template <typename T>
void JsonPersistenceService::save(const std::filesystem::path& file, const std::vector<T>& data) {
    namespace fs = std::filesystem;
    fs::path path = dataRoot() / file;
    try {
        fs::create_directories(path.parent_path());
        std::ofstream out(path);
        nlohmann::json j = data;
        out << j.dump(4);
    } catch (const std::exception& e) {
        Logger::error(e.what());
        throw;
    }
}

} // namespace flashnotes
