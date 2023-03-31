#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main (){
time_t timeVar; // initialize time
int lastQuesNum = 7;
     srand( time(&timeVar));
    //generate random odd value from 1-last question num
    int nRandomNum = rand() % (lastQuesNum+1);
    if (nRandomNum == 0)
        nRandomNum++;
        printf("%d", nRandomNum);
}
