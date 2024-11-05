fn main() {
    let matrix = ulam_spiral::generate_spiral_matrix(5);
    for row in matrix {
        println!("{:?}", row);
    }
}
