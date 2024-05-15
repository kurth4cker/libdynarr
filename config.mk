PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

CC = cc
AR = ar
RANLIB = ranlib
CTAGS = ctags

CFLAGS = -g -pedantic -pedantic-errors -Wall -Wextra
LDFLAGS =
LDLIBS =


DYNARR_CFLAGS = $(CFLAGS)

TEST_CFLAGS = $(CFLAGS)
TEST_LDFLAGS = $(LDFLAGS)
TEST_LDLIBS = $(LDLIBS)
