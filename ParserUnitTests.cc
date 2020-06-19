#include "Parser.h"

#include <gtest/gtest.h>

namespace csv {

bool operator==(const Table &l, const Table &r) {
  return l.header == r.header && l.grid == r.grid; //
}

auto operator<<(std::ostream &out, const Row &row) -> std::ostream & {
  for (auto &cell : row) {
    out << cell << ";";
  }
  return out;
}

auto operator<<(std::ostream &out, const Grid &grid) -> std::ostream & {
  for (auto &row : grid) {
    out << row << "\n";
  }
  return out;
}

auto operator<<(std::ostream &out, const Table &t) -> std::ostream & {
  return out << "header: " << t.header << '\n' //
             << "grid: " << t.grid;
}

} // namespace csv

TEST(Parser, Example) {
  auto given = std::string{"Name;Age;City\n"
                           "Peter;42;New York\n"
                           "Harry;;Seattle\n"};

  auto table = csv::parse(given);

  using namespace csv;
  EXPECT_EQ(table, (Table{Row{"Name", "Age", "City"}, //
                          Grid{
                              Row{"Peter", "42", "New York"},
                              Row{"Harry", "", "Seattle"},
                          }}));
}
