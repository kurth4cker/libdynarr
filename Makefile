CC = cc
AR = ar
RANLIB = ranlib

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

LIB = libvector.a
HDR = vector.h

OBJ = vector.o

all: $(LIB)
vector.o: vector.h

$(LIB): $(OBJ)
	$(AR) -rc $@ $(OBJ)
	-$(RANLIB) $@

clean:
	rm -f $(LIB) *.o

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
