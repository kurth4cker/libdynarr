# libdynarr
Simple dynamic array implementation in C. [WIP]

## Installation
Run `make` and then `make install`. You can set **PREFIX** and **DESTDIR**
for `make install`. Here are examples.

	# Install user home
	make install PREFIX=$HOME/.local

	# Install library files to lib64
	make install LIBDIR=/usr/local/lib64

	# Setup destdir to $PWD instead of system's root directory
	make install DESTDIR=$PWD

## Copying
Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
