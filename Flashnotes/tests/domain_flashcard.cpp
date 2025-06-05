#include <gtest/gtest.h>
#include "domain/flashcard.hpp"
#include <nlohmann/json.hpp>

using flashnotes::Flashcard;
using nlohmann::json;

TEST(FlashcardTest, DefaultRateAndJson) {
    Flashcard c{2, "front", "back"};
    EXPECT_DOUBLE_EQ(c.successRate, 0.5);
    json j = c;
    Flashcard out = j.get<Flashcard>();
    EXPECT_EQ(out.front, c.front);
    EXPECT_DOUBLE_EQ(out.successRate, 0.5);
}
