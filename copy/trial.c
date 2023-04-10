#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int main(){
    time_t timeVar;
    srand(time(&timeVar));
    int nLastQuesNum = 5;
    int nRandomNum;
    int arr[nLastQuesNum];
    if (!strcmp("AH", "AH")){
    for (int i = 0; i < 15; i++){
        nRandomNum = rand() % (nLastQuesNum + 1);
        printf("%d", nRandomNum);
    }}
    /*for (int i = 0; i < nLastQuesNum; i++){
        arr[i] = i;
    }
    for (int i = 0; i < nLastQuesNum; i++){
        printf("%d ", arr[i]);
    }*/
        
        
}