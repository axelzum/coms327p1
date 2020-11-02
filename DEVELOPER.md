#### Part B regrade
Missed 5 points for using static instead of malloc in gensine2. Changed to malloc so gensine2 can make 
multiple objects without overwriting memory.

Missed 34 points for part3, program got a segmentation fault. This should be fixed with the malloc in gensine2.
Also added some free() statments to try and fix this.

Missed 3 points for not returning 1? The outputSound functions returns 1, modified main to return 1 on failure too.

#### Part A regrade
Missed 10 points in part A for incorrectly adding two sine waves in gendial. Fixed
in part B to average the sine wave values instead of averaging the frequencies.

##### Part B notes
Implementation of no filename argument uses methods from part a.

##### Part A notes
Could use better input validation for the 10-digit phone number user input in main2.c.
