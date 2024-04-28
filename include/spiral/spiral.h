#ifndef SPIRAL_H_
#define SPIRAL_H_

#include <vector>

namespace ulam {

using RowVect = std::vector<int>;
using SquareLattice = std::vector<RowVect>;

[[nodiscard]] bool IsPrime(int n);
[[nodiscard]] SquareLattice GenerateUlamSpiral(int dim);

}  // namespace ulam

#endif
