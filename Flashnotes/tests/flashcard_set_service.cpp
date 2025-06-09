#include <gtest/gtest.h>
#include "services/FlashcardSetService.hpp"
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(FlashcardSetService, CreateList)
{
    fs::path root = fs::temp_directory_path() / "set_create";
    fs::remove_all(root);
    JsonPersistenceService::setDataRoot(root);
    FlashcardSetService svc;
    std::vector<Flashcard> cards{{0,"f","b"}};
    auto s = svc.create("t", cards, root/"set.json");
    auto list = svc.list();
    ASSERT_EQ(list.size(), 1u);
    EXPECT_EQ(list[0].id, s.id);
}
