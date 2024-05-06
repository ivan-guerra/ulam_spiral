#include "spiral/spiral.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_set>

namespace ulam {

struct Position {
  int32_t row = 0;
  int32_t col = 0;

  friend bool operator==(const Position& a, const Position& b) {
    return (a.row == b.row) && (a.col == b.col);
  }

  friend Position operator+(const Position& a, const Position& b) {
    return {.row = a.row + b.row, .col = a.col + b.col};
  }
};

struct PositionHash {
  std::size_t operator()(const Position& pos) const {
    uint64_t val = pos.row;
    val = (val << 32) | pos.col;
    return std::hash<std::size_t>{}(val);
  }
};

[[nodiscard]] static std::unordered_set<int> SieveOfEratosthenes(int n) {
  std::unordered_set<int> primes;
  for (int i = 2; i < n + 1; ++i) {
    primes.insert(i);
  }

  for (int p = 2; p * p <= n; p++) {
    if (primes.contains(p)) {
      for (int i = p * p; i <= n; i += p) {
        primes.erase(i);
      }
    }
  }
  return primes;
}

[[nodiscard]] bool IsInBounds(const Position& pos, int dim) {
  return ((pos.row >= 0) && (pos.row < dim) && (pos.col >= 0) &&
          (pos.col < dim));
}

std::optional<SquareLattice> GenerateUlamSpiral(int dim) {
  /* The implementation that follows is a slightly tweaked version of the
   * algorithm given here:
   * https://www.geeksforgeeks.org/print-a-given-matrix-in-spiral-form/# */

  if (dim <= 0) { /* invalid dimension */
    return std::nullopt;
  }

  const std::vector<Position> kDirections = {
      {.row = 0, .col = -1}, /* west */
      {.row = -1, .col = 0}, /* north */
      {.row = 0, .col = 1},  /* east  */
      {.row = 1, .col = 0},  /* south */
  };

  std::unordered_set<int> primes = SieveOfEratosthenes(dim * dim);
  SquareLattice spiral(dim, RowVect(dim, 0));
  Position pos = {.row = dim - 1, .col = dim - 1};
  int dir_index = 0;
  int value = dim * dim;
  std::unordered_set<Position, PositionHash> visited;
  for (int i = 0; i < dim * dim; ++i) {
    /* We always write a number. If value is prime, we write value, otherwise,
     * we write 0 as a placeholder. */
    if (primes.contains(value)) {
      spiral[pos.row][pos.col] = value;
    } else {
      spiral[pos.row][pos.col] = 0;
    }
    value--;

    visited.insert(pos);

    Position candidate = kDirections[dir_index] + pos;
    if (IsInBounds(candidate, dim) && !visited.count(candidate)) {
      pos = candidate;
    } else { /* A change in direction is required. */
      dir_index = (dir_index + 1) % kDirections.size();
      pos = kDirections[dir_index] + pos;
    }
  }
  return spiral;
}

}  // namespace ulam
