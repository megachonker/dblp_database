CCA ?= cc -O0
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm -pthread -ftest-coverage -fprofile-arcs
# -lm -pthread

#gcc -shared -o libfoo.so foo.o

# graph:	creation_graphe_voisins creation_Gt test_creation_Gt
# 	./test_creation_Gt

graphe: fonctions_graphe
	./fonctions_graphe

go:	tests abench.sh
	./tests

abench.sh: bench gen_cache_data

val:	abench.sh
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./bench unwrap_deserialise_Article

bench:	bench.o parsing.o list.o unwrap.o macro.o
	$(CCA) -o bench  $^ $(CFLAGS) $(LDLIBS)

tests:	tests.o parsing.o list.o unwrap.o macro.o search.o
	$(CCA) -o tests  $^ $(CFLAGS) $(LDLIBS)

Dijkstra: Dijkstra.o unwrap.o parsing.o
	$(CCA) -o Dijkstra $^ $(CFLAGS) $(LDLIBS)
	
fonctions_graphe: fonctions_graphe.o unwrap.o  parsing.o macro.o
	$(CCA) -o fonctions_graphe $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o macro.o
	$(CCA) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CCA) -o $@ -c $< $(CFLAGS) $(LDLIBS)

# %.gcno: %.c
# 	$(CCA) -o $@ -c $< $(CFLAGS)

raport: bench.c parsing.c list.c unwrap.c
	$(CCA) -O0 -o GCOVtests  $^ $(CFLAGS) $(LDLIBS)
	./GCOVtests unwrwap_deserialise
	./GCOVtests serialized
	./GCOVtests unwrwap_gen_cache
	./GCOVtests serializedsmall
	./GCOVtests unwrwap_gen_cache_small
	./GCOVtests unwrwap_gen_cache_small
	gcov -abcfu bench.c parsing.c list.c unwrap.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory LcovRapport
	firefox LcovRapport/main/index.html

doc:
	doxygen Doxyfile
	firefox html/index.html

callgrind:	abench.sh
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__unwrap_deserialise_Article	./bench unwrap_deserialise_Article
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__gen_tab_Article_from_xml	./bench gen_tab_Article_from_xml
	kcachegrind callgrind_trace__unwrap_deserialise_Article
	kcachegrind callgrind_trace__gen_tab_Article_from_xml
	# rm callgrind_trace_gen_unwrap_Graph
# lunch kprok pour profiler le temps d'execution

Update: DATA/dblp.xml
	if [ $$(curl https://dblp.uni-trier.de/xml/ |grep dblp.xml.gz.md5|grep -o ">202.-..-.."|tr -d ">") != $$(stat DATA/dblp.xml -c %y|cut -d " " -f 1) ];  then rm DATA/dblp.xml ; make DATA/dblp.xml ; fi

DATA/dblp.xml:
	rm -f dblp.xml.gz
	wget https://dblp.uni-trier.de/xml/dblp.xml.gz
	gzip dblp.xml.gz -d
	mv dblp.xml DATA/dblp.xml
	rm -f dblp.xml.gz
#10966843
DATA/dblp1sur8.xml: DATA/dblp.xml
	head DATA/dblp.xml -n 10010 > DATA/dblp1sur8.xml

#regénère tout les fichier lier a bench quand un .o change Ces regretabkle donc on enleve bench par .O
DATA/SerializedStruc.data:	DATA/dblp.xml parsing.o
	./bench serialized

DATA/Serialzed1000.data: 	DATA/dblp1sur8.xml parsing.o
	./bench serializedsmall

DATA/SerializedStrucInverse1000.data:	DATA/Serialzed1000.data 
#unwrap.o
	./bench unwrwap_gen_cache_small

#LA
DATA/SerializedStrucInverse.data: DATA/SerializedStruc.data 
#unwrap.o
	./bench unwrwap_gen_cache

DATA/SerializedStrucArticle.data: DATA/SerializedStruc.data 
#unwrap.o
	./bench unwrap_serialise_Article

gen_cache_data: DATA/dblp.xml DATA/dblp1sur8.xml DATA/SerializedStrucInverse.data DATA/Serialzed1000.data DATA/SerializedStruc.data DATA/SerializedStrucInverse1000.data DATA/SerializedStrucArticle.data

r:	clean go
rr:	cleanall go
clean:
	rm -f  *.o *.so *.gcno *.gcda *.gch *.gcov coverage.info vgcore.*
	rm -fr tests bench main GCOVtests LcovRapport html latex
# Update
cleanall: clean 
	rm -f DATA/SerializedStrucInverse.data\
		DATA/dblp1sur8.xml\
		DATA/SerializedStruc.data\
		DATA/Serialzed1000.data\
		DATA/SerializedStrucInverse1000.data\
		DATA/SerializedStrucArticle.data\
		DATA/SerializedStrucArticleCustom.data\
		DATA/SerializedStrucInverseCustom.data

# instaler doxygene est lcov