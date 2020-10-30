partc: final

all: parta partb

partb: dtmf

parta: gensine gendial

final: main1c.c gensnd.c iosnd.c process.c
	gcc -o main main1c.c gensnd.c iosnd.c process.c -lm

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
	rm -f main *~
