#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t {
    float* samples; // Sound samples
    int length;     // Number of samples in the samples array
    float rate;     // Sample rate for sequence of samples
} sound;

typedef struct waveNode {
    char name[256];
    char type[10];
    float delay;
    float attenuation;
    struct waveNode* next;
} waveNode;

typedef struct soundNode {
    char name[256];
    char waves[1024][256];
    float levels[1024];
    int length;
    struct soundNode* next;
} soundNode;

typedef struct songNode {
    sound* sound;
    float startTime;
    struct songNode* next;
} songNode;

#endif
