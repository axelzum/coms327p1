#include "sound.h"
#include "stdio.h"
#include "stdlib.h"

#include <math.h>

/*
 *  Mixes an array of sounds into one sound using a simple multiplicative factor.
 *  All the sounds in the input s must have the same sample rate. Multiplication
 *  rates are in w and correspond to the same elements in s.
 */
sound* mix(sound *s[], float w[], int c) {
    int longestSound = s[0]->length;
    int sampleRate = s[0]->rate;

    int i;
    for (i = 0 ; i < c; i++) {
        if (s[i]->rate != sampleRate) {
            fprintf(stderr, "Sounds in mix have differing sample rates.\n");
            return NULL;
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
        output->samples[i] = 0.0;
        for (j = 0; j < c; j++) {
            if (s[j]->length > i) {
                output->samples[i] += s[j]->samples[i] * w[j];
            }
        }
    }

    return output;
}

/*
 *  Multiplies two sounds together and outputs the result in on sound. Both Sounds
 *  s1 and s2 must have the same sample rate and length.
 */
sound* modulate(sound *s1, sound *s2) {
    if (s1->rate != s2->rate || s1->length != s2->length) {
        fprintf(stderr, "Sounds have differing sample rates or lengths.\n");
        return NULL;
    }

    sound *output = (sound*) malloc(sizeof(sound));
    output->samples = malloc(s1->length * sizeof *output->samples);
    output->length = s1->length;
    output->rate = s1->rate;

    int i;
    for (i = 0; i < output->length; i++) {
        output->samples[i] = s1->samples[i]*s2->samples[i];
    }

    return output;
}

/*
 *  Applys a filter to a given sound s using the fir array and a process called
 *  convolution.
 */
sound* filter(sound *s, float fir[], int c) {
    sound *output = (sound*) malloc(sizeof(sound));
    output->samples = malloc(s->length * sizeof *output->samples);
    output->length = s->length;
    output->rate = s->rate;

    int i,j;
    for (i = 0; i < output->length; i++) {
        output->samples[i] = 0.0;
        for (j = 0; j < c; j++) {
            if (i>=j) {
                output->samples[i] += s->samples[i-j] * fir[j];
            }
        }
    }

    return output;
}

/*
 *  Adds a reverb effect to a sound s. The delay and attenuation are used to apply
 *  a filter to s.
 */
sound* reverb(sound *s, float delay, float attenuation) {
    if (s == NULL) {
        fprintf(stderr, "Given sound is null.\n");
        return NULL;
    }
    if (attenuation <= 0 || attenuation >= 1) {
        fprintf(stderr, "Attenuation must be between 1 and 0\n");
        return NULL;
    }
    if (delay <= 0 || delay >= 0.1) {
        fprintf(stderr, "Delay must be bbetween 0.1 and 0.\n");
        return NULL;
    }

    int firLength = round(delay * s->rate);
    firLength++;
    float fir[firLength];
    int i;
    for (i = 0; i< firLength; i++) {
        fir[i] = 0.0;
    }
    fir[0] = 1.0;
    fir[firLength-1] = attenuation;

    return filter(s, fir, firLength);

}

/*
 *  Similar to reverb, echo applys a filter to a sound s with a delay parameter 0.1 and 1 second.
 */
sound* echo(sound *s, float delay, float attenuation) {
    if (s == NULL) {
        fprintf(stderr, "Given sound is null.\n");
        return NULL;
    }
    if (attenuation <= 0 || attenuation >= 1) {
        fprintf(stderr, "Attenuation must be between 1 and 0\n");
        return NULL;
    }
    if (delay <= 0.1 || delay >= 1.0) {
        fprintf(stderr, "Delay must be bbetween 0.1 and 1.\n");
        return NULL;
    }

    int firLength = round(delay * s->rate);
    firLength++;
    float fir[firLength];
    int i;
    for (i = 0; i< firLength; i++) {
        fir[i] = 0.0;
    }
    fir[0] = 1.0;
    fir[firLength-1] = attenuation;

    return filter(s, fir, firLength);
}
