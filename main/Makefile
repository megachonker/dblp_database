CC ?= gcc
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm

go:	tests
	./tests

tests:	tests.o parsing.o
	$(CC) -o tests  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -f tests




