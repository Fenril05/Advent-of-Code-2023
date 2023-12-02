#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_NUMBER 100
#define MAX_LINE_LENGTH 200

#define NB_RED 12
#define NB_GREEN 13
#define NB_BLUE 14


void opening_error(); // If the file can't be opened, exit
bool parse_word(char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH], int i, int* j, char* word);
/*
Description: decodes a word (until it reaches a space or line break caracter)
Input:  text:               the text from a which a word must be parsed
        i:                  the line at which the word must be parsed
        j (Out):            the index of the first caracter of the word to be parsed
        lastWord (Out) :    the word parsed
Return: false if end of line was reached, true otherwise
*/


int main(int argc, char** argv) {

    FILE *fptr;
    char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH]; // array containing each line of the file
    int sumId = 0;

    if(argc < 2 || !(fptr = fopen(argv[1], "rb"))) opening_error();
    for(int i = 0; fgets(text[i], MAX_LINE_LENGTH, fptr); i++);
    fclose(fptr);
    
    
    for(int i = 0; i < MAX_LINE_NUMBER; i++){
        int* j = malloc(sizeof(int));
        *j = 9; // Starts at 8 because we're ignoring the Game #id: each time
        char* word = malloc(20);    // will store each word parsed
        int nbCubes; //will store the number of cubes
        int maxRedCubes = 1;
        int maxGreenCubes = 1;
        int maxBlueCubes = 1;
        bool lastWord = false;
        while(!lastWord){
            lastWord = parse_word(text, i, j, word);
            nbCubes = atoi(word);
            if(nbCubes){ // if its a number
                lastWord = parse_word(text, i, j, word);// decode the color
                // printf("%d %s ", nbCubes, word);
                if (!strcmp(word, "red") && nbCubes > maxRedCubes) maxRedCubes = nbCubes;
                if (!strcmp(word, "green") && nbCubes > maxGreenCubes) maxGreenCubes = nbCubes;
                if (!strcmp(word, "blue") && nbCubes > maxBlueCubes) maxBlueCubes = nbCubes;
            }
            // else printf("Err %d %s ", nbCubes, word);
        }
        sumId+=maxRedCubes*maxBlueCubes*maxGreenCubes;
        // printf("%d\n", sumId);
    }
    
    printf("The IDs sum to %d.\n", sumId);
    
    return 0;
}


void opening_error(){
    printf("Error: couldn't open file");
    exit(1);
}

bool parse_word(char text[MAX_LINE_NUMBER][MAX_LINE_LENGTH], int i, int* j, char* word){
    int k = 0; // une sorte d'offset à partir de l'indice j (premier char du mot)
    while(text[i][*j+k] != '\n' && text[i][*j+k] != ' '){
        word[k] = text[i][*j+k];
        k++;
    }
    if(word[k-1] == ',' || word[k-1] == ';') word[k-1] = '\0';
    else word[k] = '\0';
    *j+=k+1;
    // printf("/%s/%d", word, text[i][*j-1] != '\n');
    return text[i][*j-1] == '\n';
}