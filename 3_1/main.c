#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_NUMBER 150
#define LINE_LENGTH 150


void opening_error(); // If the file can't be opened, exit


int main(int argc, char** argv) {

    FILE *fptr;
    char text[LINE_NUMBER][LINE_LENGTH]; // array containing each line of the file

    if(argc < 2 || !(fptr = fopen(argv[1], "rb"))) opening_error();
    size_t nbLines = 1;
    for(; fgets(text[nbLines]+1, LINE_LENGTH, fptr); nbLines++){}
    nbLines++;
    size_t lineLength = strlen(text[1]+1)+1;
    fclose(fptr);

    // We want to surround the array by dots (eg.          .....
    //                                           123       .123.
    //                                           .8.  -->  ..8..
    //                                           45.       .45..
    //                                                     .....)

    for(int j = 0; j < lineLength; j++){
        text[0][j]         = '.';
        text[nbLines-1][j] = '.';
    }

    for(int i = 0; i < nbLines; i++){
        text[i][0]          = '.';
        text[i][lineLength-1] = '.';
    }

    // Searching for numbers
    int sum = 0;
    for(int i = 1; i < nbLines-1; i++){
        for(int j = 1; j < lineLength-1; j++){
            if('0' <= text[i][j] && text[i][j] <= '9'){
                char* ptr_j = &j; 
                int numberFound = strtol(&text[i][j], &ptr_j, 10);
                int firstDigitIndex = j;
                j += ptr_j - &text[i][j];
                bool isPart = false;
                for(int lineOffset = -1; lineOffset <= 1; lineOffset++){
                    isPart |= text[i+lineOffset][j] != '.';
                    isPart |= text[i+lineOffset][firstDigitIndex-1] != '.';
                }
                for(int digitIndex = 0; digitIndex < j-firstDigitIndex; digitIndex++){
                    isPart |= text[i-1][firstDigitIndex+digitIndex] != '.';
                    isPart |= text[i+1][firstDigitIndex+digitIndex] != '.';
                }
                if(isPart) sum += numberFound;
            }
        }
    }

    printf("Sum of part IDs : %d\n", sum);


    return 0;
}


void opening_error(){
    printf("Error: couldn't open file");
    exit(1);
}