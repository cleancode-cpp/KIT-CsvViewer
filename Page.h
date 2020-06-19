#pragma once
#include "Table.h"

namespace csv {

struct CurrentPage {
  int v;
};
struct PageSize {
  int v;
};
struct RowCount {
  int v;
};

struct PageCounter {
  CurrentPage curret;
  PageSize pageSize;
  RowCount totalRows;
};

struct Page {
  Table table{};  // full table
  int current{};  // current page
  int rowCount{}; // rows per page

  Page() = default;
  Page(Table table, int current, int rowCount)
      : table(std::move(table))
      , current(current)
      , rowCount(rowCount) {}

  bool operator==(const Page &o) const {
    return table == o.table && current == o.current && rowCount == o.rowCount; //
  }
};

} // namespace csv
