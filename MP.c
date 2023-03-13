#include <stdio.h>
#include <string.h>
#define LEN 100
#define SIZE 1000
typedef char string[LEN];


typedef struct questionFormat
{
    string topic;
    int questionNum;
    string question;
    string choice1;
    string choice2;
    string choice3;
    string answer;

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
/*
KULANG:
1. question answer check
*/
int addRecord(struct questionFormat *A, int s){
   
    //start from index after last element, add records (quantity s)
    char dump;
        
        
        printf("Enter a question: ");
        gets(A[s].question);
        gets(A[s].question);
       

        printf("Enter the answer to the question: ");
        gets(A[s].answer);
        //add checking pa sa add record
        printf("Enter the topic of the question: ");
        gets(A[s].topic);
        printf("Enter choice 1: ");
        gets(A[s].choice1);
        printf("Enter choice 2: ");
        gets(A[s].choice2);
        printf("Enter choice 3: ");
        gets(A[s].choice3);

        //automatically set the question number
        
        A[s].questionNum = s+1;
         
        s++;
       

    return s;
}
/*
KULANG: 
1. proper password implementation
2. Other cases
*/
void manageData (string password,  questionFormat A[], int *s, FILE *fp){
    string strInput;
    int nInput;
   
    scanf("%c", strInput);
    do{
        printf("Enter the password: ");
        gets(strInput);
        
    }while(strcmp(password, strInput)!= 0);
    printf("1: Add a record\n");
    printf("2: Edit a record\n");
    printf("3: Delete a record\n");
    printf("4: Import data\n");
    printf("5: Export data\n");
    scanf("%d", &nInput);
    switch (nInput)
    {
    case 1: *s = addRecord(A, *s); printInFile(A, *s, fp); break;
    case 2:  break;
    case 3: break;
    }


}
void playGame (){

}
void printMenu(){
    char TRCorner = 191, TLCorner = 218, BRCorner = 217, BLCorner = 192, HorizontalBorder = 196, VerticalBorder = 179;
    printf("%c", TLCorner);
    for (int i =0; i <31; i++){
         printf("%c", HorizontalBorder);
    }
    printf("%c\n", TRCorner);
    printf ("%c\t1: Manage Data\t\t%c\n", VerticalBorder, VerticalBorder);
    printf ("%c\t2: Play Game\t\t%c\n", VerticalBorder, VerticalBorder);
    printf ("%c\t3: Exit\t\t\t%c\n", VerticalBorder, VerticalBorder);
    printf("%c", BLCorner);
    for (int i =0; i <31; i++){
         printf("%c", HorizontalBorder);
    }
    printf("%c\n", BRCorner);
    
}
int main(){
    questionFormat questions[100];
    string password = "Mam quatro po";
    int size=0;
    FILE *fp;
    
    printMenu();
    int menuChoice = 0;
    scanf("%d", &menuChoice);
    switch (menuChoice)
    {
    case 1: manageData(password, questions, &size, fp); break;
    case 2: playGame(); break;
    case 3: break;
    }
   /* while (menuChoice != 3){
    
    }*/
}