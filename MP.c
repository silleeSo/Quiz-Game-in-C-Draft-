#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#define LEN1 20
#define LEN2 30
#define LEN3 150
#define SIZE 1000
typedef char string20[LEN1];
typedef char string30[LEN2];
typedef char string150[LEN3];

/*  THINGS TO MODULARIzED
    1. make topics array
    2. match question topic and question num to a specific question in array of struct

*/

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

//MANAGE FUNCTIONS
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

//QUERIES
//checking if answer is actually in choices?
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
            printf("\nRecord already exists!\n");
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

void exportData(struct questionFormat *A, int s, FILE *fp){

     string30 fileName;
    printf("Import file name (txt) to export to: ");
    scanf("%s", fileName);
    fp = fopen(fileName, "w");
    for(int i = 0; i < s; i++){
        fprintf(fp, "%s\n", A[i].topic);
        fprintf(fp, "%d\n", A[i].questionNum);
        fprintf(fp, "%s\n", A[i].question);
        fprintf(fp, "%s\n", A[i].choice1);
        fprintf(fp, "%s\n", A[i].choice2);
        fprintf(fp, "%s\n", A[i].choice3);
        fprintf(fp, "%s\n\n", A[i].answer);
    }
    fclose(fp);
    printf("\nData exported successfully!\n");
}
/*
KULANG: 
1. proper password implementation
2. Other cases
Queries:
1. need ba input validation for floats???
FOR PASSWORD MASK
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

//QUERIES
//if no record paano?? display warning?
//ADD VALIDATION NA PAG INPUT IF ZERO KASO FIRST CYCLE PALANG NAMAN
// ADD VALIDATION IF NO RECORDS TAS U TRY TO EDIT
void editRecord(struct questionFormat *A, int s){
    //create array of topics
    string20 topics[s];
    string20 selectedTopic;                                     //index of the selected question in the array 
    int ctrTopics, exists, arrayTopicsSize, nInput, selectedIndex; //counter for topics array
    int loopCtr = 0;

    do{
        ctrTopics = 0, exists = 0, arrayTopicsSize = 0, selectedIndex = 0; //reset variables
    for (int i = 0; i < s; i++){
        for (int j = 0; j < ctrTopics; j++)
            if (!strcmp(A[i].topic, topics[j])) // check if exists na ung topic of current ques in topics array
                exists = 1;
        if (!exists) {//IF WALA PA, ADD TO ARRAY
            strcpy(topics[ctrTopics], A[i].topic); // add to array of topics
            ctrTopics++;

        }

        exists = 0; //reset flag variable
    }//end of atopics array creation
    //ctrTopics = size of topics array
    
    //if one edit has already been made, add new option to go back to manage menu
        if (loopCtr > 0)
            printf("0 - Go back to main menu\n");

        printf("Select a Topic: \n");
        //display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);
        
        scanf("%d", &nInput);

        //ADD VALIDATION NA PAG INPUT IF ZERO KASO FIRST CYCLE PALANG NAMAN
        if (nInput != 0){
        strcpy(selectedTopic, topics[nInput-1]); //-1 since index starts at 0, input starts at 1 lowest
        //if no records paano??
       
        //display questions - WORKS!
        printf("Enter a question number: \n");
        for (int i = 0; i < s; i++){
            if (!strcmp(A[i].topic, selectedTopic))

                printf("Question %d - %s\n", A[i].questionNum , A[i].question);
        }
        //take question index in 1d array
         scanf("%d", &nInput);
        while (A[selectedIndex].questionNum != nInput || strcmp(A[selectedIndex].topic, selectedTopic) != 0)
            selectedIndex++; //get index of selected question
        printf("Which field would you like to edit?\n1 - Topic\n2 - Question\n3 - choice 1\n4 - choice 2\n5 - choice 3\n6 - answer\n");
        scanf("%d", &nInput);
        printf("Input the new content of question %d ", A[selectedIndex].questionNum);
        switch (nInput)
        {
        case 1: 
            printf("topic: ");
            gets(A[selectedIndex].topic);
            gets(A[selectedIndex].topic);
            break;
        case 2: 
            printf("question: ");
            gets(A[selectedIndex].question);
            gets(A[selectedIndex].question);
            break;
        case 3: 
            printf("choice 1: ");
            gets(A[selectedIndex].choice1);
            gets(A[selectedIndex].choice1);
            break;
        case 4: 
            printf("choice 2: ");
            gets(A[selectedIndex].choice2);
            gets(A[selectedIndex].choice2);
            break;
        case 5: 
            printf("choice 3: ");
            gets(A[selectedIndex].choice3);
            gets(A[selectedIndex].choice3);
            break;
        case 6: 
            printf("answer: ");
            gets(A[selectedIndex].answer);
            gets(A[selectedIndex].answer);
            break;
        default:
            break;
        }
        
        printf("\nRecord edited successfully!\n\n");
        loopCtr ++;}
    } while (nInput!=0);
       
     
}//TO ADD: INPUT VALIDATION FOR EVERY QUESTION

int deleteRecord(struct questionFormat *A, int s){
    //create array of topics
    string20 topics[s];
    string20 selectedTopic;                                     //index of the selected question in the array 
    int ctrTopics, exists, arrayTopicsSize, nInput, selectedIndex; //counter for topics array
    int loopCtr = 0, currQuesNum =0;

    do{
        ctrTopics = 0, exists = 0, arrayTopicsSize = 0, selectedIndex = 0; //reset variables
    for (int i = 0; i < s; i++){
        for (int j = 0; j < ctrTopics; j++)
            if (!strcmp(A[i].topic, topics[j])) // check if exists na ung topic of current ques in topics array
                exists = 1;
        if (!exists) {//IF WALA PA, ADD TO ARRAY
            strcpy(topics[ctrTopics], A[i].topic); // add to array of topics
            ctrTopics++;

        }

        exists = 0; //reset flag variable
    }//end of atopics array creation
    //ctrTopics = size of topics array

        printf("Select a Topic: \n");
        //display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);
        
        scanf("%d", &nInput);

        //ADD VALIDATION NA PAG INPUT IF ZERO KASO FIRST CYCLE PALANG NAMAN
        
        strcpy(selectedTopic, topics[nInput-1]); //-1 since index starts at 0, input starts at 1 lowest
        //if no records paano??
       
        //display questions - WORKS!
        printf("Enter a question number: \n");
        for (int i = 0; i < s; i++){
            if (!strcmp(A[i].topic, selectedTopic))

                printf("Question %d - %s\n", A[i].questionNum , A[i].question);
        }
     
         scanf("%d", &nInput);
        while (A[selectedIndex].questionNum != nInput || strcmp(A[selectedIndex].topic, selectedTopic) != 0)   //take question index in 1d array
            selectedIndex++;
            //UP TO HERE SAME W EDIT !!!
        //at this point, nInput is still = ques num
        printf("Are you sure you want to delete question number %d of %s?\n0 - No\n1 - Yes\n", nInput, selectedTopic);
        scanf("%d", &nInput);
        //if yes and no
        int  j = selectedIndex;
        if (nInput){
            //overwrite data
            //change size
            //change q num
            //loop start from selected index (index of item to delete)

            currQuesNum = A[selectedIndex].questionNum;
            for (int i = selectedIndex + 1; i <s; i++){
                //CHANGE Q NUM OF ITEMS AFTER THE SELECTED
                if (!strcmp(A[selectedIndex].topic, A[i].topic)){
                    A[i].questionNum = currQuesNum;
                    currQuesNum++;
                }
            }
            for (int i = selectedIndex+1; i < s; i++)
                     A[i] = A[i+1]; 
                   
                    s--;
                 
                printf("\n Record deleted successfully!\n\n1 - Delete another record\n2 - Go back to manage data menu\n");
                scanf("%d", &nInput);

             //automatically set the question number:
           
                    //jump edit, not continuous
                    //get index of next elemetn w same topic

            }
           

        }while (nInput == 1);
        return s;
}

void manageFunc (string30 password,  questionFormat A[], int *s, FILE *fp){
    //declare variables
    string30 strInput;
    int nInput = 0;
    int i =0;
    char ch;

    scanf("%c", strInput); // get initial password input
    printf("Enter the password: ");
    gets(strInput);

    while(strcmp(password, strInput)!= 0 && nInput == 0){ //test if password is not the same, nInput = 0 means that user wants to try again
        printf("Incorrect Password\n0 - Try again\n1 - Go back to main menu\n");
        scanf("%d", &nInput);
        if (nInput == 0){
            printf("Enter the password: ");
            gets(strInput);
        }
        gets(strInput);
     }
    if ( nInput == 0){ // if the the nInput remains as 0 (use tried again/ user did not pick to go back)
        do{ //while the user doesnt choose to go back to main menu from manage data menu
            printf("\nMANAGE DATA MENU\n"); // display menu list
            printf("1: Add a record\n");
            printf("2: Edit a record\n");
            printf("3: Delete a record\n");
            printf("4: Import data\n");
            printf("5: Export data\n");
            printf("6: Go back to main menu\n");
            scanf("%d", &nInput);
            while (nInput < 1 || nInput > 6) { //input validation
                printf("Invalid input, try again: ");
                scanf("%d", &nInput);  
            }
   
            switch (nInput) //switch case for user input from manage data
            {
                case 1: *s = addRecord(A, *s);   break; //REMOVE PRINT AFTER, ONLY FOR TTEST printInFile(A, *s, fp);
                case 2:   editRecord(A, *s); break;// to add 2, 3, 5
                case 3: *s = deleteRecord(A, *s); printInFile(A, *s, fp);  break;
                case 4: *s = importData(A, *s, fp); break;
                case 5: exportData(A, *s, fp); break;
            }

        } while (nInput != 6);
    
    }

}


/*PLAY FUNCTIONS/
1. NAME
2. Every turn: choose form topic
3. give random question
4. if correct add score, if not display sorry message
5. ask for another topic again
**have an end game option for every turn
    if end game is selected, display final message showing accumulated score, return to the (play?) menu

*/


void playGame (struct questionFormat *A, int s, time_t timeVar){
    //create array of topics
    string20 topics[s];
    string20 selectedTopic;     
    string150 name;                                //index of the selected question in the array 
   int ctrTopics = 0, exists = 0, arrayTopicsSize = 0, selectedIndex = 0, nInput; //reset variables
    for (int i = 0; i < s; i++){
        for (int j = 0; j < ctrTopics; j++)
            if (!strcmp(A[i].topic, topics[j])) // check if exists na ung topic of current ques in topics array
                exists = 1;
        if (!exists) {//IF WALA PA, ADD TO ARRAY
            strcpy(topics[ctrTopics], A[i].topic); // add to array of topics
            ctrTopics++;

        }

        exists = 0; //reset flag variable
    }//end of atopics array creation
    //ctrTopics = size of topics array

        printf("Select a Topic: \n");
        //display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);
    //TOPICS ARRAY CREATION SAME AS EDIT FUNCTION, CAN MODULARIZE INTO ONE FUNCTION

    //ask for name
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("\nSelect a topic\n");
     
    //display the topics
 


 
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);
        
        do{
            scanf("%d", &nInput); //get the topic
            if (nInput < 1 || nInput > ctrTopics)
                printf("Topic is not in choices!\n");
        }while(nInput < 1 || nInput > ctrTopics);
        


        
       //by this time, hindi na 0 yung input
        strcpy(selectedTopic, topics[nInput-1]); //-1 since index starts at 0, input starts at 1 lowest
    //UNTIL HERE SAME WITH EDIT, except for go back to main menu


    //get last question num in that topic
        //loop through the array of questions, and everytime may question na match, add number
         int lastQuesNum = 0;
            for (int i = 0; i < s; i++) //loop through the array of structs 
           // look for the question with the same topic (as added question) with the highest num 
                if (!strcmp(A[i].topic, selectedTopic) &&  A[i].questionNum > lastQuesNum)
                    lastQuesNum = A[i].questionNum;
                //take the last num and add one to it, set it as the new question num
               // A[s].questionNum = lastQuesNum+1;
               
               //**you now have the last q num
    
    //generate random number within 1 - the last num
    srand( time(&timeVar));
    //generate random odd value from 1-last question num
    int nRandomNum = rand() % (lastQuesNum+1);
    if (nRandomNum == 0)
        nRandomNum++;
    //based on the index inputted, loop through array to get the corresponding question with the same topic ad the random num generated
    int randomQuestionInd, found = 0;
    
    int i = 0;
    while (!found){
        if (!strcmp(A[i].topic, selectedTopic) &&  A[i].questionNum == nRandomNum){ //if the current question in loop ahs same topic as the selected topic
                                                                                    //and its question num is the same as the random number generated, then save its index for later use
             randomQuestionInd= i;
             found = 1;
        }
               
    i++;
    }



//display question
printf("last ques: %d, randNum: %d : %s\n",lastQuesNum, nRandomNum, A[randomQuestionInd].question);


/*

    
    srand( time(&timeVar));
    //generate random odd value from 1-last question num
    int nRandomNum = rand() % lastQuesNum;

    
*/

    /*do{
   

}while (nInput != 0);*/

}

void playFunc (struct questionFormat *A, int s, time_t timeVar){
    int nInput;
    printf("1 - Play Game\n2 - View Scores\n3 - Exit\n");
    scanf("%d", &nInput);
    
    switch (nInput)
    {
    case 1: playGame(A, s, timeVar); break;
    case 2: break;
    
    default:
        break;
    }

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
    time_t timeVar; // initialize time

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
            case 1: manageFunc(password, questions, &size, fp); break;
            case 2: playFunc(questions, size, timeVar); break;
            case 3: break;
        }


    }while (menuChoice!=3);
   
  return 0;
}