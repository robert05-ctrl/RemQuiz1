#include "controllers/FileController.hpp"

namespace flashnotes {

FileController::FileController()
    : service_(std::make_shared<FileService>()) {}

FileController::FileController(std::shared_ptr<FileService> svc)
    : service_(std::move(svc)) {}

Expected<Material> FileController::createFile(const std::filesystem::path& path, int folderId) {
    try {
        return service_->create(path, folderId);
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

Expected<Folder> FileController::createFolder(const std::string& name, int parentId) {
    try {
        return service_->createFolder(name, parentId);
    } catch (const std::exception& e) {
        return Expected<Folder>(e.what());
    }
}

Expected<Folder> FileController::updateFolder(std::uint64_t id, const std::string& name) {
    try {
        return service_->updateFolder(id, name);
    } catch (const std::exception& e) {
        return Expected<Folder>(e.what());
    }
}

Expected<std::vector<Folder>> FileController::listFolders() const {
    try {
        return service_->listFolders();
    } catch (const std::exception& e) {
        return Expected<std::vector<Folder>>(e.what());
    }
}

Expected<void> FileController::removeFolder(std::uint64_t id) {
    try {
        service_->removeFolder(id);
        return Expected<void>();
    } catch (const std::exception& e) {
        return Expected<void>(e.what());
    }
}

} // namespace flashnotes
