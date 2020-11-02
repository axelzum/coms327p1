# coms327p1

### Part C
Running the makefile in this project generates one executable: playsong

#### playsong
Playsong takes a song inputfile name. The file is laid out with tags SAMPLERATE, WAVE, SOUND, SONG
in that speciic order with a certain definition of subline as laid out in project instuctions.

The program uses this information to generate one output file with a sound waveform that plays
the notes represented in the song file.

### Part B
Running the makefile in this project generates one executable: dtmf

#### dtmf
Allows two user command line arguments: phoneNumber and filename
phoneNumber(REQUIRED): The phone number sequence to convert to waveform. The 
phone number must consist only of digits 0-9, *, #, A, B, C, D.

filename: If included, outputs the sine wave to this filename. If no filename is
included as an argument program outputs sinewave to stdout.

### Part A
Running the makefile in this project generates two executables: gensine and gendial.

#### gensine
Asks the user to input a positive frequency, sample rate, and duration.
These values are used to generate sine waves that can be converted into an audio tone.

The freqency determines the pitch of the sound created. The sample rate determines
how many samples are taken over a certain period of time. And the duration determines
how long the sound will play for.

#### gendial
Asks the user to input a 10-digit phone number. The phone number must consist only of digits
0-9, *, #, A, B, C, D.
Given this number genail prints a series of sine waves reprenting the tone that results
from each of these digits being pressed on a touch-tone telephone keypad. The audio created
plays each tone with a frequency of 8000Hz for a duration of 500ms with 250ms of silence
inbetween each tone.
