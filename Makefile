CC = cc
AR = ar
RANLIB = ranlib

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

LIB = libdynarr.a
HDR = dynarr.h

OBJ = init.o term.o

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) -rc $@ $(OBJ)
	-$(RANLIB) $@

clean:
	rm -f $(LIB) *.o

check test: $(LIB) $(HDR)
	@make -C test

install: $(LIB) $(HDR)
	mkdir -p $(DESTDIR)$(LIBDIR) $(DESTDIR)$(INCDIR)
	cp -f $(LIB) $(DESTDIR)$(LIBDIR)
	cp -f $(HDR) $(DESTDIR)$(INCDIR)

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/$(LIB)
	rm -f $(DESTDIR)$(INCDIR)/$(HDR)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean check test install uninstall
