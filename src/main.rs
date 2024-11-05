use clap::Parser;
use std::error::Error;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    #[arg(help = "output image path (e.g., /foo/bar/ulam.png)")]
    output_file: String,

    #[arg(short, long, default_value_t = 256, help = "image dimension")]
    dimension: u16,
}

fn main() -> Result<(), Box<dyn Error>> {
    let args = Args::parse();
    let config = ulam_spiral::Config::build(args.dimension, args.output_file.into());

    ulam_spiral::run(&config)?;

    Ok(())
}
