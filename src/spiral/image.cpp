#include "spiral/image.h"

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <boost/gil/typedefs.hpp>

#include "spiral/spiral.h"

namespace ulam {

void WriteLatticeToPng(const std::string& filename,
                       const ulam::SquareLattice& ulam_mat) {
  boost::gil::gray8_image_t img(ulam_mat.size(), ulam_mat.size());

  auto output_view = boost::gil::view(img);
  for (int row = 0; row < output_view.height(); ++row) {
    for (int col = 0; col < output_view.width(); ++col) {
      /* Prime numbers are output as black pixels whereas composite numbers are
       * output as white pixels. */
      if (ulam_mat[row][col]) {
        output_view(col, row) = boost::gil::gray8_pixel_t(0);
      } else {
        output_view(col, row) = boost::gil::gray8_pixel_t(255);
      }
    }
  }

  boost::gil::write_view(filename, boost::gil::const_view(img),
                         boost::gil::png_tag{});
}

}  // namespace ulam
