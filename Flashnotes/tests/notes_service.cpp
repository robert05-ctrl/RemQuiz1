#include <gtest/gtest.h>
#define UNIT_TEST
#include "services/NotesService.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

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
