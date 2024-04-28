#include <getopt.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "graphics/screen.h"
#include "spiral/spiral.h"

static void PrintUsage() {
  std::cout << "usage: uspiral [OPTION]..." << std::endl;
  std::cout << "visualize the Ulam spiral" << std::endl;
  std::cout << "\t-d, --dimension DIM\n\t\tmatrix dimension (default 201)"
            << std::endl;
  std::cout << "\t-o, --outfile FILE\n\t\toutput the matrix to file"
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

static void WriteToFile(const std::string& filepath,
                        const ulam::SquareLattice& ulam_mat) {
  std::ofstream os(filepath);
  if (!os) {
    PrintErrAndExit("unable to open '" + filepath + "' for writing");
  }

  for (const auto& row : ulam_mat) {
    for (const auto& val : row) {
      if (val) {
        os << '*';
      } else {
        os << ' ';
      }
    }
    os << std::endl;
  }
}

int main(int argc, char** argv) {
  enum class OutputType {
    kScreen,
    kFile,
  };

  std::vector<struct option> longopts{
      {"dimension", required_argument, 0, 'd'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0},
  };
  int opt = 0;
  int long_index = 0;
  OutputType out_type = OutputType::kScreen;
  int dim = 201;
  std::string outfile;
  while (-1 != (opt = ::getopt_long(argc, argv, "d:o:h", &longopts[0],
                                    &long_index))) {
    switch (opt) {
      case 'd':
        dim = std::stoi(optarg);
        break;
      case 'o':
        out_type = OutputType::kFile;
        outfile = optarg;
        break;
      case 'h':
        PrintUsage();
        std::exit(EXIT_SUCCESS);
      case '?':
        std::exit(EXIT_FAILURE);
    }
  }

  auto ulam_mat = ulam::GenerateUlamSpiral(dim);
  if (!ulam_mat) {
    PrintErrAndExit("invalid dimension " + std::to_string(dim));
    std::exit(EXIT_FAILURE);
  }

  switch (out_type) {
    case OutputType::kScreen:
      RunDrawLoop(*ulam_mat);
      break;
    case OutputType::kFile:
      WriteToFile(outfile, *ulam_mat);
      break;
  }

  std::exit(EXIT_SUCCESS);
}
