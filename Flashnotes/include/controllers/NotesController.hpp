#pragma once
#include <memory>
#include <filesystem>
#include <vector>
#include "domain/note.hpp"
#include "services/NotesService.hpp"
#include "utils/Expected.hpp"

namespace flashnotes {

class NotesController {
public:
    NotesController();
    explicit NotesController(std::shared_ptr<NotesService> svc);

    Expected<Note> createNote(const std::string& title,
                              const std::string& body,
                              const std::filesystem::path& savePath);
    Expected<std::vector<Note>> listNotes() const;
    Expected<void> removeNote(std::uint64_t id);

private:
    std::shared_ptr<NotesService> service_;
};

} // namespace flashnotes
