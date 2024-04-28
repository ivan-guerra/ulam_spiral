#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "spiral/image.h"
#include "spiral/spiral.h"

static void PrintUsage() {
  std::cout << "usage: uspiral [OPTION]... IMAGE" << std::endl;
  std::cout << "visualize the Ulam spiral" << std::endl;
  std::cout << "\tIMAGE\n\t\toutput png filepath" << std::endl;
  std::cout << "\t-d, --dimension DIM\n\t\tsquare matrix dim (default 201)"
            << std::endl;
  std::cout << "\t-h, --help\n\t\tprint this help page" << std::endl;
}

static void PrintErrAndExit(const std::string& err_msg) {
  std::cerr << "error: " << err_msg;
  std::exit(EXIT_FAILURE);
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

  if (!argv[optind]) {
    PrintErrAndExit("output image filepath not specified");
  }

  auto ulam_mat = ulam::GenerateUlamSpiral(dim);
  if (!ulam_mat) {
    PrintErrAndExit("invalid dimension " + std::to_string(dim));
    std::exit(EXIT_FAILURE);
  }

  ulam::WriteLatticeToPng(argv[optind], *ulam_mat);

  std::exit(EXIT_SUCCESS);
}
