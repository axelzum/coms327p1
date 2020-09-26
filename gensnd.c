#include "gensnd.h"

#include <math.h>
#include <stdio.h>

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
 *  Given a pressed key on a touch-tone dial keypad, generates a sine wave
 *  corresponding to the two frequencies attributed to that key. The sine has
 *  a frequency of 8000Hz and a duration of 500ms.
 */
void dualtone(char key) {
    float frequency1, frequency2;

    switch (key) {
        case '1':
            frequency1 = 1209;
            frequency2 = 697;
            break;
        case '4':
            frequency1 = 1209;
            frequency2 = 770;
            break;
        case '7':
            frequency1 = 1209;
            frequency2 = 852;
            break;
        case '*':
            frequency1 = 1209;
            frequency2 = 941;
            break;
        case '2':
            frequency1 = 1336;
            frequency2 = 697;
            break;
        case '5':
            frequency1 = 1336;
            frequency2 = 770;
            break;
        case '8':
            frequency1 = 1336;
            frequency2 = 852;
            break;
        case '0':
            frequency1 = 1336;
            frequency2 = 941;
            break;
        case '3':
            frequency1 = 1477;
            frequency2 = 697;
            break;
        case '6':
            frequency1 = 1477;
            frequency2 = 770;
            break;
        case '9':
            frequency1 = 1477;
            frequency2 = 852;
            break;
        case '#':
            frequency1 = 1477;
            frequency2 = 941;
            break;
        case 'A':
        case 'a':
            frequency1 = 1633;
            frequency2 = 697;
            break;
        case 'B':
        case 'b':
            frequency1 = 1633;
            frequency2 = 770;
            break;
        case 'C':
        case 'c':
            frequency1 = 1633;
            frequency2 = 852;
            break;
        case 'D':
        case 'd':
            frequency1 = 1633;
            frequency2 = 941;
            break;
        default:
            printf("Not a valid numpad character.\n");
            return;
    }

    float outputSamples = 8000 * 0.5; //frequency: 8000Hz, duration: 500ms
    float samplesPerCycle1 = 8000 / frequency1;
    float samplesPerCycle2 = 8000 / frequency2;
    float outputInterval1 = (2.0 * M_PI) / samplesPerCycle1;
    float outputInterval2 = (2.0 * M_PI) / samplesPerCycle2;

    double radians = 0.0;
    int i;
    for(i = 0; i < outputSamples + 1; i++) {
        printf("%lf\n", sin(radians));
        //Averages the two output intervals to get the added frequency.
        //Also could have averaged the two frequencies together.
        radians += (outputInterval1 + outputInterval2) / 2;
    }
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
