#include "sound.h"
#include "stdio.h"
#include "stdlib.h"

sound* mix(sound *s[], float w[], int c) {
    int longestSound = s[0]->length;
    int sampleRate = s[0]->rate;

    int i;
    for (i = 0 ; i < c; i++) {
        if (s[i]->rate != sampleRate) {
            fprintf(stderr, "Sounds in mix have differing sample rates.\n");
            exit(1);
        }
        if (s[i]->length > longestSound) {
            longestSound = s[i]->length;
        }
    }

    sound *output = (sound*) malloc(sizeof(sound));

    output->samples = malloc(longestSound * sizeof *output->samples);
    output->length = longestSound;
    output->rate = s[0]->rate;

    int j;
    for (i = 0; i < output->length; i++) {
        for (j = 0; j < c; j++) {
            if (s[j]->length > i) {
                output->samples[i] += s[j]->samples[i] * w[j];
            }
        }
    }

    return output;
}
