#include "functions.h"

//TO CLEAN: IMPORT, EDIT, DELETE, PLAY
//TO ORGANIZE: ALL

//MANAGE
//USELESS FUNC
void 
printInFile (questionFormat *A, int s, FILE *fp)
{
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

void copyCharacter(char str[], int *strInd, char ch){
            str[*strInd] = ch;      // set the value of a character in a string (of array struct element) to ch (where ch is a character read from file)
            *strInd++;              //increment the string index
            str[*strInd] = '\0';    //concatenate null byte
        }
int addRecord( questionFormat *A, int s) //start from index after last element, add question (s - number of existing questions/ records)
{
    //declare variables   
    string150 question;
    string30 answer;
    int exists, nInput, lastQuesNum = 0;
    
    do{
        nInput = 1;
        exists = 0;
        //Ask for question to add
        printf("Enter a question: ");
        gets(question); // excess for newline
        gets(question);

    //ask for answer to the added question
        printf("Enter the answer to the question: ");
        gets(answer);
    
    //loop thru all elements and check if question and answered from user input already exists in array of questions
        for (int i = 0; i < s; i++){
            if (!strcmp(A[i].question, question) && !strcmp(A[i].answer, answer))
                exists = 1;
        }
       
    //if record exists, print message and end function, getting back to manage data
        if (exists == 1) 
        {
            printf("\nRecord already exists!\n"); //notify user that question and answer already exist
            printf("0 - Go back to manage menu\n1 - Try again\n");
            scanf("%d", &nInput);
            //input validation
            while (nInput != 0 && nInput != 1)
            {
                printf("Invalid input, try again: ");
                scanf("%d", &nInput);
            }
        }
        //If the record does not already exist in the array of records/ questions
        else { 
            nInput = 0; 
            // copy the question and answer to structure in array
            strcpy(A[s].question, question);  
            strcpy(A[s].answer, answer); 
            //get the remaining information needed (topic)
            printf("Enter the topic of the question: ");
            gets(A[s].topic);
            printf("Enter choice 1: ");
            gets(A[s].choice1);
            printf("Enter choice 2: ");
            gets(A[s].choice2);
            printf("Enter choice 3: ");
            gets(A[s].choice3);

        //automatically set the question number:
            //last question number has been initialized to 0
            lastQuesNum = 0;

            for (int i = 0; i < s; i++) //loop through the array of structs (questions/records)
            // if the current question in loop has the same topic (as the added question) and a higher question number
                if (!strcmp(A[i].topic, A[s].topic) &&  A[i].questionNum > lastQuesNum) 
                    lastQuesNum = A[i].questionNum;     // set the last question number to question number of current question in loop

            //after getting the last question number,add one to it and set it as the question number of the newly added question
            A[s].questionNum = lastQuesNum+1;

            //increment the size of array (of questions/records)
            s++;

            //print notifying message
            printf("\nRecord added successfully!\n"); 
        }  

    }while (nInput == 1); // loop this until user chooses to go back to manage menu after failure to add or until a record has been addded
    
    return s; //return new array size
}

int importData( questionFormat *questionList, int s, FILE *fp){
    //declare variables
    string30 fileName;
    int pos = 0, strInd =0, arrInd = 0; //CHANGE ARRAY INDEX N SET TO S IF EVER MAM SAYS NA NEED LANG APPEND, NOT REWRITE
    char ch;

    //ask for filename and validate
    printf("Import file name (txt) to import: ");
    scanf("%s", fileName);
    while (fopen(fileName, "r") == NULL)
    {
        printf("Filename does not exist! Try again: ");
        scanf("%s", fileName);
    }

    
    fp = fopen(fileName, "r");

    while (!feof(fp)){ //** position refers to the member of the struct (0-6)
        fscanf(fp, "%c", &ch); //Get the character in the loop (loop through file characters)
        if (ch == '\n') { //if character is newline, check if we are in position 7 (the separation between questions)
            if (pos == 7){
                arrInd++; //if we are in position 7 (the separation between questions)
                pos = 0; //reset position to zero and increment struct array index
            }
            else // if it is any other position than 7
                pos++; //simply increment position
            strInd = 0; // Reset string index for both cases, meaning everytime the program finishes reading one line, reset string index for next
            }
        else{
            switch (pos){
                case 0: copyCharacter (questionList[arrInd].topic, &strInd, ch);
                        break;
                case 1: questionList[arrInd].questionNum = (int)ch - 48;
                        break;
                case 2: copyCharacter (questionList[arrInd].question, &strInd, ch);
                        break;
                case 3: copyCharacter (questionList[arrInd].choice1, &strInd, ch);
                        break;
                case 4: copyCharacter (questionList[arrInd].choice2, &strInd, ch);
                        break;
                case 5: copyCharacter (questionList[arrInd].choice3, &strInd, ch);
                        break;
                case 6: copyCharacter (questionList[arrInd].answer, &strInd, ch);
                        break;
    }
        }
        //topic
        /*
        else if (pos == 0){
            questionList[arrInd].topic[strInd] = ch; 
            strInd++; //increment the string index
            questionList[arrInd].topic[strInd] = '\0'; //add null byte after
        } //The program will keep coming back to this, so long as it does not detect a newline character and we are in position 1, same with the rest
        //number
        else if (pos == 1){  //if we are in the question number line/position
           questionList[arrInd].questionNum = (int)ch - 48; //set the question num (of struct array element) to ch converted to int - 48
        }                                       // 1 was read as '1', meaning if we convert to int it is == 49. Subtracting 48 results to 1.
        //Question
        else if (pos == 2){
            questionList[arrInd].question[strInd] = ch;
            strInd++;
            questionList[arrInd].question[strInd] = '\0';
        }
        //Choice 1
        else if (pos == 3){
            questionList[arrInd].choice1[strInd] = ch;
            strInd++;
            questionList[arrInd].choice1[strInd] = '\0';
        }
        //Choice 2
        else if (pos == 4){
            questionList[arrInd].choice2[strInd] = ch;
            strInd++;
            questionList[arrInd].choice2[strInd] = '\0';
        }
        //Choice 3
         else if (pos == 5){
            questionList[arrInd].choice3[strInd] = ch;
            strInd++;
            questionList[arrInd].choice3[strInd] = '\0';
        }
        //Answer
         else if (pos == 6){
            questionList[arrInd].answer[strInd] = ch;
            strInd++;
            questionList[arrInd].answer[strInd] = '\0';
        }*/

    /* send A[arrInd].answer //this is a string pointer
    copyCharacter (A[arrInd].question, &strInd, ch);

        void copyCharacter(string str[], int *strInd, char ch){
            str[*strInd] = ch;
            *strInd++;
            str[*strInd] = '\0;
        }
    switch (pos){
        case 0: copyCharacter (questionList[arrInd].topic, &strInd, ch);
                break;
        case 1: questionList[arrInd].questionNum = (int)ch - 48;
                 break;
        case 2: copyCharacter (questionList[arrInd].question, &strInd, ch);
                 break;
        case 3: copyCharacter (questionList[arrInd].choice1, &strInd, ch);
                break;
        case 4: copyCharacter (questionList[arrInd].choice2, &strInd, ch);
                break;
        case 5: copyCharacter (questionList[arrInd].choice3, &strInd, ch);
                break;
        case 6: copyCharacter (questionList[arrInd].answer, &strInd, ch);
                break;
    }
    */

    }
    
        fclose(fp); //close file
   
       s=arrInd;
        printInFile(questionList, s, fp);
        printf("\nData imported successfully!\n");
        return s;
}
