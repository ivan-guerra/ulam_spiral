#include <iomanip>
#include <iostream>
#include <string>

#include "spiral/spiral.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }

  ulam::SquareLattice spiral = ulam::GenerateUlamSpiral(std::stoull(argv[1]));

  for (const ulam::RowVect& row : spiral) {
    for (const int& val : row) {
      std::cout << std::setw(2) << val << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
