#include "gensnd.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *  Asks the user for a frequency, sample rate, and duration and prints a
 *  sine wave produced by those parameters.
 */
int main(int argc, char const *argv[]) {

    if (argc < 2 || strspn(argv[1], "0123456789abcdABCD*#") != strlen(argv[1])) {
        fprintf(stderr, "Must include valid phone number with command line parameters\n");
        return 0;
    }

    if (argc == 2) {
        int i;
        for (i=0; i<strlen(argv[1]); i++) {
            dualtone(argv[1][i]);
            silence(8000, 0.25);
        }
    }
    else {
        FILE* f = fopen(argv[2], "w");
        if (f == NULL) {
            fprintf(stderr, "Invalid filename\n");
            return 1;
        }
        sound* tone;
        int i;
        for (i=0; i<strlen(argv[1]); i++) {
            tone = genDTMF2(argv[1][i], 8000, 0.5);
            outputSound(tone, f);
            tone = genSilence(8000, 0.25);
            outputSound(tone, f);
        }
        fclose(f);
    }

    return 0;
}
