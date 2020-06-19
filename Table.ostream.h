#include "Table.h"

#include <ostream>

namespace csv {

inline auto operator<<(std::ostream &out, const Row &row) -> std::ostream & {
  for (auto &cell : row) {
    out << cell << ";";
  }
  return out;
}

inline auto operator<<(std::ostream &out, const Grid &grid) -> std::ostream & {
  for (auto &row : grid) {
    out << row << "\n";
  }
  return out;
}

inline auto operator<<(std::ostream &out, const Table &t) -> std::ostream & {
  return out << "header: " << t.header << '\n' //
             << "grid: " << t.grid;
}

} // namespace csv
