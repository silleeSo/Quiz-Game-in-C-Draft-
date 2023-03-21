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
//question 150, answer and choices 30, topic 20

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

int addRecord(struct questionFormat *A, int s){
   
    //start from index after last element, add records (quantity s)
    string150 question;
    string30 answer;
    int exists = 0;
        printf("Enter a question: ");
        gets(question);
        gets(question);
        //gets(A[s].question);
       
        printf("Enter the answer to the question: ");
        gets(answer);

        //loop thru all elements and check ques n ans
        for (int i = 0; i < s; i++){
            if (!strcmp(A[i].question, question) && !strcmp(A[i].answer, answer))
                exists = 1;
        }
        //gets(A[s].answer);
        //add checking pa sa add record
        if (exists == 1) //if record exists, print message and end function, getting back to manage data
            printf("Record already exists!\n");
        else { //if it does not exist: 
            strcpy(A[s].question, question); //get the needed information
            strcpy(A[s].answer, answer);
            printf("Enter the topic of the question: ");
            gets(A[s].topic);
            printf("Enter choice 1: ");
            gets(A[s].choice1);
            printf("Enter choice 2: ");
            gets(A[s].choice2);
            printf("Enter choice 3: ");
            gets(A[s].choice3);

             //automatically set the question number:
            int lastQuesNum = 0;
            for (int i = 0; i < s; i++) //loop through the array of structs 
           // look for the question with the same topic (as added question) with the highest num 
                if (!strcmp(A[i].topic, A[s].topic) &&  A[i].questionNum > lastQuesNum)
                    lastQuesNum = A[i].questionNum;
                //take the last num and add one to it, set it as the new question num
                A[s].questionNum = lastQuesNum+1;

            //increment array size
            s++;
            //print notifying message
            printf("\nRecord added successfully!\n");
            
        }
        
    //return array size
    return s;
}

int importData(struct questionFormat *A, int s, FILE *fp){
    string30 fileName;
    printf("Import file name (txt) to import: ");
    scanf("%s", fileName);
    fp = fopen(fileName, "r");
    int pos = 0;
    int strInd =0, arrInd = 0; //CHANGE ARRAY INDEX N SET TO S IF EVER MAM SAYS NA NEED LANG APPEND, NOT REWRITE
    char ch;
    while (!feof(fp)){ //** position refers to the position or member of the struct (0-6)
        fscanf(fp, "%c", &ch); //Get the character in the loop (loop through file characters)
        if (ch == '\n') { //if character is newline, check if we are in position 7
            if (pos == 7){
                arrInd++; //if we are in position 7 (the separation between questions)
                pos = 0; //reset position to zero and increment struct array index
            }
            else // if it is any other position than 7
                pos++; //simply increment position
            strInd = 0; // Reset string index for both cases, meaning everytime the program finishes reading one line, reset string index for next
            }
        //topic
        else if (pos == 0){
            A[arrInd].topic[strInd] = ch; // set the value of a character in question (of array struct element) to ch
            strInd++; //increment the string index
            A[arrInd].topic[strInd] = '\0'; //add null byte after
        } //The program will keep coming back to this, so long as it does not detect a newline character and we are in position 1, same with the rest
        //number
        else if (pos == 1){  //if we are in the question number line/position
           A[arrInd].questionNum = (int)ch - 48; //set the question num (of struct array element) to ch converted to int - 48
        }                                       // 1 was read as '1', meaning if we convert to int it is == 49. Subtracting 48 results to 1.
        //Question
        else if (pos == 2){
            A[arrInd].question[strInd] = ch;
            strInd++;
            A[arrInd].question[strInd] = '\0';
        }
        //Choice 1
        else if (pos == 3){
            A[arrInd].choice1[strInd] = ch;
            strInd++;
            A[arrInd].choice1[strInd] = '\0';
        }
        //Choice 2
        else if (pos == 4){
            A[arrInd].choice2[strInd] = ch;
            strInd++;
            A[arrInd].choice2[strInd] = '\0';
        }
        //Choice 3
         else if (pos == 5){
            A[arrInd].choice3[strInd] = ch;
            strInd++;
            A[arrInd].choice3[strInd] = '\0';
        }
        //Answer
         else if (pos == 6){
            A[arrInd].answer[strInd] = ch;
            strInd++;
            A[arrInd].answer[strInd] = '\0';
        }

    }
    
        fclose(fp); //close file
   
       s=arrInd;
        printInFile(A, s, fp);
        printf("\nData imported successfully!\n");
        return s;
}
/*
KULANG: 
1. proper password implementation
2. Other cases
*/
void manageData (string30 password,  questionFormat A[], int *s, FILE *fp){
    string30 strInput;
    int nInput = 0;
   int i =0;
   char ch;
    scanf("%c", strInput);
    do{
        printf("Enter the password: ");
       gets(strInput);
    /*
    METHOD 1 (DOESNT WORK):
        do{
            //scanf("%c", &ch);
            ch = getch();
            //printf("*");
            if (ch!='\n'){
                strInput[i] = ch;
                i++;
                strInput[i] = '\0';
               
            }
        }while (i < LEN && ch!='\n');
    
    METHOD 2 (NO BACKSPACE):
    printf("Enter your password:\n");
    do
    {
        strInput[i]=getch();
        printf("*");
        i++;
    }
    while(strInput[i-1]!='\r');
    strInput[i-1]='\0';*/
        
    }while(strcmp(password, strInput)!= 0);
     do{
    printf("\nMANAGE DATA MENU\n");
    printf("1: Add a record\n");
    printf("2: Edit a record\n");
    printf("3: Delete a record\n");
    printf("4: Import data\n");
    printf("5: Export data\n");
    printf("6: Go back to main menu\n");
    scanf("%d", &nInput);
    while (nInput < 1 || nInput > 6) {
        printf("Invalid input, try again: ");
        scanf("%d", &nInput);  
    }
            //need ba input validation for floats???
   
        switch (nInput)
        {
            case 1: *s = addRecord(A, *s); printInFile(A, *s, fp);  break; //REMOVE PRINT AFTER, ONLY FOR TTEST
            case 2:  break;
            case 3: break;
            case 4: *s = importData(A, *s, fp); break;
            case 5: break;

    }

    } while (nInput != 6);
    


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
    string30 password = "Mam quatro po";
    int size=0;
    int menuChoice = 0;
    FILE *fp;
    do{
        printMenu();
    
        scanf("%d", &menuChoice);
        switch (menuChoice)
        {
            case 1: manageData(password, questions, &size, fp); break;
            case 2: playGame(); break;
            case 3: break;
        }


    }while (menuChoice!=3);
   
  return 0;
}