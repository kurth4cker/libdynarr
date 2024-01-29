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
	mkdir -p $(LIBDIR) $(INCDIR)
	cp -f $(LIB) $(LIBDIR)
	cp -f $(HDR) $(INCDIR)

uninstall:
	rm -f $(LIBDIR)/$(LIB)
	rm -f $(INCDIR)/$(HDR)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
