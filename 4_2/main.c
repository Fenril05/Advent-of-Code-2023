#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_NUMBER 200
#define MAX_LINE_LENGTH 120

#define MAX_WINNING_NUMBERS 10
#define MAX_ELF_NUMBERS 25


void opening_error(); // If the file can't be opened, exit
int c_atoi(char digit); // Single character to integer, 0 if not a digit.
int get_cardPoints(int i, int winningNumbersArray[MAX_LINE_NUMBER][MAX_WINNING_NUMBERS], int elfNumbersArray[MAX_LINE_NUMBER][MAX_ELF_NUMBERS]);

int main(int argc, char** argv) {

    FILE *fptr;
    char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH]; // array containing each line of the file

    if(argc < 2 || !(fptr = fopen(argv[1], "rb"))) opening_error();
    size_t nbLines = 0;
    for(; fgets(text[nbLines], MAX_LINE_LENGTH, fptr); nbLines++){}
    size_t lineLength = strlen(text[0]);
    fclose(fptr);
    
    int winningNumbersArray[MAX_LINE_NUMBER][MAX_WINNING_NUMBERS] = {};
    int elfNumbersArray[MAX_LINE_NUMBER][MAX_ELF_NUMBERS] = {};
    int totalNumberNb = (lineLength-12)/3;

    for(int i = 0; i < nbLines; i++){
        int numberIndex = 0;
        int offset = 10; // Will count game number caracters and the separator in the middle
        for(; text[i][numberIndex*3+offset] != '|'; numberIndex++){
            winningNumbersArray[i][numberIndex] = c_atoi(text[i][numberIndex*3+offset])*10 + c_atoi(text[i][numberIndex*3+offset+1]);
        }
        offset+=2;
        int winningNumbersNb = numberIndex+1;
        for(; numberIndex < totalNumberNb; numberIndex++){
            elfNumbersArray[i][numberIndex-winningNumbersNb+1] = c_atoi(text[i][numberIndex*3+offset])*10 + c_atoi(text[i][numberIndex*3+offset+1]);
        }
    }

    int sum = 0;
    int cardAmount[MAX_LINE_NUMBER];
    for(int i = 0; i < MAX_LINE_NUMBER; i++){
        if (winningNumbersArray[i][0] != 0) cardAmount[i] = 1;
        else cardAmount[i] = 0;
    }

    for(int i = 0; i < MAX_LINE_NUMBER; i++){
        int nbPoints = get_cardPoints(i, winningNumbersArray, elfNumbersArray);
        for(int j = 1; j <= nbPoints; j++){
            cardAmount[i+j]+=cardAmount[i];
        }
        sum += cardAmount[i];
    }

    printf("The total number of points is : %d\n", sum);

    return 0;
}

void opening_error(){
    printf("Error: couldn't open file");
    exit(1);
}

int c_atoi(char digit){
    if('0' <= digit && digit <= '9') return digit - 0x30;
    return 0;
}

int get_cardPoints(int i, int winningNumbersArray[MAX_LINE_NUMBER][MAX_WINNING_NUMBERS], int elfNumbersArray[MAX_LINE_NUMBER][MAX_ELF_NUMBERS]){
    int nbPoints = 0;
    for(int win_j = 0; win_j < MAX_WINNING_NUMBERS && winningNumbersArray[i][win_j] != 0; win_j++){
        for(int elf_j = 0; elf_j < MAX_ELF_NUMBERS && elfNumbersArray[i][elf_j] != 0; elf_j++){
            if(elfNumbersArray[i][elf_j] == winningNumbersArray[i][win_j]){
                nbPoints++;
                break;
            }
        }
    }
    return nbPoints;
}