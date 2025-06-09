#include <gtest/gtest.h>
#include "controllers/NotesController.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(NotesController, ThrowsOnEmptyTitle) {
    fs::path root = fs::temp_directory_path() / "notes_controller_empty";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    NotesController ctrl;
    auto res = ctrl.createNote("", "body", "/tmp");
    EXPECT_FALSE(res);
    EXPECT_EQ(res.error(), "Title must not be empty");
}

TEST(NotesController, UpdateNote) {
    fs::path root = fs::temp_directory_path() / "notes_controller_update";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    NotesController ctrl;
    auto created = ctrl.createNote("t","b","/tmp/path.txt");
    ASSERT_TRUE(created);
    auto updated = ctrl.updateNote(created.value().id, "t2", "b2");
    ASSERT_TRUE(updated);
    EXPECT_EQ(updated.value().title, "t2");
    auto list = ctrl.listNotes();
    ASSERT_TRUE(list);
    EXPECT_EQ(list.value()[0].title, "t2");
}
