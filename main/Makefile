CC ?= gcc
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm
BENCHNUMBER ?= deserialisedb

# go:	tests
# 	./tests

bench:	bench.o parsing.o
	$(CC) -o bench  $^ $(CFLAGS) $(LDLIBS)
	# bench $(BENCHNUMBER)

tests:	tests.o parsing.o
	$(CC) -o tests  $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o
	$(CC) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -f tests bench main




