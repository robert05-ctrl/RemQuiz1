#include <gtest/gtest.h>
#include "domain/folder.hpp"
#include <nlohmann/json.hpp>

using flashnotes::Folder;
using nlohmann::json;

TEST(FolderTest, BasicSerialization) {
    Folder f{3, 0, "root"};
    json j = f;
    ASSERT_EQ(j["name"], "root");
    Folder out = j.get<Folder>();
    EXPECT_EQ(out.id, 3);
    EXPECT_EQ(out.parentId, 0);
}
