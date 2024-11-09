use clap::Parser;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    #[arg(help = "output image path (e.g., /foo/bar/ulam.png)")]
    output_file: String,

    #[arg(
        short, 
        long, 
        default_value_t = 256, 
        value_parser = clap::value_parser!(u16).range(128..=4096),
        help = "image dimension"
    )]
    dimension: u16,
}

fn main() {
    let args = Args::parse();
    let config = ulam_spiral::Config::new(args.dimension, args.output_file.into());

    if let Err(e) = ulam_spiral::run(&config) {
        eprintln!("error: {}", e);
        std::process::exit(1);
    }
}
