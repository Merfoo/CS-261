default: avl

avl.o: avl.c avl.h
	gcc -Wall -ansi -c avl.c

avl: main.c avl.o
	gcc -Wall -ansi -o avl avl.o main.c

clean:
	rm *.o
