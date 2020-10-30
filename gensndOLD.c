#include "gensndOLD.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *  Generates a sine wave of a specified frequency in Hz, sampleRate in Hz,
 *  and duration in seconds.
 *  Returns no output just sends the value of the sinewave to stdout.
 */
void gensine(float frequency, float sampleRate, float duration) {
    float outputSamples = sampleRate * duration;
    float samplesPerCycle = sampleRate / frequency;
    float outputInterval = (2.0 * M_PI) / samplesPerCycle;

    double radians = 0.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        printf("%lf\n", sin(radians));
        radians += outputInterval;
    }
}

/*
 *  Generates a sine wave similar to gensine. Returns a pointer to the sound struct
 *  with the size in the struct being the number of samples generated and
 */
sound* gensine2(float hertz, float sample_rate, float duration) {
    sound *output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;
    float samplesPerCycle = sample_rate / hertz;
    float outputInterval = (2.0 * M_PI) / samplesPerCycle;

    double radians = 0.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        output->samples[i] = sin(radians);
        radians += outputInterval;
    }

    return output;
}

/*
 *  Given a pressed key on a touch-tone dial keypad, generates a sine wave
 *  corresponding to the two frequencies attributed to that key. The sine has
 *  a frequency of 8000Hz and a duration of 500ms.
 */
void dualtone(char key) {
    float frequency1, frequency2;

    if (getFrequency(key, &frequency1, &frequency2) != 0) {
        printf("Not a valid numpad character.\n");
        return;
    }

    float outputSamples = 8000 * 0.5; //frequency: 8000Hz, duration: 500ms
    float samplesPerCycle1 = 8000 / frequency1;
    float samplesPerCycle2 = 8000 / frequency2;
    float outputInterval1 = (2.0 * M_PI) / samplesPerCycle1;
    float outputInterval2 = (2.0 * M_PI) / samplesPerCycle2;

    double radians1 = 0.0;
    double radians2 = 0.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        printf("%lf\n", (sin(radians1) + sin(radians2)) / 2.0);
        radians1 += outputInterval1;
        radians2 += outputInterval2;
    }
}

/*
 *  Generates a sine wave of two frequencies similar to dualtone() returns a pointer to a
 *  sound struct.
 */
sound* genDTMF2(char key, float sample_rate, float duration) {
    float frequency1, frequency2;

    if (getFrequency(key, &frequency1, &frequency2) != 0) {
        printf("Not a valid numpad character.\n");
        return NULL;
    }

    sound* output1 = gensine2(frequency1, sample_rate, duration);
    sound* output2 = gensine2(frequency2, sample_rate, duration);

    sound* output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;

    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        output->samples[i] = (output1->samples[i] + output2->samples[i]) / 2;
    }

    free(output1->samples);
    free(output1);
    free(output2->samples);
    free(output2);

    return output;
}

/*
 *  Given a pressed key value updates the frequency values to match the two frequencies
 *  of a touch tone telephone with the given key pressed. Helper method for genDTMF.
 *  If a 0 is returned frequency was returned correctly, else the input was invalid.
 */
int getFrequency(char key, float* frequency1, float* frequency2) {
    switch (key) {
        case '1':
            *frequency1 = 1209;
            *frequency2 = 697;
            break;
        case '4':
            *frequency1 = 1209;
            *frequency2 = 770;
            break;
        case '7':
            *frequency1 = 1209;
            *frequency2 = 852;
            break;
        case '*':
            *frequency1 = 1209;
            *frequency2 = 941;
            break;
        case '2':
            *frequency1 = 1336;
            *frequency2 = 697;
            break;
        case '5':
            *frequency1 = 1336;
            *frequency2 = 770;
            break;
        case '8':
            *frequency1 = 1336;
            *frequency2 = 852;
            break;
        case '0':
            *frequency1 = 1336;
            *frequency2 = 941;
            break;
        case '3':
            *frequency1 = 1477;
            *frequency2 = 697;
            break;
        case '6':
            *frequency1 = 1477;
            *frequency2 = 770;
            break;
        case '9':
            *frequency1 = 1477;
            *frequency2 = 852;
            break;
        case '#':
            *frequency1 = 1477;
            *frequency2 = 941;
            break;
        case 'A':
        case 'a':
            *frequency1 = 1633;
            *frequency2 = 697;
            break;
        case 'B':
        case 'b':
            *frequency1 = 1633;
            *frequency2 = 770;
            break;
        case 'C':
        case 'c':
            *frequency1 = 1633;
            *frequency2 = 852;
            break;
        case 'D':
        case 'd':
            *frequency1 = 1633;
            *frequency2 = 941;
            break;
        default:
            return 1;
    }
    return 0;
}

/*
 *  Generates a a sine wave that produces no sound (0) over a given duration
 *  and sample rate.
 */
void silence(float sampleRate, float duration) {
    float outputSamples = sampleRate * duration;

    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        printf("%lf\n", sin(0.0));
    }
}

/*
 *  Generates a sine wave that outputs no sounds for a sample rate and duration.
 *  Returns a pointer to a sound struct
 */
sound* genSilence(float sample_rate, float duration) {
    sound *output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;

    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        output->samples[i] = sin(0.0);
    }

    return output;
}

/*
 *  Takes a sound as an input and outputs to a file in rows similar to part a.
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
