#include "controllers/FileController.hpp"

namespace flashnotes {

FileController::FileController()
    : service_(std::make_shared<FileService>()) {}

FileController::FileController(std::shared_ptr<FileService> svc)
    : service_(std::move(svc)) {}

Expected<Material> FileController::createFile() {
    try {
        return service_->create();
    } catch (const std::exception& e) {
        return Expected<Material>(e.what());
    }
}

Expected<std::vector<Material>> FileController::listFiles() const {
    try {
        return service_->list();
    } catch (const std::exception& e) {
        return Expected<std::vector<Material>>(e.what());
    }
}

Expected<void> FileController::removeFile(std::uint64_t id) {
    try {
        service_->remove(id);
        return Expected<void>();
    } catch (const std::exception& e) {
        return Expected<void>(e.what());
    }
}

} // namespace flashnotes
