#!/bin/sh

ROMNAME=gb-starter

mkdir build -p
rgbasm -o build/$ROMNAME.o -i src/ -i data/ src/main.asm
rgblink -o build/$ROMNAME.gb build/$ROMNAME.o
rgbfix -v -p0 build/$ROMNAME.gb