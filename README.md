
<img src="graphics/banner.png">

![license-mit](https://img.shields.io/github/license/platinum-phoenix/Photorealistic)
![C/C++ CI](https://github.com/Platinum-Phoenix/Photorealistic/workflows/C/C++%20CI/badge.svg)


# Table of Contents
- [About](#About)
- [Dependencies](#Dependencies)
- [Building](#Building)
- [Notes](#Notes)
- [Credits](#Credits)

# About
Photorealistic is a low-dependency Ray Tracing Engine to generate photorealistic images.

Supported Systems:
- macOS
- Linux (in theory)
- Windows MYSYS2 (in theory)

# Dependencies

You will need [SDL2](http://www.libsdl.org):
```shell
Linux:
    apt-get install libsdl2-dev
Mac OS X:
    brew install sdl2
MSYS2:
    pacman -S mingw-w64-i686-SDL2
```

You will also need [SDL Image](https://www.libsdl.org/projects/SDL_image/):
```shell
Linux:
    apt-get install libsdl2-image-dev
macOS:
    brew install sdl_image
MSYS2:
    pacman -S mingw-w64-i686-SDL2_image
```

Yup, those are the two dependencies, the rest are built with the project.

# Building

To build make sure you have managed the [dependencies](#Dependencies)


Then run:
```sh
git clone https://github.com/Platinum-Phoenix/Photorealistic
cd Photorealistic
make
```
It should generate an executable named "Photorealistic"

Running:
```sh
./Photorealistic
```

# Contributing

You can help by:
- Reporting and issue
- Creating a fork and doing a pull-request
# Notes
- To use the tools (found in the tools direcotry) you may need to run:
```sh
chmod +x tools/*.sh
```
# Credits
* [_libSDL_](https://libsdl.org) 
for [SDL_Image](https://www.libsdl.org/projects/SDL_image/) 
and [SDL2](http://www.libsdl.org)
* [_imgui_](https://github.com/ocornut/imgui) 
for the gui library
* [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) 
for majority of the [core](src/core)
