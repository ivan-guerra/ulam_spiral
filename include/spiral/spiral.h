#ifndef SPIRAL_H_
#define SPIRAL_H_

#include <vector>

namespace ulam {

using RowVect = std::vector<int>;
using SquareLattice = std::vector<RowVect>;

/**
 * \brief Generate a \p dim x \p dim Ulam Spiral matrix.
 * \details See https://en.wikipedia.org/wiki/Ulam_spiral# for details.
 */
[[nodiscard]] SquareLattice GenerateUlamSpiral(int dim);

}  // namespace ulam

#endif
