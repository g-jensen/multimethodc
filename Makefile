CC = gcc
SRC = src
SPEC = specc
SPEC_FILES != find $(SPEC) -name '*.c'

main: compile-main
	$(CC) *.o -o multimethodc

spec-auto:
	find . -name '*.[ch]' | entr make spec

spec: compile-spec
	$(CC) *.o -o cclj-specc
	./cclj-specc

compile-spec:
	$(CC) -c $(SPEC_FILES)

compile-main:
	$(CC) -c example.c

clean:
	rm -f *.o