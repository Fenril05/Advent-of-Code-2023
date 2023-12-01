#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    FILE *fptr;
    int sum = 0;
    char lastRead;
    int chiffre1;
    int chiffre2;

    if((fptr = fopen("D:\\Projets C\\Advent of Code 2023\\input.txt", "rb")) == NULL){
        printf("Error : Coudn't open");
        exit(1);
    }

    while((lastRead = fgetc(fptr)) != '\0') {

        // printf("%c", lastRead);
        if('0' <= lastRead && lastRead <= '9') {
            chiffre1 = lastRead - '0';
            chiffre2 = chiffre1;
        }
        else {chiffre1 = -1;}

        while((lastRead = fgetc(fptr)) != 0x0A){
            // printf("%c", lastRead);
            if('0' <= lastRead && lastRead <= '9'){
                if(chiffre1 == -1) {chiffre1 = lastRead - '0';}
                chiffre2 = lastRead - '0';
            }
        }

        // printf(" %d%d\n", chiffre1, chiffre2);
        sum += chiffre1*10 + chiffre2;

    }


    printf("%d", sum);

    fclose(fptr);
    return 0;
}