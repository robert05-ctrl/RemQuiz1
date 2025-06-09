#include <gtest/gtest.h>
#include "services/NotesService.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>
#include <fstream>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(NotesService, CreateAndList) {
    fs::path root = fs::temp_directory_path() / "notes_service_create";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    NotesService svc;
    auto n = svc.create("t","b","/tmp");
    auto all = svc.list();
    ASSERT_EQ(all.size(), 1u);
    EXPECT_EQ(all[0].id, n.id);
}

TEST(NotesService, RemovePersists) {
    fs::path root = fs::temp_directory_path() / "notes_service_remove";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    NotesService svc;
    auto n = svc.create("t","b","/tmp");
    svc.remove(n.id);
    JsonPersistenceService::setDataRoot(root);
    NotesService reload;
    EXPECT_TRUE(reload.list().empty());
}

TEST(NotesService, UpdatePersists) {
    fs::path root = fs::temp_directory_path() / "notes_service_update";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    NotesService svc;
    auto n = svc.create("t","b","/tmp/file.txt");
    svc.update(n.id, "t2", "b2");
    JsonPersistenceService::setDataRoot(root);
    NotesService reload;
    auto all = reload.list();
    ASSERT_EQ(all.size(), 1u);
    EXPECT_EQ(all[0].title, "t2");
    EXPECT_EQ(all[0].body, "b2");
}

TEST(NotesService, RemoveDeletesFile) {
    fs::path root = fs::temp_directory_path() / "notes_service_file_remove";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    fs::create_directories(root);
    fs::path file = root / "note.txt";
    {
        std::ofstream out(file.string());
        out << "body";
    }
    NotesService svc;
    auto n = svc.create("t","body", file);
    svc.remove(n.id);
    EXPECT_FALSE(fs::exists(file));
}
