#include "Hints.h"

#include <gtest/gtest.h>

TEST(Hints_SplitLine, Empty) {
  auto given = std::string{};

  auto result = hints::splitString(given, ';');

  EXPECT_TRUE(result.empty());
}

TEST(Hints_SplitLine, Regular) {
  auto given = std::string{"a;b;c"};

  auto result = hints::splitString(given, ';');

  auto expected = std::vector<std::string>{"a", "b", "c"};
  EXPECT_EQ(result, expected);
}

TEST(Hints_SplitLine, EmptyCell) {
  auto given = std::string{"a;;c"};

  auto result = hints::splitString(given, ';');

  auto expected = std::vector<std::string>{"a", "", "c"};
  EXPECT_EQ(result, expected);
}

TEST(Hints_FormatRow, Regular) {
  auto givenRow = std::vector<std::string>{"a", "b", "c"};
  auto givenWidths = std::vector<int>{1, 2, 3};

  auto result = hints::formatRow(givenWidths, givenRow, '|');

  auto expected = "a|b |c  |";
  EXPECT_EQ(result, expected);
}

TEST(Hints_FormatRow, ExtraWidths) {
  auto givenRow = std::vector<std::string>{"a"};
  auto givenWidths = std::vector<int>{1, 2};

  auto result = hints::formatRow(givenWidths, givenRow, '|');

  auto expected = "a|  |";
  EXPECT_EQ(result, expected);
}

TEST(Hints_FormatRow, ExtraCell) {
  auto givenRow = std::vector<std::string>{"a", "b", "c"};
  auto givenWidths = std::vector<int>{1, 2};

  auto result = hints::formatRow(givenWidths, givenRow, '|');

  auto expected = "a|b |";
  EXPECT_EQ(result, expected);
}

TEST(Hints_FormatSplitter, Regular) {
  auto givenWidths = std::vector<int>{1, 2, 3};

  auto result = hints::formatSplitter(givenWidths, '-', '+');

  auto expected = "-+--+---+";
  EXPECT_EQ(result, expected);
}
