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

  // later with C++20
  // bool operator==(const Table &) const = default;
};

} // namespace csv
