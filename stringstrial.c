#include <stdio.h>
#include <conio.h>
#include <string.h>

void 
getStrInput(char strInput[31], int nMaxLength)
{
    char cInput;
    int nInd = 0;
    int nLoopCtr = 0;

    do
    {    // scanf character
        scanf("%c", &cInput);

        // if the character is not \n store it into string
        if (cInput!='\n')
        {
            strInput[nInd] = cInput;
            nInd++;
            strInput[nInd] = '\0';
        }       
        nLoopCtr++;
    } while (strlen(strInput) < nMaxLength && (cInput!='\n' || nLoopCtr < 2));
}
int main(){
    char stringTest[31];
    int nInput;
    //printf("Enter number: ");
    //scanf("%d", &nInput);
    printf("Enter a string: ");
    getStrInput(stringTest, 30);
    printf("Enter a string: ");
    getStrInput(stringTest, 30);
    printf("%s", stringTest);
}