#include "Formatter.h"

#include "Table.ostream.h"

#include <gtest/gtest.h>

using namespace csv;

TEST(Formatter, PageExample) {
  auto page = Page{
      Table{Row{"Name", "Age", "City"}, //
            Grid{
                Row{"Peter", "42", "New York"}, //
                Row{"Harry", "", "Seattle"}     //
            }},
      0, 2 //
  };
  EXPECT_EQ(csv::formatPage(page),
            "Name |Age|City    |\n"
            "-----+---+--------+\n"
            "Peter|42 |New York|\n"
            "Harry|   |Seattle |\n"); //
}

TEST(Formatter, PageCounterExample) {
  auto pageCounter = PageCounter{
      CurrentPage{0}, PageSize{2}, RowCount{4} //
  };
  EXPECT_EQ(csv::formatPageCounter(pageCounter), "Page 1 of 2");
}