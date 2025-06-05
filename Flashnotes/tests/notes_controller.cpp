#include <gtest/gtest.h>
#define UNIT_TEST
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
