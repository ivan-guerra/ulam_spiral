#ifndef SPIRAL_H_
#define SPIRAL_H_

#include <optional>
#include <vector>

namespace ulam {

using RowVect = std::vector<int>;
using SquareLattice = std::vector<RowVect>;

/**
 * \brief Generate a \p dim x \p dim Ulam Spiral matrix.
 * \details See https://en.wikipedia.org/wiki/Ulam_spiral# for the details.
 * \returns A Ulam Spiral lattice with the parameter dimension. If \p dim is
 *          less than or equal to zero, std::nullopt is returned.
 */
[[nodiscard]] std::optional<SquareLattice> GenerateUlamSpiral(int dim);

}  // namespace ulam

#endif
