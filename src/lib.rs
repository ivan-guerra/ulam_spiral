use image::{GrayImage, Luma};
use std::error::Error;
use std::path::{Path, PathBuf};

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

pub fn generate_ulam_matrix(n: usize) -> Vec<Vec<u32>> {
    let mut matrix = vec![vec![0; n]; n];
    let mut x = n / 2;
    let mut y = n / 2;
    let mut num: u32 = 1;

    // Clockwise movement: right, up, left, down.
    let directions = [(1, 0), (0, -1), (-1, 0), (0, 1)];
    let mut step = 1;

    while num <= (n * n) as u32 {
        for (i, &(dx, dy)) in directions.iter().enumerate() {
            for _ in 0..step {
                if x < n && y < n && matrix[y][x] == 0 {
                    matrix[y][x] = match primes::is_prime(num.into()) {
                        true => num,
                        false => 0,
                    };
                    num += 1;
                }

                // Move in the current direction.
                x = ((x as isize) + dx) as usize;
                y = ((y as isize) + dy) as usize;

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

pub fn write_ulam_img(n: usize, output_file: &Path) -> Result<(), Box<dyn Error>> {
    let matrix = generate_ulam_matrix(n);
    let mut img = GrayImage::new(n as u32, n as u32);

    img.enumerate_pixels_mut().for_each(|(x, y, pixel)| {
        let value = match matrix[y as usize][x as usize] {
            0 => 255,
            _ => 0,
        };
        *pixel = Luma([value]);
    });

    img.save(output_file)?;

    Ok(())
}

pub fn run(config: &Config) -> Result<(), Box<dyn Error>> {
    write_ulam_img(config.dimension.into(), &config.output_file)?;

    Ok(())
}
