#include "gensnd.h"

#include <stdio.h>

/*
 *  Asks the user for a frequency, sample rate, and duration and prints a
 *  sine wave produced by those parameters.
 */
int main(int argc, char const *argv[]) {

    if (argc < 2) {
        fprintf( stderr, "my %s has %d chars\n", "string format", 30);
    }
    else {
        boolean correct = string.matches("[0123456789]+");
    }

    char* phoneNumber = argv[1];
    char* fileName = argv[2];

    float frequency;
    float sampleRate;
    float duration;

    //The while loops check the user inputs for validity (are positive)
    //The program will not continue until all inputs are valid.
    while (1) {
        printf("Input a positive frequency in hertz:\n");
        scanf("%f", &frequency);

        if (frequency >= 0) {
            break;
        }
    }
    while (1) {
        printf("Input a positive sample rate in hertz:\n");
        scanf("%f", &sampleRate);

        if (sampleRate >= 0) {
            break;
        }
    }
    while (1) {
        printf("Input a positive time duraiton in seconds:\n");
        scanf("%f", &duration);

        if (duration >= 0) {
            break;
        }
    }

    gensine(frequency, sampleRate, duration);

    return 0;
}
