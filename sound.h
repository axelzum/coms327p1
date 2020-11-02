#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t {
    float* samples; // Sound samples
    int length;     // Number of samples in the samples array
    float rate;     // Sample rate for sequence of samples
} sound;

//  Linked list to hold data in WAVE objects in input file
typedef struct waveNode {
    char name[256];
    char type[10];
    float delay;
    float attenuation;
    struct waveNode* next;
} waveNode;

//  Linked list to hold data in SOUND objects in input file
typedef struct soundNode {
    char name[256];
    char waves[1024][256];
    float levels[1024];
    int length;
    struct soundNode* next;
} soundNode;

//  Linked list to hold sounds from SONG part of input file
typedef struct songNode {
    sound* sound;
    float startTime;
    struct songNode* next;
} songNode;

#endif
