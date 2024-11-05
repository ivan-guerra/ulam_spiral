pub fn generate_spiral_matrix(n: usize) -> Vec<Vec<u32>> {
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
