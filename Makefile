CC = gcc
SRC = src
SPEC = spec
SPEC_FILES != find $(SPEC) -name '*.c'

main: compile-main
	$(CC) *.o -o multimethodc

spec-auto:
	find . -name '*.[ch]' | entr make spec

spec: compile-spec
	$(CC) *.o -o specc
	./specc

compile-spec:
	$(CC) -c $(SPEC_FILES)

compile-main:
	$(CC) -c example.c

clean:
	rm -f *.o