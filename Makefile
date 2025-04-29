PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

CC = cc
AR = ar
RANLIB = ranlib

CFLAGS = -g -pedantic -Wall -Wextra -Werror
LDFLAGS =
LDLIBS =


DYNARR_CFLAGS = -std=c11 $(CFLAGS)

LIB = libdynarr.a
OBJECTS = dynarr.o

EXAMPLE_PROGRAM = example

HEADER = dynarr.h

all: $(LIB) $(EXAMPLE_PROGRAM)

$(EXAMPLE_PROGRAM): $(LIB)

$(OBJECTS): $(HEADER)

$(LIB): $(OBJECTS)
	$(AR) -rc $@ $(OBJECTS)
	-$(RANLIB) $@

clean:
	rm -f $(LIB) $(EXAMPLE_PROGRAM) *.o

install: $(LIB) $(HEADER)
	mkdir -p $(DESTDIR)$(LIBDIR) $(DESTDIR)$(INCLUDEDIR)
	cp -f $(LIB) $(DESTDIR)$(LIBDIR)
	cp -f $(HEADER) $(DESTDIR)$(INCLUDEDIR)

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(LIB)
	rm -f $(DESTDIR)$(INCLUDEDIR)/$(HEADER)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(DYNARR_CFLAGS) -c -o $@ $<

.c:
	$(CC) $(DYNARR_CFLAGS) $(LDFLAGS) -o $@ $< $(LIB) $(LDLIBS)
