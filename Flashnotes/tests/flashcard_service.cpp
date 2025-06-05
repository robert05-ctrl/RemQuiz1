#include <gtest/gtest.h>
#include "services/FlashcardService.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(FlashcardService, CreateList) {
    fs::path root = fs::temp_directory_path() / "flashcard_create";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FlashcardService svc;
    auto c = svc.create("f","b");
    auto list = svc.list();
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0].id, c.id);
}

TEST(FlashcardService, RemovePersists) {
    fs::path root = fs::temp_directory_path() / "flashcard_remove";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FlashcardService svc;
    auto c = svc.create("f","b");
    svc.remove(c.id);
    JsonPersistenceService::setDataRoot(root);
    FlashcardService reload;
    EXPECT_TRUE(reload.list().empty());
}

TEST(FlashcardService, GetNextCardsLimit) {
    fs::path root = fs::temp_directory_path() / "flashcard_next";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FlashcardService svc;
    svc.create("1","1");
    svc.create("2","2");
    svc.create("3","3");
    auto next = svc.getNextCards(2);
    ASSERT_LE(next.size(), 2u);
    EXPECT_EQ(next[0].front, "1");
}
