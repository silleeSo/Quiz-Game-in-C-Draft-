#include <stdio.h>
#include <string.h>
#include <conio.h>
#define LEN1 20
#define LEN2 30
#define LEN3 150
#define SIZE 1000
typedef char string20[LEN1];
typedef char string30[LEN2];
typedef char string150[LEN3];
typedef struct questionFormat
{
    string20 topic;
    int questionNum;
    string150 question;
    string30 choice1;
    string30 choice2;
    string30 choice3;
    string30 answer;

}questionFormat;

void printInFile(struct questionFormat *A, int s, FILE *fp){
    fp = fopen("records.txt", "w");
    for(int i = 0; i < s; i++){
        fprintf(fp, "%s\n", A[i].topic);
        fprintf(fp, "%d\n", A[i].questionNum);
        fprintf(fp, "%s\n", A[i].question);
        fprintf(fp, "%s\n", A[i].choice1);
        fprintf(fp, "%s\n", A[i].choice2);
        fprintf(fp, "%s\n", A[i].choice3);
        fprintf(fp, "%s\n", A[i].answer);
    }
    fclose(fp);
}

int main(){
FILE *fp;
questionFormat A[100];
int s= 0;
char ch;
 string30 fileName;
    //printf("Import file name (txt) to import: ");
    //scanf("%s", fileName);
    fp = fopen("sample.txt", "r");
    /*
        fgets(A[s].topic, LEN1, fp);
        fscanf(fp,"%d", &A[s].questionNum);
        fgets(A[s].question, LEN3, fp);
        fgets(A[s].choice1, LEN2, fp);
        fgets(A[s].choice2, LEN2, fp);
        fgets(A[s].choice3, LEN2, fp);
        fgets(A[s].answer, LEN2, fp);
      
        s++;*/

    int pos = 0;
    int strInd =0, arrInd = 0;
    while (!feof(fp)){
        fscanf(fp, "%c", &ch);
        if (ch == '\n') {
            if (pos == 7){
                arrInd++;
                pos = 0;
            }
            else
                pos++;
            strInd = 0;
            }
        //topic
        else if (pos == 0){
            A[arrInd].topic[strInd] = ch;
            strInd++;
            A[arrInd].topic[strInd] = '\0';
        }
        //number
        else if (pos == 1){
           A[arrInd].questionNum = (int)ch - 48;
        }
        else if (pos == 2){
            A[arrInd].question[strInd] = ch;
            strInd++;
            A[arrInd].question[strInd] = '\0';
        }
        else if (pos == 3){
            A[arrInd].choice1[strInd] = ch;
            strInd++;
            A[arrInd].choice1[strInd] = '\0';
        }
        else if (pos == 4){
            A[arrInd].choice2[strInd] = ch;
            strInd++;
            A[arrInd].choice2[strInd] = '\0';
        }
         else if (pos == 5){
            A[arrInd].choice3[strInd] = ch;
            strInd++;
            A[arrInd].choice3[strInd] = '\0';
        }
         else if (pos == 6){
            A[arrInd].answer[strInd] = ch;
            strInd++;
            A[arrInd].answer[strInd] = '\0';
        }

    }
//INCREMENT ARRIND
  
//printf("%s\n%d\n%s\n%s\n%s\n%s\n%s", A[0].topic, A[0].questionNum, A[0].question, A[0].choice1, A[0].choice2, A[0].choice3, A[0].answer);
 fclose(fp);
 //printf("%s %d", A[0].topic, A[0].questionNum);
   for(int i = 0; i < arrInd; i++){
            printf("%s\n%d\n%s\n%s\n%s\n%s\n%s ", A[i].topic, A[i].questionNum, A[i].question, A[i].choice1, A[i].choice2, A[i].choice3, A[i].answer);
       }
}