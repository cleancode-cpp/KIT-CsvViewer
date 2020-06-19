#include "Formatter.h"

#include "Hints.h"

#include <algorithm>
#include <sstream>

namespace csv {

using hints::Widths;

auto begin(const Page &page) -> Grid::const_iterator {
  return page.table.grid.begin() +                   //
         std::min<int>(page.current * page.rowCount, //
                       page.table.grid.size());      //
}

auto end(const Page &page) -> Grid::const_iterator {
  return page.table.grid.begin() +                                   //
         std::min<int>(page.current * page.rowCount + page.rowCount, //
                       page.table.grid.size());
}

auto computeMaxColumnWidths(const Page &page) -> Widths {
  auto columnCount = page.table.header.size();
  auto widths = Widths{};
  widths.resize(columnCount, 0);

  auto forRow = [&](const Row &row) {
    auto len = std::min(row.size(), columnCount);
    for (auto col = 0u; col < len; col++) {
      widths[col] = std::max<int>(widths[col], row[col].length());
    }
  };

  forRow(page.table.header);
  for (auto &row : page) {
    forRow(row);
  }
  return widths;
}

auto formatPage(const Page &page) -> string {
  auto widths = computeMaxColumnWidths(page);

  auto stream = std::stringstream{};
  stream << hints::formatRow(widths, page.table.header, '|') << '\n' //
         << hints::formatSplitter(widths, '-', '+') << '\n';

  for (auto &row : page) {
    stream << hints::formatRow(widths, row, '|') << '\n';
  }
  return stream.str();
}

auto formatPageCounter(const PageCounter &pageCounter) -> string {
  auto stream = std::stringstream{};
  auto pageCount = (pageCounter.totalRows.v + pageCounter.pageSize.v - 1) / pageCounter.pageSize.v;
  stream << "Page " << (pageCounter.curret.v + 1) << " of " << pageCount;
  return stream.str();
}

auto formatActions(const Labels &labels) -> string {
  auto stream = std::stringstream{};
  auto first = true;
  for (auto &label : labels) {
    if (!first)
      stream << ", ";
    else
      first = false;
    stream << label;
  }
  return stream.str();
}

} // namespace csv