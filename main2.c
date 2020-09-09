#include "gensnd.h"

#include <stdio.h>

int main(int argc, char const *argv[]) {

    char phoneNumber[11];

    printf("Input a 10 digit phone number:\n");
    scanf("%s", phoneNumber);

    dualtone(phoneNumber[0]);
    silence(8000, 0.25);
    dualtone(phoneNumber[1]);
    silence(8000, 0.25);
    dualtone(phoneNumber[2]);
    silence(8000, 0.25);
    dualtone(phoneNumber[3]);
    silence(8000, 0.25);
    dualtone(phoneNumber[4]);
    silence(8000, 0.25);
    dualtone(phoneNumber[5]);
    silence(8000, 0.25);
    dualtone(phoneNumber[6]);
    silence(8000, 0.25);
    dualtone(phoneNumber[7]);
    silence(8000, 0.25);
    dualtone(phoneNumber[8]);
    silence(8000, 0.25);
    dualtone(phoneNumber[9]);

    return 0;
}
