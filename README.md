# Ulam Spiral

<p align="center">
  <img src="resources/spiral.webp" />
</p>

`uspiral` is command line utility that outputs a visualization of the [Ulam
spiral][1] in the form of a grayscale image. `uspiral` can generate spiral
images with dimensions in the range `[128, 4096]`. Many [image formats][2] are
supported including PNG, JPEG, and Webp. See below for the program usage.

```bash
Visualize the Ulam spiral.

Usage: uspiral [OPTIONS] <OUTPUT_FILE>

Arguments:
  <OUTPUT_FILE>  output image path (e.g., /foo/bar/ulam.png)

Options:
  -d, --dimension <DIMENSION>  image dimension [default: 256]
  -h, --help                   Print help
  -V, --version                Print version
```

[1]: https://en.wikipedia.org/wiki/Ulam_spiral#
[2]: https://github.com/image-rs/image/blob/main/README.md#supported-image-formats
