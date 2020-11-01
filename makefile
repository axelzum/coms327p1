partc: final

final: main1c.c gensnd.c iosnd.c process.c
	gcc -o main main1c.c gensnd.c iosnd.c process.c -lm

clean:
	rm -f main *~
