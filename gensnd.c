#include "sound.h"
#include "gensnd.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*
 *  Generates a sine wave. Returns a pointer to the sound struct
 *  with the size in the struct being the number of samples generated.
 */
sound* gensine(float hertz, float sample_rate, float duration) {
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
 *  Generates a square wave. Returns a pointer to the sound struct
 *  with the size in the struct being the number of samples generated.
 */
sound* genSquare(float hertz, float sample_rate, float duration) {
    sound *output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;

    float samplesPerCycle = sample_rate / hertz;

    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        if (fmod(i, samplesPerCycle) < samplesPerCycle/2.0) {
            output->samples[i] = -1.0;
        }
        else {
            output->samples[i] = 1.0;
        }
    }
    return output;
}

/*
 *  Generates a triangle wave. Returns a pointer to the sound struct
 *  with the size in the struct being the number of samples generated.
 */
sound* genTriangle(float hertz, float sample_rate, float duration) {
    sound *output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;

    float samplesPerCycle = sample_rate / hertz;
    float outputInterval = 2.0 / (samplesPerCycle / 2.0);

    float value = -1.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        output->samples[i] = value;
        if (fmod(i, samplesPerCycle) < samplesPerCycle/2.0) {
            if (value + outputInterval > 1.0) {
                value = 1.0 - (outputInterval - (1.0 - value));
            }
            else {
                value += outputInterval;
            }
        }
        else {
            if (value - outputInterval < -1.0) {
                value = -1.0 + (outputInterval - (value - -1.0));
            }
            else {
                value -= outputInterval;
            }

        }
    }
    return output;
}

/*
 *  Generates a sawtooth wave. Returns a pointer to the sound struct
 *  with the size in the struct being the number of samples generated.
 */
sound* genSawtooth(float hertz, float sample_rate, float duration) {
    sound *output = (sound*) malloc(sizeof(sound));

    float outputSamples = sample_rate * duration;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sample_rate;

    float samplesPerCycle = sample_rate / hertz;
    float outputInterval = 2.0 / samplesPerCycle;

    float value = -1.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        output->samples[i] = value;
        if (i % (int)roundf(samplesPerCycle) == 0 && i != 0) {
            value = -1;
        }
        else {
            value += outputInterval;
        }
    }
    return output;
}

/*
 *  Generates a sine wave of two frequencies corresponding to a key on a touch
 *  tone phone. returns a pointer to a sound struct.
 */
sound* genDTMF(char key, float sample_rate, float duration) {
    float frequency1, frequency2;

    if (getFrequency(key, &frequency1, &frequency2) != 0) {
        printf("Not a valid numpad character.\n");
        return NULL;
    }

    sound* output1 = gensine(frequency1, sample_rate, duration);
    sound* output2 = gensine(frequency2, sample_rate, duration);

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
