#pragma once
#include <memory>
#include <vector>
#include "domain/material.hpp"
#include "services/FileService.hpp"
#include "utils/Expected.hpp"

namespace flashnotes {

class FileController {
public:
    FileController();
    explicit FileController(std::shared_ptr<FileService> svc);

    Expected<Material> createFile();
    Expected<std::vector<Material>> listFiles() const;
    Expected<void> removeFile(std::uint64_t id);

private:
    std::shared_ptr<FileService> service_;
};

} // namespace flashnotes
