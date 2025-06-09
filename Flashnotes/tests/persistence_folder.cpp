#include <gtest/gtest.h>
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(Persistence, FolderRoundTrip) {
    fs::path temp = fs::temp_directory_path() / "flashnotes_folder";
    JsonPersistenceService::setDataRoot(temp);
    std::vector<Folder> folders{{1, -1, "f1"},{2,1,"f2"}};
    JsonPersistenceService::saveFolders(folders);
    auto loaded = JsonPersistenceService::loadFolders();
    ASSERT_EQ(loaded.size(), folders.size());
    EXPECT_EQ(loaded[0].name, folders[0].name);
    EXPECT_EQ(loaded[1].parentId, folders[1].parentId);
}
