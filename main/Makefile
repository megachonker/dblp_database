CC ?= gcc
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm
BENCHNUMBER ?= deserialisedb

go:	tests
	./tests


test_creation_Gt:	test_creation_Gt.o creation_Gt.o list-makefile-2/linked-list.o parsing.o
	$(CC) -o test_creation_Gt -g $^ $(CFLAGS) $(LDLIBS)
	# bench $(BENCHNUMBER)

bench:	bench.o parsing.o
	$(CC) -o bench  $^ $(CFLAGS) $(LDLIBS)
	# bench $(BENCHNUMBER)

tests:	tests.o parsing.o
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


