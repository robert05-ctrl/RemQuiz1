#include <iostream>
#include "controllers/AppController.hpp"

using namespace flashnotes;

int main() {
    try {
        AppController app;

        auto noteRes = app.notes().createNote("Sample", "Body", "/tmp");
        if (!noteRes) {
            std::cerr << noteRes.error() << std::endl;
            return 1;
        }
        auto notes = app.notes().listNotes();
        if (!notes) {
            std::cerr << notes.error() << std::endl;
            return 1;
        }
        std::cout << "Notes count: " << notes.value().size() << std::endl;

        auto mat = app.files().createFile("/tmp/test.txt");
        if (!mat) {
            std::cerr << mat.error() << std::endl;
            return 1;
        }
        auto mats = app.files().listFiles();
        if (!mats) {
            std::cerr << mats.error() << std::endl;
            return 1;
        }
        std::cout << "Materials count: " << mats.value().size() << std::endl;

        app.flashcards().createFlashcard("Q1", "A1");
        app.flashcards().createFlashcard("Q2", "A2");
        auto next = app.flashcards().getNextCards(1);
        if (!next) {
            std::cerr << next.error() << std::endl;
            return 1;
        }
        for (const auto& c : next.value()) {
            std::cout << "Card: " << c.front << " -> " << c.back << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
