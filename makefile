all: parta partb

partb: dtmf

parta: gensine gendial

dtmf: main1b.c gensnd.c
	gcc -o dtmf main1b.c gensnd.c -lm

gensine: main.c gensnd.c
	gcc -o gensine main.c gensnd.c -lm

gendial: main2.c gensnd.c
	gcc -o gendial main2.c gensnd.c -lm

clean:
	rm -f gensine *~
	rm -f gendial *~
	rm -f dtmf *~
