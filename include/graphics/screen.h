#ifndef SCREEN_H_
#define SCREEN_H_

#include <optional>
#include <string>

namespace ulam {

struct Point2D {
  int x = 0;
  int y = 0;
};

/**
 * \brief Supported character colors.
 */
enum Color {
  kRed = 1,
  kGreen,
  kBlue,
  kYellow,
  kMagenta,
  kCyan,
  kWhite,
};

/**
 * \brief Screen Dimensions
 */
struct ScreenDimension {
  int width = 0;  /**< Screen width. */
  int height = 0; /**< Screen height. */
};

/**
 * \brief Initialize the ncurses screen.
 * \returns The dimensions of the screen (i.e., terminal window).
 */
[[nodiscard]] std::optional<ScreenDimension> InitScreen();

/**
 * \brief Cleanup ncurses screen.
 */
void TerminateScreen();

/**
 * \brief Render \p symbol at position \p pos on the screen.
 * \param [in] pos    Position at which the character will be rendered on
 *                    screen.
 * \param [in] symbol The character that will be rendered.
 * \param [in] color  The color of the printed character.
 */
void DrawChar(const Point2D& pos, char symbol, Color color = Color::kWhite);

/**
 * \brief Draw the string \p str at position \p pos on the screen.
 * \param [in] str The string to be printed.
 * \param [in] pos Position at which the string will be printed.
 */
void DrawStr(const std::string& str, const Point2D& pos);

/**
 * \brief Return \c true if the user pressed any key.
 */
[[nodiscard]] bool UserPressedKey();

}  // namespace ulam

#endif
