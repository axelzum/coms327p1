all: gensine gendial

gensine: main.c gensnd.c
	gcc -o gensine main.c gensnd.c

gendial: main2.c gensnd.c
	gcc -o gendial main2.c gensnd.c

clean:
	rm -f gensine *~
	rm -f gendial *~
