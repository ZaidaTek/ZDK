# ZDK

ZaidaTek Development Kit



### Latest

`2025-09-12` -- The library has undergone significant changes, including to the its internal structure, most notably, ZT_SIZE has been set to a U64 instead of a (previously intentional) U32 format. ZTK conversion to Linux remains at large, more emphasis will be put on keeping present (likely collaterally deprecated) compatibility with Windows builds.

`2025-08-14` -- The library is presently undergoing the process of conversion to Linux-compatibility. This will then also be its primary platform.



## Description


The ZaidaTek Development Kit (ZDK) is a library originally designed to reduce boiler-plate-code in creating GUI-windows.

It is designed with (future) cross-platform compatibility in mind, though it presently only supports Windows systems, and has only been tested on 32-bit binaries.


## Deployments

1) [ZaidaScope](https://github.com/ZaidaTek/ZaidaScope), an Arduino-based, simple oscilloscope-software

2) [Seagull](https://github.com/ariebesehl/Seagull), a native Windows application implementing Conway's Game of Life


## Examples

1) [Hello World](https://github.com/ariebesehl/HelloWorld), a set of four example applications detailing basic usage of ZDK


## Components

ZDK's main components are:

1) ZTM, a basic wrapper for standard library, basic and other primitive functions and algorithms, mostly OS-agnostic

2) ZTL, an OS-dependent wrapper for shell, serial-device, high-precision-timing and threading functions

3) ZTK, an OS-dependent wrapper and module for pixel graphics, system-based windows and OpenGL rendering

Interfacing with these components are:

1) ZTX, a library that interfaces with zlib, libjpeg and libpng via ZTL to provide the necessary functions and modules for loading and saving JPG and PNG files

2) ZDX, a library interfacing with ZTL for data acquisition and rendering with serial-devices, used in ZaidaScope

3) ZUI, a library interfacing with ZTK to provide an OS-agnostic graphical-user-interface


## License

Copyright (C) 2019-2021 ZaidaTek and Andreas Riebesehl

This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License

For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
