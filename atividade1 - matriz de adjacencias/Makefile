UTIL = Util/Util.c
LISTA = adjmatrix.c
BINARY = adjmatrixBin
NAME = TAD

all:
	gcc -Wall -g $(UTIL) $(LISTA) -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o

objlib:
	gcc -Wall -pedantic -Werror -Wextra -c -fPIC $(UTIL) $(ITEM)

lib:
	ar -rcs lib_util.a *.o