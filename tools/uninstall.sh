#!/bin/sh

echo "I'm sorry to see you go"
echo "Do you also want to uninstall SDl2 and SDL2_Image (y/n)"
read sdl

if [ $sdl = "y" ]
then
    echo "Deleting SDL2 and SDL2_Image"
    if [ `uname -s` = "Darwin" ]; then
        echo "System: macOS"
        brew uninstall sdl2
        brew uninstall sdl2_Image
    fi

    if [ `uname -s` = "Linux" ]; then
        echo "System: Linux"
        apt-get –-purge remove libsdl2-dev
        apt-get –-purge remove libsdl2-image-dev
    fi

    if [ `uname -s` = "MINGW32_NT-6.1" ]; then
        echo "System: MinGW"
        pacman -R mingw-w64-i686-SDL2
        pacman -R mingw-w64-i686-SDL2_image
    fi
fi

echo "Deleting Photorealistic"
rm -rf ../..Photorealistic
