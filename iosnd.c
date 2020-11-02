#include "sound.h"

#include <stdio.h>

/*
 *  Takes a sound as an input and outputs to a file in rows.
 *  Returns 0 if write was a success, 1 otherwise.
 */
int outputSound(sound *s, FILE *f) {
    int i;
    for (i=0; i<s->length; i++) {
        if (fprintf(f, "%lf\n", s->samples[i]) < 0) {
            return 1;
        }
    }
    return 0;
}
