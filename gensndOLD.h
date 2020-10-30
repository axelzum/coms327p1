#ifndef GENSNDOLD_H
#define GENSNDOLD_H

#include <stdio.h>

typedef struct sound_t {
    float* samples; // Sound samples
    int length;     // Number of samples in the samples array
    float rate;     // Sample rate for sequence of samples
} sound;

void gensine(float frequency, float sampleRate, float duration);

sound* gensine2(float hertz, float sample_rate, float duration);

void dualtone(char key);

sound* genDTMF2(char key, float sample_rate, float duration);

int getFrequency(char key, float* frequency1, float* frequency2);

void silence(float sampleRate, float duration);

sound* genSilence(float sample_rate, float duration);

int outputSound(sound *s, FILE *f);

#endif
