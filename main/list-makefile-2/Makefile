
tests: tests.o linked-list.o
	gcc -g -o tests tests.o linked-list.o 	

clean: 
	rm -f *.o
	rm -f tests

linked-list.o: linked-list.c
	gcc -Wall -Wextra -Werror  -g -o linked-list.o -c linked-list.c

tests.o: tests.c
	gcc -Wall -Wextra -Werror  -g -o tests.o -c tests.c


