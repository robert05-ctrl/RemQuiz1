#include <gtest/gtest.h>
#include "services/FileService.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>
#include <fstream>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(FileService, CreateList) {
    fs::path root = fs::temp_directory_path() / "file_service_create";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FileService svc;
    fs::path fake = root / "dummy.txt";
    std::ofstream(fake).close();
    auto m = svc.create(fake);
    auto list = svc.list();
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0].id, m.id);
}

TEST(FileService, RemovePersists) {
    fs::path root = fs::temp_directory_path() / "file_service_remove";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FileService svc;
    fs::path fake = root / "dummy.txt";
    std::ofstream(fake).close();
    auto m = svc.create(fake);
    svc.remove(m.id);
    JsonPersistenceService::setDataRoot(root);
    FileService reload;
    EXPECT_TRUE(reload.list().empty());
}
