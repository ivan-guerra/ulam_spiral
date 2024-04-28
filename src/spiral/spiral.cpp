#include "spiral/spiral.h"

#include <cmath>
#include <cstddef>

namespace ulam {

struct Position {
  int row = 0;
  int col = 0;
};

bool IsPrime(int n) {
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

SquareLattice GenerateUlamSpiral(int dim) {
  const std::vector<Position> kDirections = {
      {.row = 0, .col = 1},
      {.row = 1, .col = 0},
      {.row = 0, .col = -1},
      {.row = -1, .col = 0},
  };

  SquareLattice spiral(dim, RowVect(dim, 0));
  Position curr_pos = {.row = 0, .col = 0};
  int di = 0;
  std::size_t value = dim * dim;
  std::vector<std::vector<bool>> seen(dim, std::vector<bool>(dim, false));
  for (int i = 0; i < dim * dim; ++i) {
    if (IsPrime(value)) {
      spiral[curr_pos.row][curr_pos.col] = value;
    } else {
      spiral[curr_pos.row][curr_pos.col] = 0;
    }
    value--;

    seen[curr_pos.row][curr_pos.col] = true;

    int row = curr_pos.row + kDirections[di].row;
    int col = curr_pos.col + kDirections[di].col;
    if ((row >= 0) && (row < dim) && (col >= 0) && (col < dim) &&
        !seen[row][col]) {
      curr_pos.row = row;
      curr_pos.col = col;
    } else {
      di = (di + 1) % kDirections.size();
      curr_pos.row += kDirections[di].row;
      curr_pos.col += kDirections[di].col;
    }
  }
  return spiral;
}

}  // namespace ulam
