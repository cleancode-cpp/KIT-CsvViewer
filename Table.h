#pragma once
#include <string>
#include <vector>

namespace csv {

using std::string;

using Row = std::vector<string>;
using Grid = std::vector<Row>;

struct Table {
  Row header;
  Grid grid;

  Table() = default;
  Table(const Row &) {}

  Table(const Table &) = delete;
  Table &operator=(const Table &) = delete;
  //   Table(Table &&) = default;
  //   Table& operator=(Table &&) = default;
  //   ~Table() = default;

  // later with C++20
  // bool operator==(const Table &) const = default;
};

} // namespace csv
