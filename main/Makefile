CC ?= gcc
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm
BENCHNUMBER ?= deserialisedb

go:	tests
	./tests

bench:	bench.o parsing.o
	$(CC) -o bench  $^ $(CFLAGS) $(LDLIBS)
	# bench $(BENCHNUMBER)

tests:	tests.o parsing.o list.o
	$(CC) -o tests  $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o
	$(CC) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


# DATA/dblp1sur8.xml:	DATA/dblp.xml
# 	head DATA/dblp.xml -n 10966843 > DATA/dblp1sur8.xml

clean:
	rm -rf *.o
	rm -f tests bench main
	rm DATA/Serialzed1000.data DATA/SerializedStruc.data DATA/dblp1sur8.xml


