CCA ?= cc -O0
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= 

PATH_BIN	?= bin/
PATH_HEADER	?= header/
PATH_SOURCE	?= source/
PATH_BUILD	?= build/

abench.sh: genfolder $(PATH_BIN)bench gen_cache_data 


# -lm -pthread -ftest-coverage -fprofile-arcs
# -lm -pthread

#gcc -shared -o libfoo.so foo.o

go:	genfolder $(PATH_BIN)tests custom
	./$(PATH_BIN)tests

# explargeur: Dijkstra abench.sh
# 	./Dijkstra

# graphe: fonctions_graphe abench.sh
# 	./fonctions_graphe
# $(PATH_HEADER)

Dijkstra: graphTest2 genfolder $(PATH_BIN)Dijkstra
	./$(PATH_BIN)Dijkstra

val:	genfolder $(PATH_BIN)bench gsmall
	# valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(PATH_BIN)bench dg 2
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(PATH_BIN)bench sg 2
	# valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(PATH_BIN)bench gxml 2
	
raport: genfolder $(PATH_SOURCE)bench.c $(PATH_SOURCE)parsing.c $(PATH_SOURCE)unwrap.c $(PATH_SOURCE)macro.c $(PATH_SOURCE)search.c
	$(CCA) -O0 -o GCOVtests  $^ $(CFLAGS) -ftest-coverage -fprofile-arcs
	./GCOVtests graph_xml 1
	./GCOVtests sg 1
	./GCOVtests dg 1
	gcov -abcfu $(PATH_SOURCE)bench.c $(PATH_SOURCE)parsing.c $(PATH_SOURCE)unwrap.c $(PATH_SOURCE)macro.c $(PATH_SOURCE)search.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory LcovRapport
	firefox LcovRapport/main/index.html

doc:
	doxygen Doxyfile
	firefox html/index.html

callgrind:	genfolder bench gsmall
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__unwrap_deserialise_Article	./$(PATH_BIN)bench sg 1
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=callgrind_trace__gen_tab_Article_from_xml	./$(PATH_BIN)bench dg 1
	kcachegrind callgrind_trace__unwrap_deserialise_Article
	kcachegrind callgrind_trace__gen_tab_Article_from_xml
	# rm callgrind_trace_gen_unwrap_Graph
# lunch kprok pour profiler le temps d'execution

$(PATH_BIN)bench:	$(PATH_BUILD)bench.o $(PATH_BUILD)parsing.o $(PATH_BUILD)list.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)macro.o 
	$(CCA) -o $(PATH_BIN)bench  $^ $(CFLAGS) $(LDLIBS)

$(PATH_BIN)tests:	$(PATH_BUILD)tests.o $(PATH_BUILD)parsing.o $(PATH_BUILD)list.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)macro.o $(PATH_BUILD)search.o
	$(CCA) -o $(PATH_BIN)tests  $^ $(CFLAGS) $(LDLIBS)

$(PATH_BIN)Dijkstra: $(PATH_BUILD)Dijkstra.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)parsing.o $(PATH_BUILD)macro.o $(PATH_BUILD)fonctions_graphe.o
	$(CCA) -o $(PATH_BIN)Dijkstra $^ $(CFLAGS) $(LDLIBS)
	
$(PATH_BIN)fonctions_graphe: $(PATH_BUILD)fonctions_graphe.o $(PATH_BUILD)unwrap.o  $(PATH_BUILD)parsing.o macro.o
	$(CCA) -o $(PATH_BIN)fonctions_graphe $^ $(CFLAGS) $(LDLIBS)

$(PATH_BIN)main:	$(PATH_BUILD)main.o $(PATH_BUILD)parsing.o $(PATH_BUILD)macro.o
	$(CCA) -o $(PATH_BIN)main  $^ $(CFLAGS) $(LDLIBS)

$(PATH_BUILD)%.o: $(PATH_SOURCE)%.c
	$(CCA) -o $@ -c $< $(CFLAGS) $(LDLIBS)

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
# 	./$(PATH_BIN)benchserialized

# DATA/SerialzedSmall.data: 	DATA/dblpSmall.xml parsing.o
# 	./$(PATH_BIN)benchserializedsmall

# DATA/SerializedStrucInverseSmall.data:	DATA/SerialzedSmall.data 
# #unwrap.o
# 	./$(PATH_BIN)benchunwrwap_gen_cache_small

# #LA
# DATA/SerializedStrucInverse.data: DATA/SerializedStruc.data 
# #unwrap.o
# 	./$(PATH_BIN)benchunwrwap_gen_cache

# DATA/SerializedStrucArticle.data: DATA/SerializedStruc.data 
# #unwrap.o
# 	./$(PATH_BIN)benchunwrap_serialise_Article

# gen_cache_data: DATA/dblp.xml DATA/dblpSmall.xml DATA/SerializedStrucInverse.data DATA/SerialzedSmall.data DATA/SerializedStruc.data DATA/SerializedStrucInverseSmall.data DATA/SerializedStrucArticle.data

# DATA/dblp.xml DATA/SerializedStruc.data DATA/SerializedStrucInverse.data DATA/SerializedStrucArticle.data

gen_cache_data: graphXML gsmall custom graphTest2

graphXML: 	DATA/SerializedStruc.data DATA/SerializedStrucInverse.data DATA/SerializedStrucArticle.data 
gsmall: 	DATA/SerialzedSmall.data DATA/SerializedStrucInverseSmall.data DATA/small_article.data
custom: 	DATA/customfichecache.data DATA/SerializedStrucInverseCustom.data DATA/SerializedStrucArticleCustom.data
graphTest2: DATA/SerializedStrucKatie.data DATA/SerializedStrucInverseKatie.data DATA/SerializedStrucArticleKatie.data

DATA/SerializedStruc.data: $(PATH_BIN)bench DATA/dblp.xml 
	./$(PATH_BIN)bench sg 0
DATA/SerializedStrucInverse.data: $(PATH_BIN)bench DATA/SerializedStruc.data
	./$(PATH_BIN)bench sg 0
DATA/SerializedStrucArticle.data: $(PATH_BIN)bench DATA/SerializedStrucInverse.data
	./$(PATH_BIN)bench sg 0

DATA/SerialzedSmall.data: DATA/dblpSmall.xml $(PATH_BIN)bench
	./$(PATH_BIN)bench sg 1
DATA/SerializedStrucInverseSmall.data: $(PATH_BIN)bench DATA/SerialzedSmall.data
	./$(PATH_BIN)bench sg 1
DATA/small_article.data: $(PATH_BIN)bench DATA/SerializedStrucInverseSmall.data
	./$(PATH_BIN)bench sg 1

DATA/customfichecache.data: $(PATH_BIN)bench DATA/custom.xml
	./$(PATH_BIN)bench sg 2
DATA/SerializedStrucInverseCustom.data: $(PATH_BIN)bench DATA/customfichecache.data
	./$(PATH_BIN)bench sg 2
DATA/SerializedStrucArticleCustom.data: $(PATH_BIN)bench DATA/SerializedStrucInverseCustom.data
	./$(PATH_BIN)bench sg 2

DATA/SerializedStrucKatie.data: $(PATH_BIN)bench DATA/test_Katie.xml
	./$(PATH_BIN)bench sg 3
DATA/SerializedStrucInverseKatie.data: $(PATH_BIN)bench DATA/SerializedStrucKatie.data
	./$(PATH_BIN)bench sg 3
DATA/SerializedStrucArticleKatie.data: $(PATH_BIN)bench DATA/SerializedStrucInverseKatie.data
	./$(PATH_BIN)bench sg 3

r:	clean go
rr:	cleanall go
c:clean
cc:cleanall


genfolder: $(PATH_BIN) $(PATH_BUILD)
$(PATH_BIN):
	mkdir -p $(PATH_BIN)
$(PATH_BUILD):
	mkdir -p $(PATH_BUILD)

clean:
	rm -f  coverage.info vgcore.*
	rm -fr GCOVtests LcovRapport html latex
	rm -rf $(PATH_BUILD) $(PATH_BIN)
# Update
cleanall: clean 
	rm -f 	DATA/dblpSmall.xml\
			DATA/SerializedStruc.data\
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