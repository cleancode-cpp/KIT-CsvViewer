#include "Formatter.h"

#include <functional>
#include <memory>

namespace csv {

struct IConsole {
  virtual ~IConsole() = default;
  virtual void clear() = 0;
  virtual void print(const string &) = 0;
  virtual char readKey() = 0;
  virtual int readNumber() = 0;
};
using ConsolePtr = std::shared_ptr<IConsole>;

using ActionFunc = std::function<void()>;
struct Action {
  string label;
  char key;
  ActionFunc func;
};
using Actions = std::vector<Action>;

struct Viewer {
  Viewer(ConsolePtr console, Table table, PageSize pageSize)
      : console(console)
      , page(std::move(table), 0, pageSize.v) {

    actions.emplace_back(Action{"N(ext page", 'n', [this] { nextPage(); }});
    actions.emplace_back(Action{"F(irst page", 'f', [this] { firstPage(); }});
    actions.emplace_back(Action{"eX(it", 'x', [this] { isRunning = false; }});
  }

  void run() {
    while (isRunning) {
      render();
      interact();
    }
  }

private:
  void render() {
    console->clear();
    console->print(formatPage(page));
    console->print(formatPageCounter(getPageCounter()));
    console->print("\n\n");
    console->print(formatActions(getActionLabels()));
    console->print("\n");
  }

  auto getPageCounter() const -> PageCounter {
    return {
        CurrentPage{page.current},            //
        PageSize{page.rowCount},              //
        RowCount{(int)page.table.grid.size()} //
    };
  }

  void interact() {
    auto key = console->readKey();
    auto action = actionForKey(key);
    action();
  }

  auto getActionLabels() const -> Labels {
    auto result = Labels{};
    for (auto &action : actions)
      result.emplace_back(action.label);
    return result;
  }

  auto actionForKey(char key) const -> ActionFunc {
    for (auto &action : actions) {
      if (action.key == key)
        return action.func;
    }
    return []() {};
  }

  void nextPage() {
    auto next = page.current + 1;
    if (next * page.rowCount < page.table.grid.size()) {
      page.current = next;
    }
  }
  void firstPage() { page.current = 0; }

private:
  ConsolePtr console;
  Page page;
  Actions actions;
  bool isRunning{true};
};

} // namespace csv