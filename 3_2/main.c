#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_NUMBER 150
#define LINE_LENGTH 150


void opening_error(); // If the file can't be opened, exit

typedef struct{
    int i;
    int j;
} coordinate;

typedef struct{
    int number;
    coordinate star;
} starNeighbor;

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
    starNeighbor starNeighborArray[10000];
    int nbStarNeighbors = 0;
    for(int i = 1; i < nbLines-1; i++){
        for(int j = 1; j < lineLength-1; j++){
            if('0' <= text[i][j] && text[i][j] <= '9'){
                char* ptr_j = &j; 
                int numberFound = strtol(&text[i][j], &ptr_j, 10);
                int firstDigitIndex = j;
                j += ptr_j - &text[i][j];
                for(int lineOffset = -1; lineOffset <= 1; lineOffset++){
                    if (text[i+lineOffset][j] == '*'){
                        starNeighborArray[nbStarNeighbors].number = numberFound;
                        starNeighborArray[nbStarNeighbors].star.i = i+lineOffset;
                        starNeighborArray[nbStarNeighbors].star.j = j;
                        nbStarNeighbors++;
                    }
                    if(text[i+lineOffset][firstDigitIndex-1] == '*'){
                        starNeighborArray[nbStarNeighbors].number = numberFound;
                        starNeighborArray[nbStarNeighbors].star.i = i+lineOffset;
                        starNeighborArray[nbStarNeighbors].star.j = firstDigitIndex-1;
                        nbStarNeighbors++;
                    }
                }
                for(int digitIndex = 0; digitIndex < j-firstDigitIndex; digitIndex++){
                    if(text[i-1][firstDigitIndex+digitIndex] == '*'){
                        starNeighborArray[nbStarNeighbors].number = numberFound;
                        starNeighborArray[nbStarNeighbors].star.i = i-1;
                        starNeighborArray[nbStarNeighbors].star.j = firstDigitIndex+digitIndex;
                        nbStarNeighbors++;
                    }
                    if(text[i+1][firstDigitIndex+digitIndex] == '*'){
                        starNeighborArray[nbStarNeighbors].number = numberFound;
                        starNeighborArray[nbStarNeighbors].star.i = i+1;
                        starNeighborArray[nbStarNeighbors].star.j = firstDigitIndex+digitIndex;
                        nbStarNeighbors++;
                    }
                }
            }
        }
    }

    int sumOfProducts = 0;
    for(int i = 0; i < nbStarNeighbors; i++){
        if(starNeighborArray[i].star.i != 0){    // On va "supprimer" des éléments en leur mettant star.i = 0
            int product = starNeighborArray[i].number;
            for(int j = i+1; j < nbStarNeighbors; j++) {
                if(starNeighborArray[i].star.i == starNeighborArray[j].star.i && starNeighborArray[i].star.j == starNeighborArray[j].star.j){
                    if(product == starNeighborArray[i].number){
                        product *= starNeighborArray[j].number;
                        starNeighborArray[j].star.i = 0;
                    }
                    else{
                        product = 0;
                        starNeighborArray[j].star.i = 0;
                    }
                }
            }
            if(product == starNeighborArray[i].number) product = 0;
            sumOfProducts += product;
        }
    }

    printf("Sum of gear ratios : %d\n", sumOfProducts);


    return 0;
}


void opening_error(){
    printf("Error: couldn't open file");
    exit(1);
}