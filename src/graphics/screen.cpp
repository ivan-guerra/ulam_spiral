#include "graphics/screen.h"

#include <curses.h>
#include <ncurses.h>

#include <optional>
#include <vector>

namespace ulam {

std::optional<ScreenDimension> InitScreen() {
  if (!::initscr()) {
    return std::nullopt;
  }
  /*
   * In the conditional below, we try to set the following ncurses settings:
   *   (1) disable line buffering
   *   (2) enable the keypad so we can exit via keypress
   *   (3) disable character echoing
   *   (4) hide the cursor
   *   (5) start the color engine
   */
  if (ERR == ::cbreak() || ERR == ::keypad(stdscr, TRUE) || ERR == ::noecho() ||
      ERR == ::curs_set(0) || ERR == ::start_color()) {
    return std::nullopt;
  }

  /* Initialize color pairs. */
  const std::vector<std::pair<Color, int>> kColors = {
      {Color::kRed, COLOR_RED},         {Color::kGreen, COLOR_GREEN},
      {Color::kBlue, COLOR_BLUE},       {Color::kYellow, COLOR_YELLOW},
      {Color::kMagenta, COLOR_MAGENTA}, {Color::kCyan, COLOR_CYAN},
      {Color::kWhite, COLOR_WHITE},
  };
  for (const auto& p : kColors) {
    if (ERR == ::init_pair(p.first, p.second, COLOR_BLACK)) {
      return std::nullopt;
    }
  }

  /* Fetch the screen dimensions. */
  ScreenDimension screen_dim = {.width = 0, .height = 0};
  /* Funny, getmaxyx() macro has an undefined return value. */
  getmaxyx(stdscr, screen_dim.height, screen_dim.width);

  return screen_dim;
}

void TerminateScreen() { ::endwin(); }

void DrawChar(const Point2D& pos, char symbol, Color color) {
  ::attron(COLOR_PAIR(color) | A_BOLD);
  mvaddch(pos.y, pos.x, symbol);
  ::attroff(COLOR_PAIR(color) | A_BOLD);

  ::refresh();
}

void DrawStr(const std::string& str, const Point2D& pos) {
  ::mvprintw(pos.y, pos.x, "%s", str.c_str());

  ::refresh();
}

bool UserPressedKey() { return (ERR != ::getch()); }

}  // namespace ulam
