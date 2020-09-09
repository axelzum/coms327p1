#include "gensnd.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

    float frequency;
    float sampleRate;
    float duration;

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
