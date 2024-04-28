#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "spiral/spiral.h"

static void PrintUsage() {
  std::cout << "usage: uspiral [OPTION]..." << std::endl;
  std::cout << "visualize the Ulam spiral" << std::endl;
  std::cout << "\t-d, --dimension DIM\n\t\tmatrix dimension" << std::endl;
  std::cout << "\t-h, --help\n\t\tprint this help page" << std::endl;
}

int main(int argc, char** argv) {
  std::vector<struct option> longopts{
      {"dimension", required_argument, 0, 'd'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0},
  };

  int opt = 0;
  int long_index = 0;
  std::size_t dim = 0;
  while (-1 !=
         (opt = ::getopt_long(argc, argv, "d:h", &longopts[0], &long_index))) {
    switch (opt) {
      case 'd':
        dim = std::stoull(optarg);
        break;
      case 'h':
        PrintUsage();
        std::exit(EXIT_SUCCESS);
      case '?':
        std::exit(EXIT_FAILURE);
    }
  }

  ulam::SquareLattice ulam_mat = ulam::GenerateUlamSpiral(dim);
  /* TODO: Add visualization code. */

  std::exit(EXIT_SUCCESS);
}
