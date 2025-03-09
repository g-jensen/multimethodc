CC = gcc
SRC = src
SPEC = specc
SRC_FILES != find $(SRC) -name '*.c'
SPEC_FILES != find $(SPEC) -name '*.c'

main: compile-main
	$(CC) *.o -o cclj

spec-auto:
	find . -name '*.[ch]' | entr make spec

spec: compile-spec
	$(CC) *.o -o cclj-specc
	./cclj-specc

compile-spec: compile-src
	$(CC) -c $(SPEC_FILES)

compile-main: compile-src
	$(CC) -c main.c

compile-src:
	$(CC) -c $(SRC_FILES)

clean:
	rm -f *.o