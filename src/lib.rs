//! `ulam_spiral` provides a library for generating NxN [Ulam
//! spirals](https://en.wikipedia.org/wiki/Ulam_spiral#). A binary, `uspiral`, is also provided
//! which allows the user to generate a visualization of a Ulam spiral as a grayscale image. Any
//! [image format](https://github.com/image-rs/image/blob/main/README.md#supported-image-formats)
//! supported by the [image] crate may be used.
use array2d::Array2D;
use image::{GrayImage, Luma};
use primal::Sieve;
use std::error::Error;
use std::path::{Path, PathBuf};

const MIN_DIMENSION: u16 = 128;
const MAX_DIMENSION: u16 = 4096;

#[doc(hidden)]
pub struct Config {
    pub dimension: u16,
    pub output_file: PathBuf,
}

impl Config {
    pub fn build(dimension: u16, output_file: PathBuf) -> Config {
        Config {
            dimension,
            output_file,
        }
    }
}

/// Returns the Ulam spiral matrix of size `n x n`.
///
/// # Examples
///
/// ```rust
/// let expected_matrix = vec![
///     vec![37, 0, 0, 0, 0, 0, 31],
///     vec![0, 17, 0, 0, 0, 13, 0],
///     vec![0, 0, 5, 0, 3, 0, 29],
///     vec![0, 19, 0, 0, 2, 11, 0],
///     vec![41, 0, 7, 0, 0, 0, 0],
///     vec![0, 0, 0, 23, 0, 0, 0],
///     vec![43, 0, 0, 0, 47, 0, 0],
/// ];
/// assert_eq!(ulam_spiral::generate_ulam_matrix(7).as_rows(), expected_matrix);
/// ```
pub fn generate_ulam_matrix(n: usize) -> Array2D<u32> {
    enum Direction {
        North(i32, i32),
        South(i32, i32),
        East(i32, i32),
        West(i32, i32),
    }

    // Initialize the matrix with zeros.
    let mut matrix = Array2D::filled_with(0, n, n);
    let mut x = n / 2;
    let mut y = n / 2;
    let mut num: u32 = 1;

    // Counter clockwise movement: right, up, left, down.
    let directions = [
        Direction::East(1, 0),
        Direction::North(0, -1),
        Direction::West(-1, 0),
        Direction::South(0, 1),
    ];

    let sieve = Sieve::new(n * n);
    let mut step = 1;
    while num <= (n * n) as u32 {
        for (i, direction) in directions.iter().enumerate() {
            // Match against the enum to extract dx and dy.
            let (dx, dy) = match direction {
                Direction::North(dx, dy) => (*dx, *dy),
                Direction::South(dx, dy) => (*dx, *dy),
                Direction::East(dx, dy) => (*dx, *dy),
                Direction::West(dx, dy) => (*dx, *dy),
            };

            for _ in 0..step {
                if x < n && y < n && matrix[(y, x)] == 0 {
                    if sieve.is_prime(num as usize) {
                        matrix[(y, x)] = num;
                    } else {
                        matrix[(y, x)] = 0;
                    }
                    num += 1;
                }

                // Move in the current direction.
                x = ((x as isize) + dx as isize) as usize;
                y = ((y as isize) + dy as isize) as usize;

                if num > (n * n) as u32 {
                    return matrix;
                }
            }

            // Increase step size after completing a vertical movement (down or up).
            if i % 2 == 1 {
                step += 1;
            }
        }
    }

    matrix
}

/// Writes the Ulam spiral matrix as a grayscale image to the specified output file.
pub fn write_ulam_img(n: usize, output_file: &Path) -> Result<(), Box<dyn Error>> {
    let matrix = generate_ulam_matrix(n);
    let mut img = GrayImage::new(n as u32, n as u32);

    img.enumerate_pixels_mut().for_each(|(x, y, pixel)| {
        let value = match matrix[(y as usize, x as usize)] {
            0 => 255,
            _ => 0,
        };
        *pixel = Luma([value]);
    });

    img.save(output_file)?;

    Ok(())
}

#[doc(hidden)]
pub fn run(config: &Config) -> Result<(), Box<dyn Error>> {
    if !(MIN_DIMENSION..=MAX_DIMENSION).contains(&config.dimension) {
        return Err(format!(
            "dimension {} is outside of the range of allowed dimensions [{},{}]",
            config.dimension, MIN_DIMENSION, MAX_DIMENSION
        )
        .into());
    }

    write_ulam_img(config.dimension.into(), &config.output_file)?;

    Ok(())
}

#[cfg(test)]
mod test {
    use crate::{generate_ulam_matrix, run, Config, MAX_DIMENSION, MIN_DIMENSION};
    use std::path;
    use testdir::testdir;

    #[test]
    fn dimension_of_zero_results_in_empty_matrix() {
        let matrix = generate_ulam_matrix(0);
        assert_eq!(matrix.num_elements(), 0);
    }

    #[test]
    fn generate_ulam_spiral_returns_valid_7_by_7_matrix() {
        // 7x7 matrix taken from the Wikipedia page:
        // https://en.wikipedia.org/wiki/Ulam_spiral#Construction
        let expected_matrix = vec![
            vec![37, 0, 0, 0, 0, 0, 31],
            vec![0, 17, 0, 0, 0, 13, 0],
            vec![0, 0, 5, 0, 3, 0, 29],
            vec![0, 19, 0, 0, 2, 11, 0],
            vec![41, 0, 7, 0, 0, 0, 0],
            vec![0, 0, 0, 23, 0, 0, 0],
            vec![43, 0, 0, 0, 47, 0, 0],
        ];
        let actual_matrix = generate_ulam_matrix(7);
        assert_eq!(actual_matrix.as_rows(), expected_matrix);
    }

    #[test]
    fn run_returns_error_on_too_small_dimension() {
        let config = Config::build(MIN_DIMENSION - 1, path::PathBuf::from("/foo/bar/test.png"));
        let result = run(&config);
        assert!(
            result.is_err(),
            "expect the error regarding too small dimension value"
        );
    }

    #[test]
    fn run_returns_error_on_too_large_dimension() {
        let config = Config::build(MAX_DIMENSION + 1, path::PathBuf::from("/foo/bar/test.png"));
        let result = run(&config);
        assert!(
            result.is_err(),
            "expect the error regarding too large dimension value"
        );
    }

    #[test]
    fn run_succeeds_with_valid_dimension() {
        let test_dir: path::PathBuf = testdir!();
        let path = test_dir.join("output.png");

        let config = Config::build(256, path);
        assert!(run(&config).is_ok());
    }

    #[test]
    fn run_succeeds_with_min_dimension() {
        let test_dir: path::PathBuf = testdir!();
        let path = test_dir.join("output.png");

        let config = Config::build(MIN_DIMENSION, path);
        assert!(run(&config).is_ok());
    }

    #[test]
    fn run_succeeds_with_max_dimension() {
        let test_dir: path::PathBuf = testdir!();
        let path = test_dir.join("output.png");

        let config = Config::build(MAX_DIMENSION, path);
        assert!(run(&config).is_ok());
    }
}
