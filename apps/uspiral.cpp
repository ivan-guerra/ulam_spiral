#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "spiral/spiral.h"

static void PrintUsage() {
  std::cout << "usage: uspiral [OPTION]..." << std::endl;
  std::cout << "visualize the Ulam spiral" << std::endl;
  std::cout << "\t-d, --dimension DIM\n\t\tmatrix dimension (default 201)"
            << std::endl;
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
  int dim = 201;
  while (-1 !=
         (opt = ::getopt_long(argc, argv, "d:h", &longopts[0], &long_index))) {
    switch (opt) {
      case 'd':
        dim = std::stoi(optarg);
        break;
      case 'h':
        PrintUsage();
        std::exit(EXIT_SUCCESS);
      case '?':
        std::exit(EXIT_FAILURE);
    }
  }

  auto ulam_mat = ulam::GenerateUlamSpiral(dim);
  if (ulam_mat) {
    /* TODO: Add visualization code. */
  } else {
    std::cerr << "error: invalid dimension " << dim << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::exit(EXIT_SUCCESS);
}
