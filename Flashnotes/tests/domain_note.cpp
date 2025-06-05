#include <gtest/gtest.h>
#include "domain/note.hpp"
#include <nlohmann/json.hpp>

using flashnotes::Note;
using nlohmann::json;

TEST(NoteTest, SerializeDeserialize) {
    Note n{1, "title", "body", "/tmp"};
    json j = n;
    EXPECT_EQ(j["id"], 1);
    EXPECT_EQ(j["title"], "title");
    Note out = j.get<Note>();
    EXPECT_EQ(out.id, n.id);
    EXPECT_EQ(out.savedPath, n.savedPath);
}
