#include "sound.h"
#include "gensnd.h"
#include "iosnd.h"
#include "process.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
 *  Takes two arguments.
 *  The first is an input filename that must be formatted in a specific way as
 *  indicated by the project 1 part c instructions. The order of commands in the firLength
 *  is SAMPLERATE, WAVE, SOUND, SONG.
 *  The second argument is an output filename which the program outputs a txt file
 *  with the wave formate for the input song.
 */
int main(int argc, char const *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments. Proper usage:\n");
        fprintf(stderr, "playsong <input filename> <output filename>\n");
        return 1;
    }

    char const* inputFilename = argv[1];
    char const* outputFilename = argv[2];

    FILE* file = fopen(inputFilename, "r");
    if (file == NULL) {
        fprintf(stderr, "File open error: failed to open %s\n", inputFilename);
        return 1;
    }

    //Set up linked lists to save objects in the input file.
    float sampleRate;
    waveNode* waveHead = (waveNode*) malloc(sizeof(waveNode));
    waveHead->next = NULL;
    soundNode* soundHead = (soundNode*) malloc(sizeof(soundNode));
    soundHead->next = NULL;
    songNode* songHead = NULL;

    //While in the loop, continuously reads lines of the input file, but handles
    //those based on a state machine.
    int state = 0;
    float songEnd = 0.0;
    char line[512];

    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n");

        //State 0: File start, looking for SAMPLERATE
        if (state == 0) {
            if (strcmp(line, "SAMPLERATE") != 0) {
                fprintf(stderr, "Song file must begin with 'SAMPLERATE'\n");
                return 1;
            }
            else {
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                sampleRate = atof(line);
                state = 1;
            }
        }
        //State 1: After SAMPLERATE, looking for WAVE
        else if (state == 1) {
            if (strcmp(line, "\n") == 0) {
                continue;
            }

            if (strcmp(line, "WAVE") != 0) {
                fprintf(stderr, "Expected WAVE after SAMPLERATE, got: %s\n", line);
                return 1;
            }
            else {
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(waveHead->name, line);
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(waveHead->type, line);
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                waveHead->delay = atof(strtok(line, " "));
                waveHead->attenuation = atof(strtok(NULL, " "));
                state = 2;
            }
        }
        //State 2: After first WAVE, looking for more WAVE or SOUND
        else if (state == 2) {
            if (strcmp(line, "\n") == 0) {
                continue;
            }

            if (strcmp(line, "WAVE") == 0) {
                waveNode* waveLink = (waveNode*) malloc(sizeof(waveNode));

                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(waveLink->name, line);
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(waveLink->type, line);
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                waveLink->delay = atof(strtok(line, " "));
                waveLink->attenuation = atof(strtok(NULL, " "));

                waveLink->next = waveHead;
                waveHead = waveLink;
            }
            else if (strcmp(line, "SOUND") == 0) {
                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(soundHead->name, line);

                int numWaves = 0;
                while (fgets(line, sizeof(line), file)) {
                    strtok(line, "\n");
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    else {
                        numWaves++;
                        strcpy(soundHead->waves[numWaves-1], strtok(line, " "));
                        soundHead->levels[numWaves-1] = atof(strtok(NULL, " "));
                    }
                }
                soundHead->length = numWaves;
                state = 3;
            }
            else {
                fprintf(stderr, "Expected WAVE or SOUND after WAVE, got: %s\n", line);
                return 1;
            }
        }
        //State 3: After first SOUND, looking for SOUND or SONG
        else if (state == 3) {
            if (strcmp(line, "\n") == 0) {
                continue;
            }

            if (strcmp(line, "SOUND") == 0) {
                soundNode* soundLink = (soundNode*) malloc(sizeof(soundNode));

                fgets(line, sizeof(line), file);
                strtok(line, "\n");
                strcpy(soundLink->name, line);

                int numWaves = 0;
                while (fgets(line, sizeof(line), file)) {
                    strtok(line, "\n");
                    if (strcmp(line, "\n") == 0) {
                        break;
                    }
                    else {
                        numWaves++;
                        strcpy(soundLink->waves[numWaves-1], strtok(line, " "));
                        soundLink->levels[numWaves-1] = atof(strtok(NULL, " "));
                    }
                }
                soundLink->length = numWaves;

                soundLink->next = soundHead;
                soundHead = soundLink;
            }
            else if (strcmp(line, "SONG") == 0) {
                state = 4;
            }
            else {
                fprintf(stderr, "Expected SOUND or SONG after SOUND, got: %s\n", line);
                return 1;
            }
        }
        //State 4: Reading song, once the song is in a linked list end the loop
        else if (state == 4) {
            strtok(line, "\n");
            if (strcmp(line, "\n") == 0) {
                break;
            }
            char* soundName = strtok(line, " ");
            int keyNumber = atoi(strtok(NULL, " "));
            float startTime = atof(strtok(NULL, " "));
            float duration = atof(strtok(NULL, " "));

            if (startTime + duration > songEnd) {
                songEnd = startTime + duration;
            }

            float frequency = pow(2,(keyNumber-49)/12) * 440;

            soundNode *currSound = soundHead;
            while (strcmp(currSound->name, soundName) != 0) {
                currSound = currSound->next;
            }

            sound *s[currSound->length];
            float w[currSound->length];
            int i;
            for (i = 0; i < currSound->length; i++) {
                waveNode *currWave = waveHead;
                while (strcmp(currWave->name, currSound->waves[i]) != 0) {
                    currWave = currWave->next;
                }

                if (strcmp(currWave->type, "sine") == 0) {
                    s[i] = reverb(gensine(frequency, sampleRate, duration), currWave->delay, currWave->attenuation);
                }
                else if (strcmp(currWave->type, "square") == 0) {
                    s[i] = reverb(genSquare(frequency, sampleRate, duration), currWave->delay, currWave->attenuation);
                }
                else if (strcmp(currWave->type, "triangle") == 0) {
                    s[i] = reverb(genTriangle(frequency, sampleRate, duration), currWave->delay, currWave->attenuation);
                }
                else {
                    s[i] = reverb(genSawtooth(frequency, sampleRate, duration), currWave->delay, currWave->attenuation);
                }
                w[i] = currSound->levels[i];
            }

            songNode* songLink = (songNode*) malloc(sizeof(songNode));
            songLink->sound = mix(s, w, currSound->length);
            songLink->startTime = startTime;

            songLink->next = songHead;
            songHead = songLink;
        }
    }
    fclose(file);

    sound *output = (sound*) malloc(sizeof(sound));
    float outputSamples = sampleRate * songEnd;
    output->samples = malloc((int)outputSamples * sizeof *output->samples);
    output->length = (int)outputSamples;
    output->rate = sampleRate;

    int i;
    for (i = 0; i < output->length; i++) {
        output->samples[i] = 0.0;
    }

    songNode *currSong = songHead;
    while (currSong->next !=  NULL) {
        int startIndex = currSong->startTime * sampleRate;
        for (i = 0; i < currSong->sound->length; i++) {
            output->samples[startIndex+i] += currSong->sound->samples[i];
        }
        currSong = currSong->next;
    }

    file = fopen(outputFilename, "w");
    if (file == NULL) {
        fprintf(stderr, "Invalid filename\n");
        return 1;
    }
    if (outputSound(output, file) == 1) {
        fclose(file);
        return 1;
    }
    else {
        return 0;
    }
}
