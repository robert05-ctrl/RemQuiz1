#include "controllers/NotesController.hpp"

namespace flashnotes {

NotesController::NotesController()
    : service_(std::make_shared<NotesService>()) {}

NotesController::NotesController(std::shared_ptr<NotesService> svc)
    : service_(std::move(svc)) {}

Expected<Note> NotesController::createNote(const std::string& title,
                                           const std::string& body,
                                           const std::filesystem::path& savePath) {
    if (title.empty()) {
        return Expected<Note>("Title must not be empty");
    }
    try {
        return service_->create(title, body, savePath);
    } catch (const std::exception& e) {
        return Expected<Note>(e.what());
    }
}

Expected<Note> NotesController::updateNote(std::uint64_t id,
                                           const std::string& title,
                                           const std::string& body) {
    if (title.empty()) {
        return Expected<Note>("Title must not be empty");
    }
    try {
        return service_->update(id, title, body);
    } catch (const std::exception& e) {
        return Expected<Note>(e.what());
    }
}

Expected<std::vector<Note>> NotesController::listNotes() const {
    try {
        return service_->list();
    } catch (const std::exception& e) {
        return Expected<std::vector<Note>>(e.what());
    }
}

Expected<void> NotesController::removeNote(std::uint64_t id) {
    try {
        service_->remove(id);
        return Expected<void>();
    } catch (const std::exception& e) {
        return Expected<void>(e.what());
    }
}

} // namespace flashnotes
