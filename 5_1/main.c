#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_NUMBER 250
#define MAX_LINE_LENGTH 250

#define MAX_CONV 10
#define MAX_ID 9999999999

#define MAX_SEEDS 10


void opening_error(); // If the file can't be opened, exit

int main(int argc, char** argv) {

    FILE *fptr;
    char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH]; // array containing each line of the file

    if(argc < 2 || !(fptr = fopen(argv[1], "rb"))) opening_error();
    size_t nbLines = 0;
    for(; fgets(text[nbLines], MAX_LINE_LENGTH, fptr); nbLines++){}
    // size_t lineLength = strlen(text[0]);
    fclose(fptr);

    // int map[MAX_ID];
    // int idArray[MAX_SEEDS];
    // memset(idArray, 0xFF, MAX_SEEDS*sizeof(int));
    // int seedIndex = 0;
    // for(char* i = (char*)text+6; *i != '\n'; seedIndex++){
    //     i++;
    //     idArray[seedIndex] = strtol(i, &i, 10);
    // }
    
    // for(int line_i = 3, conversionIndex = 0; line_i < nbLines && conversionIndex < MAX_CONV; conversionIndex++){
        
    //     for(int j = 0; j < MAX_ID; j++){
    //         map[j] = j;
    //     }
    //     while (text[line_i][0] != '\n'){
    //         char* j = text[line_i];
    //         int dest = strtol(j, &j, 10);
    //         int src = strtol(j, &j, 10);
    //         int range = strtol(j, &j, 10);

    //         for(int k = 0; k < range; k++){
    //             map[src+k] = dest+k;
    //         }
    //     }
    //     line_i++;

    //     for(int j = 0; j < MAX_SEEDS; j++){
    //         if(idArray[j] != -1){
    //             idArray[j] = map[idArray[j]];
    //         }
    //     }
    // }

    // unsigned int minLocationId = INT_MAX;
    // for(int i = 0; i < MAX_SEEDS; i++){
    //     if((unsigned int)idArray[i] < minLocationId) minLocationId = idArray[i];
    // }

    // // for(int bite = 0; bite < MAX_ID; bite++){
    // //     printf("%d -> %d\n", bite, map[1][bite]);
    // // }

    // printf("The longest location number is %d", minLocationId);

    // return 0;
}

void opening_error(){
    printf("Error: couldn't open file");
    exit(1);
}
