all: partc

partc: playsong.c gensnd.c iosnd.c process.c
	gcc -o playsong playsong.c gensnd.c iosnd.c process.c -lm

clean:
	rm -f playsong *~
