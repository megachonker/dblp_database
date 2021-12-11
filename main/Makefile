CC ?= gcc
CFLAGS ?= -Wall -Wextra -g -O0
LDLIBS ?= -lm
BENCHNUMBER ?= deserialisedb

go:	tests
	./tests

bench:	bench.o parsing.o list.o unwrap.o
	$(CC) -o bench  $^ $(CFLAGS) $(LDLIBS)
	# bench $(BENCHNUMBER)

tests:	tests.o parsing.o list.o
	$(CC) -o tests  $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o
	$(CC) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


DATA/dblp.xml:
	rm -f dblp.xml.gz
	wget https://dblp.uni-trier.de/xml/dblp.xml.gz
	gzip dblp.xml.gz -d
	mv dblp.xml DATA/dblp.xml
	rm -f dblp.xml.gz

DATA/dblp1sur8.xml: DATA/dblp.xml
	head DATA/dblp.xml -n 10966843 > DATA/dblp1sur8.xml

DATA/SerializedStruc.data:	bench DATA/dblp.xml
	./bench "serialized"

DATA/Serialzed1000.data: 	DATA/SerializedStruc.data
	head DATA/SerializedStruc.data -n 1002 > DATA/Serialzed1000.data

safetest: bench DATA/dblp.xml DATA/dblp1sur8.xml DATA/SerializedStruc.data DATA/Serialzed1000.data
	valgrind ./bench ALL



clean:
	rm -f *.o
	rm -f tests bench main tests
	rm -f	DATA/dblp1sur8.xml\
		DATA/SerializedStruc.data\
		DATA/Serialzed1000.data\
		
		



