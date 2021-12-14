CC ?= gcc
CFLAGS ?= -Wall -Wextra -g -O0
LDLIBS ?= -lm
BENCHNUMBER ?= deserialisedb

go:	tests abench.sh
	./tests

abench.sh: bench gen_cache_data

bench:	bench.o parsing.o list.o unwrap.o
	$(CC) -o bench  $^ $(CFLAGS) $(LDLIBS)

tests:	tests.o parsing.o list.o unwrap.o
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

#regénère tout les fichier lier a bench quand un .o change Ces regretabkle donc on enleve bench par .O
DATA/SerializedStruc.data:	DATA/dblp.xml parsing.o
	./bench serialized

DATA/Serialzed1000.data: 	DATA/SerializedStruc.data
	head DATA/SerializedStruc.data -n 1002 > DATA/Serialzed1000.data

#LA
DATA/SerializedStrucInverse.data: DATA/SerializedStruc.data
	./bench unwrwap_gen_cache

gen_cache_data: DATA/dblp.xml DATA/dblp1sur8.xml DATA/SerializedStrucInverse.data DATA/Serialzed1000.data DATA/SerializedStruc.data


clean:
	rm -f *.o
	rm -f tests bench main
	rm -f DATA/SerializedStrucInverse.data\
		DATA/dblp1sur8.xml\
		DATA/SerializedStruc.data\
		DATA/Serialzed1000.data\
		
		



