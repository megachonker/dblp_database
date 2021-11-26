CC ?= gcc
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm

go:	tests
	./tests

tests:	tests.o parsing.o
	$(CC) -o tests  $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o
	$(CC) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -f tests




