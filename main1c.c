#include "sound.h"
#include "gensnd.h"
#include "iosnd.h"

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

    FILE* f = fopen(argv[1], "w");
    if (f == NULL) {
        fprintf(stderr, "Invalid filename\n");
        return 1;
    }
    sound* tone = genSawtooth(550.5, 7764, 1.0);
    outputSound(tone, f);
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
