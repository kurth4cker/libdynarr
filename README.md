# libdynarr
Simple dynamic array implementation in C. [WIP]

## Building
Standart Makefile. Here are building and testing samples:

    # build library
    make

    # run test suite
    make check

    # install library
    make install

## Using Library
Just simple library. Use it as system library or copy both of dynarr.c and
dynarr.h into your project tree.

    # as system library
    # requires libdynarr to be installed on your system at building
    cc -o sample main.c -ldynarr

    # copy it to your source tree
    cc -o sample main.c dynarr.c

## Copying
Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
