#include "spiral/spiral.h"

#include <gtest/gtest.h>

#include <fstream>
#include <optional>
#include <sstream>
#include <string>

static const char* kUlamSpiral201Path = "data/uspiral_201.txt";

[[nodiscard]] static ulam::SquareLattice LoadLattice(
    const std::string& filepath) {
  ulam::SquareLattice lattice;

  std::ifstream fhandle(filepath);
  std::string line;
  while (std::getline(fhandle, line)) {
    ulam::RowVect row;
    std::stringstream ss(line);
    std::string value;
    while (ss >> value) {
      row.push_back(std::stoi(value));
    }
    lattice.push_back(row);
  }
  return lattice;
}

TEST(SpiralTest, GenUlamSpiralWithZeroDimReturnsNullopt) {
  std::optional<ulam::SquareLattice> lattice = ulam::GenerateUlamSpiral(0);

  ASSERT_FALSE(lattice);
}

TEST(SpiralTest, GenUlamSpiralWithNegativeDimReturnsNullopt) {
  std::optional<ulam::SquareLattice> lattice = ulam::GenerateUlamSpiral(-1);

  ASSERT_FALSE(lattice);
}

TEST(SpiralTest, GenUlamSpiralWithValidDimReturnsCorrectUlamSpiralLattice) {
  ulam::SquareLattice expected = LoadLattice(kUlamSpiral201Path);
  std::optional<ulam::SquareLattice> actual = ulam::GenerateUlamSpiral(201);

  ASSERT_TRUE(actual);
  ASSERT_EQ(expected, *actual);
}
