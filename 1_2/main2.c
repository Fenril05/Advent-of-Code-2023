#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 6



char lastRead[N] = "aaaaa"; // stores the N-1 last read characters, needs to be initialized with non null characters



char push(char x){  // we are using lastRead as a sort of char queue
    for(int i = 0; lastRead[i] != '\0'; i++){
        lastRead[i] = lastRead[i+1];
    }

    lastRead[N-2] = x;
    return x;
}

int check(){    // returns a digit if the last character read IS a digit or COMPLETES the name of a digit in the lastRead queue, returns -1 otherwise
    if('0' <= lastRead[N-2] && lastRead[N-2] <= '9'){
        return lastRead[N-2] - '0';
    }
    bool one = true, two = true, three = true, four = true, five = true, six = true, seven = true, eight = true, nine = true;
    for(int i = 0; i < N; i++){  // Yandere Dev code be like
        if(i < 3 && lastRead[N-4+i] !=   "one"[i]) one = false;
        if(i < 3 && lastRead[N-4+i] !=   "two"[i]) two = false;
        if(i < 5 && lastRead[N-6+i] != "three"[i]) three = false;
        if(i < 4 && lastRead[N-5+i] !=  "four"[i]) four = false;
        if(i < 4 && lastRead[N-5+i] !=  "five"[i]) five = false;
        if(i < 3 && lastRead[N-4+i] !=   "six"[i]) six = false;
        if(i < 5 && lastRead[N-6+i] != "seven"[i]) seven = false;
        if(i < 5 && lastRead[N-6+i] != "eight"[i]) eight = false;
        if(i < 4 && lastRead[N-5+i] !=  "nine"[i]) nine = false;
    }
    if(one)   return 1;
    if(two)   return 2;
    if(three) return 3;
    if(four)  return 4;
    if(five)  return 5;
    if(six)   return 6;
    if(seven) return 7;
    if(eight) return 8;
    if(nine)  return 9;
    return -1;
}

int main()
{
    FILE *fptr;
    int sum = 0;
    int digit;        // the digit from the last read, -1 if not a digit
    int chiffre1;
    int chiffre2;

    if((fptr = fopen("D:\\Projets C\\Advent of Code 2023\\1_2\\input.txt", "rb")) == NULL){
        // printf("Error : Coudn't open");
        exit(1);
    }

    while(push(fgetc(fptr)) != '\0') {

        digit = check();
        // printf("%s %d\n", lastRead, digit);
        if(digit != -1) {
            chiffre1 = digit;
            chiffre2 = chiffre1;
        }
        else {chiffre1 = -1;}

        while(push(fgetc(fptr)) != 0x0A){
            // printf("%c", lastRead);
            digit = check();
            // printf("%s %d\n", lastRead, digit);
            if(digit != -1){
                if(chiffre1 == -1) {chiffre1 = digit;}
                chiffre2 = digit;
            }
        }

        // printf(" %d%d\n", chiffre1, chiffre2);
        sum += chiffre1*10 + chiffre2;

    }

    printf("%d", sum);

    fclose(fptr);
    return 0;
}