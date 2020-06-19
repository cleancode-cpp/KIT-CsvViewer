#include "Hints.h"

#include <iomanip>
#include <sstream>

namespace hints {

auto splitString(const String &str, char delim) -> Strings {
  auto entry = String{};
  auto stream = std::stringstream(str);
  auto r = Strings{};
  while (std::getline(stream, entry, delim)) {
    r.push_back(entry);
  }
  return r;
}

auto formatRow(const Widths &widths, const Strings &row, char delim) -> String {
  auto stream = std::stringstream();
  auto columnCount = widths.size();
  for (auto col = 0u; col < columnCount; ++col) {
    stream << std::setw(widths[col]) << std::left //
           << (col < row.size() ? row[col] : "") << delim;
  }
  return stream.str();
}

auto formatSplitter(const Widths &widths, const char line, char delim) -> String {
  auto stream = std::stringstream();
  auto columnCount = widths.size();
  for (auto w : widths) {
    stream << std::string(w, line) << delim;
  }
  return stream.str();
}

} // namespace hints
