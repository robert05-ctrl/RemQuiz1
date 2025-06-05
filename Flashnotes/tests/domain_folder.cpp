#include <gtest/gtest.h>
#include "domain/folder.hpp"
#include <nlohmann/json.hpp>

using flashnotes::Folder;
using nlohmann::json;

TEST(FolderTest, VectorSerialization) {
    Folder f{3, "root", {1,2}};
    json j = f;
    ASSERT_TRUE(j["childrenIds"].is_array());
    Folder out = j.get<Folder>();
    EXPECT_EQ(out.childrenIds.size(), 2u);
    EXPECT_EQ(out.childrenIds[0], 1);
}
