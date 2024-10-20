PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include

CC = cc
AR = ar
RANLIB = ranlib
CTAGS = ctags

CFLAGS = -g -pedantic
LDFLAGS =
LDLIBS =


DYNARR_CFLAGS = -std=c23 $(CFLAGS)

LIB = libdynarr.a
OBJECTS = dynarr.o

HEADER = dynarr.h

all: $(LIB)

$(OBJECTS): $(HEADER)

$(LIB): $(OBJECTS)
	$(AR) -rc $@ $(OBJECTS)
	-$(RANLIB) $@

clean:
	rm -f $(LIB) *.o test/*.o tags

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
