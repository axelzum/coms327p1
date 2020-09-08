#include "gensnd.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

    float frequency;
    float sampleRate;
    float duration;

    printf("Input a frequency in hertz:\n");
    scanf("%f", &frequency);
    printf("Input a sample rate in hertz:\n");
    scanf("%f", &sampleRate);
    printf("Input a time duraiton in seconds:\n");
    scanf("%f", &duration);

    //run gensnd

    return 0;
}
