all: parta partb

partb: dtmf

parta: gensine gendial

dtmf: main1b.c gensndOLD.c
	gcc -o dtmf main1b.c gensndOLD.c -lm

gensine: main.c gensndOLD.c
	gcc -o gensine main.c gensndOLD.c -lm

gendial: main2.c gensndOLD.c
	gcc -o gendial main2.c gensndOLD.c -lm

clean:
	rm -f gensine *~
	rm -f gendial *~
	rm -f dtmf *~
