#pragma once
#include "Page.h"

namespace csv {

auto formatPage(const Page &page) -> string;

auto formatPageCounter(const PageCounter &pageCounter) -> string;

using Labels = std::vector<string>;
auto formatActions(const Labels &labels) -> string;

} // namespace csv
