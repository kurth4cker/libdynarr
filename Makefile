CC = cc
AR = ar
RANLIB = ranlib
CTAGS = ctags

CFLAGS = -g -Wall -Wextra

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
INCDIR = $(PREFIX)/include

LIB = libdynarr.a
OBJ = dynarr.o

HDR = dynarr.h
SRC = $(OBJ:.o=.c)

TESTBIN = run-tests
TESTOBJ = test/main.o test/munit.o

all: $(LIB)
$(OBJ): dynarr.h
$(TESTOBJ): dynarr.h test/munit.h

$(LIB): $(OBJ)
	$(AR) -rc $@ $(OBJ)
	-$(RANLIB) $@

$(TESTBIN): $(TESTOBJ) $(LIB)
	$(CC) $(LDFLAGS) -o $@ $(TESTOBJ) $(LIB)

check: $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -f $(LIB) *.o $(TESTBIN) test/*.o tags

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
	$(CC) $(CFLAGS) -c -o $@ $<
