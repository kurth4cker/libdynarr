CC = cc
AR = ar
RANLIB = ranlib
CTAGS = ctags

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

TESTDIR = ../libdynarr-tests
TESTBIN = $(TESTDIR)/dynarr-test

LIB = libdynarr.a
OBJ = dynarr.o

HDR = dynarr.h
SRC = $(OBJ:.o=.c)

all: $(LIB)

$(LIB): $(OBJ)
	$(AR) -rc $@ $(OBJ)
	-$(RANLIB) $@

clean:
	rm -f $(LIB) *.o
	@-make -C $(TESTDIR) clean

$(TESTBIN): $(LIB) $(HDR)
	@rm -f $(TESTBIN)
	@make -C $(TESTDIR) LIBDYNARR_DIR=$$PWD

check test: $(TESTBIN)
	@make -C $(TESTDIR) test LIBDYNARR_DIR=$$PWD

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

.PHONY: all clean check test install uninstall
