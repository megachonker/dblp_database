CCA ?= cc -O0
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm -pthread -ftest-coverage -fprofile-arcs


//OK
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

# %.gcno: %.c
# 	$(CCA) -o $@ -c $< $(CFLAGS)

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
	doxygen Doxyfile
	firefox html/index.html

callgrind:	bench
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace ./bench unwrwap_gen_cache
	kcachegrind callgrind_trace
	rm callgrind_trace
# lunch kprok pour profiler le temps d'execution

Update: DATA/dblp.xml
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

DATA/Serialzed1000.data: 	DATA/dblp1sur8.xml
	./bench serializedsmall

DATA/SerializedStrucInverse1000.data:	DATA/Serialzed1000.data
	./bench unwrwap_gen_cache_small

#LA
DATA/SerializedStrucInverse.data: DATA/SerializedStruc.data
	./bench unwrwap_gen_cache

gen_cache_data: DATA/dblp.xml DATA/dblp1sur8.xml DATA/SerializedStrucInverse.data DATA/Serialzed1000.data DATA/SerializedStruc.data DATA/SerializedStrucInverse1000.data

r: clean abench.sh

clean:
	rm -f  *.o *.so *.gcno *.gcda *.gcov coverage.info
	rm -fr tests bench main GCOVtests LcovRapport html latex
# Update
cleanall: clean 
	rm -f DATA/SerializedStrucInverse.data\
		DATA/dblp1sur8.xml\
		DATA/SerializedStruc.data\
		DATA/Serialzed1000.data\
		DATA/SerializedStrucInverse1000.data\




# instaler doxygene est lcov