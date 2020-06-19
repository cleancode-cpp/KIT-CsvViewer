#include "Parser.h"

#include "Table.ostream.h"

#include <gtest/gtest.h>

using namespace csv;

TEST(Parser, Minimal) {
  EXPECT_EQ(csv::parse("C"), (Table{Row{"C"}, Grid{}})); //
}

TEST(Parser, Example) {
  auto given = std::string{"Name;Age;City\n"
                           "Peter;42;New York\n"
                           "Harry;;Seattle\n"};

  auto table = csv::parse(given);
  EXPECT_EQ(table, (Table{Row{"Name", "Age", "City"}, //
                          Grid{
                              Row{"Peter", "42", "New York"},
                              Row{"Harry", "", "Seattle"},
                          }}));
}
