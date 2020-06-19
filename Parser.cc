#include "Parser.h"

#include "Hints.h"

#include <sstream>

namespace csv {

auto parse(string input) -> Table {
  auto stream = std::stringstream{input};
  auto line = std::string{};
  std::getline(stream, line);
  auto header = hints::splitString(line, ';');
  auto grid = Grid{};
  while (std::getline(stream, line)) {
    grid.emplace_back(hints::splitString(line, ';'));
  }
  return {header, grid};
}

} // namespace csv