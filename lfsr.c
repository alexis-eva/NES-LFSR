#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for usleep
#define CLRBUF while(getchar() != '\n') {} // clears input buffer
#define WINCLR system("cls");
#define UNCLR system("clear");
#if defined(_WIN32) // cls on windows, clear on unix
    WINCLR
#else
    UNCLR
#endif

int main(void) {

    int temp; // to store the XOR result
    int count = 1; // count number of iterations
    unsigned int shift_register = 1; // the shift register! 15 bits of bitwise math nonsense
    int length; // how many times?
    short int speed; // how fast?
    short int mode; // MODE 0 = 0XOR1, MODE 1 = 0XOR6
    int speedOptions[3]; // how fast options (numbers of microseconds)
    speedOptions[0] = 133333;
    speedOptions[1] = 66666;
    speedOptions[2] = 33333;
    int selection; // for options

    puts("*** 15-bit linear feedback shift register simulator ***");
    puts("based on the NES noise sound generator");
    printf("Which MODE? 0 for 0XOR1, 1 for 0XOR6: "); // first, fill out some options
    while((scanf("%d", &selection) !=1 ) || (selection !=0 && selection !=1 )) { // if any of these checks fail, input validation loop
        printf("Wrong input! Enter 0 or 1: ");
        CLRBUF
    }
    mode = selection;
    printf("How fast? 0 = slow, 1 = medium, 2 = fast: ");
    while((scanf("%d", &selection) !=1 ) || (selection !=0 && selection !=1 && selection!=2 )) { // if any of these checks fail, input validation loop
        printf("Wrong input! Enter 0, 1, or 2: ");
        CLRBUF
    }
    speed = selection;
    printf("Go for how many steps? 500 recommended: ");
    while((scanf("%d", &selection) !=1 ) || selection < 1 ) { // if any of these checks fail, input validation loop
        printf("Wrong input! Enter a positive integer: ");
        CLRBUF
    }
    length = selection;

    for(int i = 0; i < length; i++) { // now to actually do the stuff
    WINCLR // replaced with UNCLR on unix systems
        for (int j = 0; j < 15; j++) // print each bit of the lfsr
            printf("%d", ((shift_register >> j) & 1)); // print a bit
        printf(" %d", count);
        usleep(speedOptions[speed]);
        if (mode == 0)
            temp = ((shift_register & 0x4000) >> 14) ^ ((shift_register & 0x2000)  >> 13); // XOR bit 0 and bit 1, put in temp
        else // MODE flag is set
            temp = ((shift_register & 0x4000) >> 14) ^ ((shift_register & 0x100) >> 8); // XOR bit 0 and bit 6, put in temp
        shift_register = (shift_register << 1) | temp; // shift everything, put temp in bit 14
        count++;
    }

    return 0;
}
