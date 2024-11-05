use std::error::Error;
use std::path::Path;

fn main() -> Result<(), Box<dyn Error>> {
    let outfile = Path::new("test.png");
    ulam_spiral::write_ulam_img(256, outfile)?;

    Ok(())
}
