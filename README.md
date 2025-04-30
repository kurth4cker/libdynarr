# libdynarr
Simple dynamic array implementation in C. [WIP]

## Building
Standart Makefile. Here are building and testing samples:

    # bootstrap build system
    cc -o nob nob.c

    # build the library
    ./nob


## Using Library
Just simple library. Use it as system library or copy both of dynarr.c and
dynarr.h into your project tree.

    # copy it to your source tree
    cc -o sample main.c dynarr.c


## Copying
Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
