#include <gtest/gtest.h>
#define UNIT_TEST
#include "services/JsonPersistenceService.hpp"
#include <filesystem>

using namespace flashnotes;
namespace fs = std::filesystem;

TEST(Persistence, NoteRoundTrip) {
    fs::path temp = fs::temp_directory_path() / "flashnotes_note";
    JsonPersistenceService::setDataRoot(temp);
    std::vector<Note> notes{{1,"t1","b1","/p1"},{2,"t2","b2","/p2"}};
    JsonPersistenceService::saveNotes(notes);
    auto loaded = JsonPersistenceService::loadNotes();
    ASSERT_EQ(loaded.size(), notes.size());
    EXPECT_EQ(loaded[0].title, notes[0].title);
    EXPECT_EQ(loaded[1].body, notes[1].body);
}
