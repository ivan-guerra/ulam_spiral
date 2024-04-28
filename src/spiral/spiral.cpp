#include "spiral/spiral.h"

#include <cmath>
#include <optional>

namespace ulam {

struct Position {
  int row = 0;
  int col = 0;
};

[[nodiscard]] static bool IsPrime(int n) {
  if (n <= 1) {
    return false;
  }

  for (int i = 2; i <= std::sqrt(n); i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

std::optional<SquareLattice> GenerateUlamSpiral(int dim) {
  /* The implementation that follows is a slightly tweaked version of the
   * algorithm given here:
   * https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/# */

  if (dim <= 0) { /* invalid dimension */
    return std::nullopt;
  }

  const std::vector<Position> kDirections = {
      {.row = 0, .col = 1},  /* east  */
      {.row = 1, .col = 0},  /* south */
      {.row = 0, .col = -1}, /* west */
      {.row = -1, .col = 0}, /* north */
  };

  SquareLattice spiral(dim, RowVect(dim, 0));
  Position pos = {.row = 0, .col = 0};
  int dir_index = 0;
  int value = dim * dim;
  std::vector<std::vector<bool>> visited(dim, std::vector<bool>(dim, false));
  for (int i = 0; i < dim * dim; ++i) {
    /* We always write a number. If value is prime, we write value, otherwise,
     * we write 0 as a placeholder. Note how we spiral inwards so that larger
     * numbers are on the outside of the spiral and smaller ones are closer to
     * the center. */
    if (IsPrime(value)) {
      spiral[pos.row][pos.col] = value;
    } else {
      spiral[pos.row][pos.col] = 0;
    }
    value--;

    visited[pos.row][pos.col] = true;

    int row = pos.row + kDirections[dir_index].row;
    int col = pos.col + kDirections[dir_index].col;
    if ((row >= 0) && (row < dim) && (col >= 0) && (col < dim) &&
        !visited[row][col]) { /* Continue moving in the current direction. */
      pos.row = row;
      pos.col = col;
    } else { /* A change in direction is required. */
      dir_index = (dir_index + 1) % kDirections.size();
      pos.row += kDirections[dir_index].row;
      pos.col += kDirections[dir_index].col;
    }
  }
  return spiral;
}

}  // namespace ulam
