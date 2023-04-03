#include <stdio.h>
typedef char String[50];
typedef struct{
    String a;
} structTemp;

void askForIntInput (int nLowerBound, int nUpperBound, int *nInput){
    int  character;
    printf("Enter num: ");
    scanf("%d", nInput);
    while((*nInput < nLowerBound || *nInput > nUpperBound) )
    {
        //Clear the stdin so that program won't keep reading the wrong input ^-^
        while((character = getchar())!='\n' &&  character!=EOF); 
        printf("Invalid input, try again: ");
        scanf("%d", nInput);
    }

    
}

int main (){
    int nInput;
    askForIntInput(1,5, &nInput);

    printf("Nice! %d", nInput);
   
}