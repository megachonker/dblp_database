CCA ?= cc -O0
CFLAGS ?= -Wall -Wextra -g
LDLIBS ?= 

PATH_BIN	?= bin/
PATH_HEADER	?= header/
PATH_SOURCE	?= source/
PATH_BUILD	?= build/
PATH_DEBUG	?= debug/

abench.sh: genfolder $(PATH_BIN)bench gen_cache_data 


# -lm -pthread -ftest-coverage -fprofile-arcs
# -lm -pthread

#gcc -shared -o libfoo.so foo.o

go:	genfolder $(PATH_BIN)tests custom
	./$(PATH_BIN)tests

Dijkstra: abench.sh
	./$(PATH_BIN)bench dik 1 15

val:	genfolder $(PATH_BIN)bench
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(PATH_BIN)bench sg 1
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(PATH_BIN)bench dik 1 5


raport:	genfolder rp
rp: $(PATH_SOURCE)bench.c $(PATH_SOURCE)parsing.c $(PATH_SOURCE)unwrap.c $(PATH_SOURCE)macro.c $(PATH_SOURCE)search.c $(PATH_SOURCE)Dijkstra.c $(PATH_SOURCE)fonctions_graphe.c
	$(CCA) -O0 -o $(PATH_DEBUG)GCOVtests  $^ $(CFLAGS) -ftest-coverage -fprofile-arcs
	./$(PATH_DEBUG)GCOVtests sg 1
	./$(PATH_DEBUG)GCOVtests dik 1 1
	gcov -abcfu $(PATH_SOURCE)bench.c $(PATH_SOURCE)parsing.c $(PATH_SOURCE)unwrap.c $(PATH_SOURCE)macro.c $(PATH_SOURCE)search.c
	lcov --capture --directory $(PATH_DEBUG) --output-file $(PATH_DEBUG)coverage.info
	genhtml $(PATH_DEBUG)coverage.info --output-directory $(PATH_DEBUG)LcovRapport
	firefox $(PATH_DEBUG)LcovRapport/index.html

doc:
	doxygen Doxyfile
	firefox html/index.html

callgrind:	genfolder $(PATH_BIN)bench
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=$(PATH_DEBUG)callgrind_trace__SerialiseGraph	./$(PATH_BIN)bench sg 0
	valgrind --dump-instr=yes --collect-jumps=yes --tool=callgrind --callgrind-out-file=$(PATH_DEBUG)callgrind_trace__deSerialiseGraph	./$(PATH_BIN)bench dik 1 10
	kcachegrind $(PATH_DEBUG)callgrind_trace__SerialiseGraph
	kcachegrind $(PATH_DEBUG)callgrind_trace__deSerialiseGraph

# lunch kprok pour profiler le temps d'execution

$(PATH_BIN)bench:	$(PATH_BUILD)bench.o $(PATH_BUILD)parsing.o $(PATH_BUILD)list.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)macro.o $(PATH_BUILD)fonctions_graphe.o $(PATH_BUILD)Dijkstra.o
	$(CCA) -o $(PATH_BIN)bench  $^ $(CFLAGS) $(LDLIBS)

$(PATH_BIN)tests:	$(PATH_BUILD)tests.o $(PATH_BUILD)parsing.o $(PATH_BUILD)list.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)macro.o $(PATH_BUILD)search.o
	$(CCA) -o $(PATH_BIN)tests  $^ $(CFLAGS) $(LDLIBS)

# ces un lib maintenan...
# $(PATH_BIN)Dijkstra: $(PATH_BUILD)Dijkstra.o $(PATH_BUILD)unwrap.o $(PATH_BUILD)parsing.o $(PATH_BUILD)macro.o $(PATH_BUILD)fonctions_graphe.o
# 	$(CCA) -o $(PATH_BIN)Dijkstra $^ $(CFLAGS) $(LDLIBS)
	
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

gen_cache_data: $(PATH_BIN)bench graphXML gsmall custom graphTest2

graphXML: 	DATA/SerializedStruc.data DATA/SerializedStrucInverse.data DATA/SerializedStrucArticle.data 
gsmall: 	DATA/SerialzedSmall.data DATA/SerializedStrucInverseSmall.data DATA/small_article.data
custom: 	DATA/customfichecache.data DATA/SerializedStrucInverseCustom.data DATA/SerializedStrucArticleCustom.data
graphTest2: DATA/SerializedStrucKatie.data DATA/SerializedStrucInverseKatie.data DATA/SerializedStrucArticleKatie.data

DATA/SerializedStruc.data: $(PATH_BUILD)unwrap.o DATA/dblp.xml 
	./$(PATH_BIN)bench sg 0
DATA/SerializedStrucInverse.data: $(PATH_BUILD)unwrap.o DATA/SerializedStruc.data
	./$(PATH_BIN)bench sg 0
DATA/SerializedStrucArticle.data: $(PATH_BUILD)unwrap.o DATA/SerializedStrucInverse.data
	./$(PATH_BIN)bench sg 0

DATA/SerialzedSmall.data: $(PATH_BUILD)unwrap.o DATA/dblpSmall.xml
	./$(PATH_BIN)bench sg 1
DATA/SerializedStrucInverseSmall.data: $(PATH_BUILD)unwrap.o DATA/SerialzedSmall.data
	./$(PATH_BIN)bench sg 1
DATA/small_article.data: $(PATH_BUILD)unwrap.o DATA/SerializedStrucInverseSmall.data
	./$(PATH_BIN)bench sg 1

DATA/customfichecache.data: $(PATH_BUILD)unwrap.o DATA/custom.xml
	./$(PATH_BIN)bench sg 2
DATA/SerializedStrucInverseCustom.data: $(PATH_BUILD)unwrap.o DATA/customfichecache.data
	./$(PATH_BIN)bench sg 2
DATA/SerializedStrucArticleCustom.data: $(PATH_BUILD)unwrap.o DATA/SerializedStrucInverseCustom.data
	./$(PATH_BIN)bench sg 2

DATA/SerializedStrucKatie.data: $(PATH_BUILD)unwrap.o DATA/test_Katie.xml
	./$(PATH_BIN)bench sg 3
DATA/SerializedStrucInverseKatie.data: $(PATH_BUILD)unwrap.o DATA/SerializedStrucKatie.data
	./$(PATH_BIN)bench sg 3
DATA/SerializedStrucArticleKatie.data: $(PATH_BUILD)unwrap.o DATA/SerializedStrucInverseKatie.data
	./$(PATH_BIN)bench sg 3

r:	clean go
rr:	cleanall go
c:clean
cc:cleanall


genfolder: $(PATH_BIN) $(PATH_BUILD) $(PATH_DEBUG) DATA/dblpSmall.xml
$(PATH_BIN):
	mkdir -p $(PATH_BIN)
$(PATH_BUILD):
	mkdir -p $(PATH_BUILD)
$(PATH_DEBUG):
	mkdir -p $(PATH_DEBUG)

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
	rm -rf $(PATH_DEBUG)

# instaler doxygene est lcov