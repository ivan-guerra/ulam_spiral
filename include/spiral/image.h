#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>

#include "spiral/spiral.h"

namespace ulam {

/**
 * \brief Write the parameter Ulam Spiral to a PNG file.
 * \details In the output image, prime numbers are represented as black pixels
 *          and composite numbers are represented as white pixels.
 * \param [in] filename Path to an output PNG file.
 * \param [in] ulam_mat A Ulam Spiral lattice generated via a successful call
 *                      to ulam::GenerateUlamSpiral().
 */
void WriteLatticeToPng(const std::string& filename,
                       const ulam::SquareLattice& ulam_mat);

}  // namespace ulam

#endif
