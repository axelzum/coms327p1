#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t {
    float* samples; // Sound samples
    int length;     // Number of samples in the samples array
    float rate;     // Sample rate for sequence of samples
} sound;

#endif
