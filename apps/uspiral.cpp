#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "graphics/screen.h"
#include "spiral/spiral.h"

static void PrintUsage() {
  std::cout << "usage: uspiral [OPTION]..." << std::endl;
  std::cout << "visualize the Ulam spiral" << std::endl;
  std::cout << "\t-d, --dimension DIM\n\t\tmatrix dimension (default 201)"
            << std::endl;
  std::cout << "\t-h, --help\n\t\tprint this help page" << std::endl;
}

static void PrintErrAndExit(const std::string& err_msg) {
  std::cerr << "error: " << err_msg;
  std::exit(EXIT_FAILURE);
}

static void RunDrawLoop(const ulam::SquareLattice& ulam_mat) {
  std::optional<ulam::ScreenDimension> screen_dim = ulam::InitScreen();
  if (!screen_dim) {
    PrintErrAndExit("failed to initialize screen");
  }

  /* Draw the Ulam Spiral lattice on screen. */
  int rlimit = static_cast<int>(ulam_mat.size());
  int climit = static_cast<int>(ulam_mat[0].size());
  for (int i = 0; i < rlimit; ++i) {
    for (int j = 0; j < climit; ++j) {
      if (ulam_mat[i][j]) {
        ulam::DrawChar({.x = j, .y = i}, '*', ulam::Color::kWhite);
      }
    }
  }

  /* Print a banner telling the user how to exit. */
  ulam::DrawStr("press any key to quit", {.x = 0, .y = screen_dim->height - 1});

  /* Wait for the user to press a key before cleaning up. */
  while (!ulam::UserPressedKey()) {
  }

  /* Cleanup. */
  ulam::TerminateScreen();
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
    RunDrawLoop(*ulam_mat);
  } else {
    PrintErrAndExit("invalid dimension " + std::to_string(dim));
    std::exit(EXIT_FAILURE);
  }
  std::exit(EXIT_SUCCESS);
}
