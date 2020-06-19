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

  bool operator==(const Table &o) const {
    return header == o.header && grid == o.grid; //
  }
};

} // namespace csv
