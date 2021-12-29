CCA ?= cc 
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm -pthread -ftest-coverage -fprofile-arcs

go:	tests abench.sh
	./tests

abench.sh: bench gen_cache_data

bench:	bench.o parsing.o list.o unwrap.o
	$(CCA) -o bench  $^ $(CFLAGS) $(LDLIBS)

tests:	tests.o parsing.o list.o unwrap.o
	$(CCA) -o tests  $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o
	$(CCA) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CCA) -o $@ -c $< $(CFLAGS)

%.gcno: %.c
	$(CCA) -o $@ -c $< $(CFLAGS)

raport: bench.c parsing.c list.c unwrap.c
	$(CCA) -O0 -o GCOVtests  $^ $(CFLAGS) $(LDLIBS)
	./GCOVtests unwrwap_deserialise
	./GCOVtests serialized
	./GCOVtests unwrwap_gen_cache
	gcov -abcfu bench.c parsing.c list.c unwrap.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory LcovRapport
	firefox LcovRapport/main/index.html

doc:
	doxygen .
	firefox html/index.html

xml_Update: DATA/dblp.xml
	if [ $$(curl https://dblp.uni-trier.de/xml/ |grep dblp.xml.gz.md5|grep -o ">202.-..-.."|tr -d ">") != $$(stat DATA/dblp.xml -c %y|cut -d " " -f 1) ];  then rm DATA/dblp.xml ; make DATA/dblp.xml ; fi

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
	rm -f  *.o *.so *.gcno *.gcda *.gcov coverage.info
	rm -fr tests bench main GCOVtests LcovRapport html latex

cleanall: clean xml_Update
	rm -f DATA/SerializedStrucInverse.data\
		DATA/dblp1sur8.xml\
		DATA/SerializedStruc.data\
		DATA/Serialzed1000.data\


