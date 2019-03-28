# Stress++

## Description

This is just a small stress-testing program I am writing that uses
Ackermann's function to stress the processor and test it's stability.

## Building

 * Just build the source the way you would any other CMake project (if you don't
know how, just Google it).

## Installing

* Arch Linux users: Stress++ can be install from the AUR under "stress++".
* Red Hat Linux users: In the releases section you can find stable versions of Stress++ packaged in
rpm format.
* Other people: build the CMake project using `cmake . -DCMAKE_BUILD_TYPE=Release` then run `make install`.
* Windows users: You guys will just have to build the source code. Google around the internet for how to build
CMake source; it's really not that difficult. At some point I might start Cross-Compiling Stress++ to Windows.
Anyone who would like to contribute by compiling for Windows, send me an email at: 
[jacomalan.12@gmail.com](mailto:jacomalan.12@gmail.com)
