CC = cc
AR = ar
RANLIB = ranlib
CTAGS = ctags

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

LIB = libdynarr.a
OBJ = dynarr.o

HDR = dynarr.h
SRC = $(OBJ:.o=.c)

all: $(LIB)
dynarr.o: dynarr.h

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

tags: $(SRC) $(HDR)
	$(CTAGS) $(SRC) $(HDR)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $<
