#include <gtest/gtest.h>
#define UNIT_TEST
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(Persistence, FolderRoundTrip) {
    fs::path temp = fs::temp_directory_path() / "flashnotes_folder";
    JsonPersistenceService::setDataRoot(temp);
    std::vector<Folder> folders{{1,"f1",{2,3}},{2,"f2",{}}};
    JsonPersistenceService::saveFolders(folders);
    auto loaded = JsonPersistenceService::loadFolders();
    ASSERT_EQ(loaded.size(), folders.size());
    EXPECT_EQ(loaded[0].childrenIds[0], folders[0].childrenIds[0]);
    EXPECT_EQ(loaded[1].name, folders[1].name);
}
