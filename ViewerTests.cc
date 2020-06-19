#include "Viewer.h"

#include <gtest/gtest.h>
#include <queue>
#include <sstream>

using namespace csv;

using Keys = std::queue<char>;
using Numbers = std::queue<int>;

struct TestConsole : IConsole {
  std::ostream &out;
  Keys keys;
  Numbers numbers;

  TestConsole(std::ostream &out, Keys keys, Numbers numbers)
      : out(out)
      , keys(keys)
      , numbers(numbers) {}

  ~TestConsole() = default;

  void clear() override {}
  void print(const string &str) override { out << str; }
  char readKey() override {
    auto k = keys.front();
    keys.pop();
    return k;
  }
  int readNumber() override {
    auto n = numbers.front();
    numbers.pop();
    return n;
  }
};

TEST(CsvViewer, Example) {
  auto buffer = std::stringstream{};
  auto keys = Keys{};
  keys.push('n');
  keys.push('f');
  keys.push('x');

  auto console = std::make_shared<TestConsole>(buffer, keys, Numbers{});

  auto table = Table{Row{"Name", "Age", "City"}, //
                     Grid{
                         Row{"Peter", "42", "New York"},
                         Row{"Harry", "", "Seattle"},
                         Row{"Harry2", "", "Seattle"},
                     }};

  auto viewer = Viewer{console, table, PageSize{2}};
  viewer.run();

  EXPECT_EQ(R"(Name |Age|City    |
-----+---+--------+
Peter|42 |New York|
Harry|   |Seattle |
Page 1 of 2

N(ext page, F(irst page, eX(it
Name  |Age|City   |
------+---+-------+
Harry2|   |Seattle|
Page 2 of 2

N(ext page, F(irst page, eX(it
Name |Age|City    |
-----+---+--------+
Peter|42 |New York|
Harry|   |Seattle |
Page 1 of 2

N(ext page, F(irst page, eX(it
)",
            buffer.str());
}
