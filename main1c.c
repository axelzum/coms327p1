#include "sound.h"
#include "gensnd.h"
#include "iosnd.h"
#include "process.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *  Takes two arguments.
 *  The first is a phone number of any size. This argument is required and must contain
 *  only allowed characters.
 *  The second is a filename to write to. If no file argument is included program writes to stdout.
 */
int main(int argc, char const *argv[]) {


    sound *s = (sound*) malloc(sizeof(sound));
    s->samples = malloc(16 * sizeof *s->samples);
    s->samples[0] = 0.4;
    s->samples[1] = 0.1;
    s->samples[2] = 0.0;
    s->samples[3] = 0.0;
    s->samples[4] = 0.0;
    s->samples[5] = 0.1;
    s->samples[6] = 0.5;
    s->samples[7] = 0.2;
    s->samples[8] = 0.0;
    s->samples[9] = 0.0;
    s->samples[10] = 0.0;
    s->samples[11] = 0.0;
    s->samples[12] = 0.2;
    s->samples[13] = 0.2;
    s->samples[14] = 0.3;
    s->samples[15] = 0.3;

    s->length = 16;

    s->rate = 60;

    FILE* f = fopen(argv[1], "w");
    if (f == NULL) {
        fprintf(stderr, "Invalid filename\n");
        return 1;
    }
    sound* tone = reverb(s, 0.05, 0.2);
    outputSound(tone, f);
    free(tone->samples);
    free(tone);
    fclose(f);

    /*

    //strspan checks the string to make sure it only contains allowed characters
    if (argc < 2 || strspn(argv[1], "0123456789abcdABCD*#") != strlen(argv[1])) {
        fprintf(stderr, "Must include valid phone number with command line parameters\n");
        return 0;
    }

    //No filename argument detected, outputing to stdout
    if (argc == 2) {
        printf("Input file name\n");
    }
    //Outputting to file
    else {
        FILE* f = fopen(argv[2], "w");
        if (f == NULL) {
            fprintf(stderr, "Invalid filename\n");
            return 1;
        }
        sound* tone;
        int i;
        for (i=0; i<strlen(argv[1]); i++) {
            tone = genDTMF(argv[1][i], 8000, 0.5);
            free(tone);
            outputSound(tone, f);
            tone = genSilence(8000, 0.25);
            free(tone);
            outputSound(tone, f);
        }
        fclose(f);
    }
    */

    return 0;
}
