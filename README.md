# libdynarr
Simple dynamic array implementation in C. [WIP]

## Installation
Just simple and portable Makefile. Run `make` for compile and `make install`
for install.

Here are some customization options:

* CC, AR, RANLIB: Standard programs for building a C library.
* PREFIX: Installation prefix. (default: /usr/local)
* LIBDIR, INCDIR: Very specific installation locations. (default: `$PREFIX/lib`
  and `$PREFIX/include`)
* CFLAGS: Flags passed to $CC.

## Copying
Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
