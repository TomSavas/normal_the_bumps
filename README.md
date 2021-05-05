# Normal the Bumps
Converts bump maps (jpg, png, bmp, tga...) into normal maps (jpg).

## Building
As simple as `clang -O2 -lm main.c -o normal_the_bumps`

## Usage
`./normal_the_bumps your_bump_map.png output_normal.jpg`

## Dependencies
Uses stb_image and stb_image_write from [the wonderful stb repo](https://github.com/nothings/stb).

## Licence
This project is licensed under MIT License - see [LICENCE](LICENCE) file for details.
