include config.mk

LIB = libdynarr.a
OBJ = dynarr.o

HEADER = dynarr.h

all: $(LIB)

$(OBJ): dynarr.h

$(LIB): $(OBJ)
	$(AR) -rc $@ $(OBJ)
	-$(RANLIB) $@

TESTBIN = run-tests
TESTOBJ = test/main.o test/munit.o

$(TESTOBJ): dynarr.h test/munit.h

$(TESTBIN): $(TESTOBJ) $(LIB)
	$(CC) $(TEST_LDFLAGS) -o $@ $(TESTOBJ) $(LIB) $(TEST_LDLIBS)

check: $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -f $(LIB) *.o $(TESTBIN) test/*.o tags

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
