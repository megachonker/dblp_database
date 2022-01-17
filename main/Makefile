CCA ?= cc -O0
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= -lm -pthread -ftest-coverage -fprofile-arcs
# -lm -pthread

#gcc -shared -o libfoo.so foo.o

explargeur: Dijkstra abench.sh
	./Dijkstra

graphe: fonctions_graphe abench.sh
	./fonctions_graphe

go:	tests abench.sh
	./tests

abench.sh: bench gen_cache_data

val:	abench.sh
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./bench dg 1
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./bench sg 1
bench:	bench.o parsing.o list.o unwrap.o macro.o
	$(CCA) -o bench  $^ $(CFLAGS) $(LDLIBS)

tests:	tests.o parsing.o list.o unwrap.o macro.o search.o
	$(CCA) -o tests  $^ $(CFLAGS) $(LDLIBS)

Dijkstra: Dijkstra.o unwrap.o parsing.o macro.o fonctions_graphe.o
	$(CCA) -o Dijkstra $^ $(CFLAGS) $(LDLIBS)
	
fonctions_graphe: fonctions_graphe.o unwrap.o  parsing.o macro.o
	$(CCA) -o fonctions_graphe $^ $(CFLAGS) $(LDLIBS)

main:	main.o parsing.o macro.o
	$(CCA) -o main  $^ $(CFLAGS) $(LDLIBS)

%.o: %.c
	$(CCA) -o $@ -c $< $(CFLAGS) $(LDLIBS)

# %.gcno: %.c
# 	$(CCA) -o $@ -c $< $(CFLAGS)

raport: bench.c parsing.c unwrap.c macro.c search.c
	$(CCA) -O0 -o GCOVtests  $^ $(CFLAGS) $(LDLIBS)
	./GCOVtests graph_xml 1
	./GCOVtests sg 1
	./GCOVtests dg 1
	gcov -abcfu bench.c parsing.c unwrap.c macro.c search.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory LcovRapport
	firefox LcovRapport/main/index.html

doc:
	doxygen Doxyfile
	firefox html/index.html

callgrind:	abench.sh
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__unwrap_deserialise_Article	./bench sg 1
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__gen_tab_Article_from_xml	./bench sg 1
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

DATA/dblpSmall.xml: DATA/dblp.xml
	head DATA/dblp.xml -n 10010 > DATA/dblpSmall.xml

# #regénère tout les fichier lier a bench quand un .o change Ces regretabkle donc on enleve bench par .O
# DATA/SerializedStruc.data:	DATA/dblp.xml parsing.o
# 	./bench serialized

# DATA/SerialzedSmall.data: 	DATA/dblpSmall.xml parsing.o
# 	./bench serializedsmall

# DATA/SerializedStrucInverseSmall.data:	DATA/SerialzedSmall.data 
# #unwrap.o
# 	./bench unwrwap_gen_cache_small

# #LA
# DATA/SerializedStrucInverse.data: DATA/SerializedStruc.data 
# #unwrap.o
# 	./bench unwrwap_gen_cache

# DATA/SerializedStrucArticle.data: DATA/SerializedStruc.data 
# #unwrap.o
# 	./bench unwrap_serialise_Article

# gen_cache_data: DATA/dblp.xml DATA/dblpSmall.xml DATA/SerializedStrucInverse.data DATA/SerialzedSmall.data DATA/SerializedStruc.data DATA/SerializedStrucInverseSmall.data DATA/SerializedStrucArticle.data

# DATA/dblp.xml DATA/SerializedStruc.data DATA/SerializedStrucInverse.data DATA/SerializedStrucArticle.data

gen_cache_data: graphXML graphSmall graphTest graphTest2

graphXML: DATA/SerializedStruc.data DATA/SerializedStrucInverse.data DATA/SerializedStrucArticle.data 
graphSmall: DATA/SerialzedSmall.data DATA/SerializedStrucInverseSmall.data DATA/small_article.data
graphTest: DATA/customfichecache.data DATA/SerializedStrucInverseCustom.data DATA/SerializedStrucArticleCustom.data
graphTest2: DATA/SerializedStrucKatie.data DATA/SerializedStrucInverseKatie.data DATA/SerializedStrucArticleKatie.data

DATA/SerializedStruc.data: bench DATA/dblp.xml
	./bench sg 0
DATA/SerializedStrucInverse.data: bench
	./bench sg 0
DATA/SerializedStrucArticle.data: bench
	./bench sg 0

DATA/SerialzedSmall.data: DATA/dblpSmall.xml bench
	./bench sg 1
DATA/SerializedStrucInverseSmall.data: bench
	./bench sg 1
DATA/small_article.data: bench
	./bench sg 1

DATA/customfichecache.data: bench DATA/custom.xml
	./bench sg 2
DATA/SerializedStrucInverseCustom.data: bench
	./bench sg 2
DATA/SerializedStrucArticleCustom.data: bench
	./bench sg 2

DATA/SerializedStrucKatie.data: bench DATA/test_Katie.xml
	./bench sg 3
DATA/SerializedStrucInverseKatie.data: bench
	./bench sg 3
DATA/SerializedStrucArticleKatie.data: bench
	./bench sg 3

r:	clean go
rr:	cleanall go
clean:
	rm -f  *.o *.so *.gcno *.gcda *.gch *.gcov coverage.info vgcore.*
	rm -fr tests bench main GCOVtests LcovRapport html latex
# Update
cleanall: clean 
	rm -f 	DATA/SerializedStruc.data\
			DATA/SerializedStrucInverse.data\
			DATA/SerializedStrucArticle.data\
			DATA/SerialzedSmall.data\
			DATA/SerializedStrucInverseSmall.data\
			DATA/small_article.data\
			DATA/customfichecache.data\
			DATA/SerializedStrucInverseCustom.data\
			DATA/SerializedStrucArticleCustom.data\
			DATA/SerializedStrucKatie.data\
			DATA/SerializedStrucInverseKatie.data\
			DATA/SerializedStrucArticleKatie.data

# instaler doxygene est lcov