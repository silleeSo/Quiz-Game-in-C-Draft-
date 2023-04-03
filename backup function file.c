#include "functions.h"

//TO CLEAN: IMPORT, EDIT, DELETE, PLAY
//TO ORGANIZE: ALL

//MANAGE

void 
catCharacter(char *strPointer, int *strIndex, char cNewChar){
    strPointer[*strIndex] = cNewChar;      // set the value of a character in a string (of array struct element) to ch (where ch is a character read from file)
    *strIndex += 1;              //increment the string index
    strPointer[*strIndex] = '\0';    //concatenate null byte
}

void 
editField(char *fieldName, char *field){
    printf("%s: ", fieldName);
    gets(field);
    gets(field);
                
}


int 
getIntInput (int nLowerBound, int nUpperBound){
    int character, nInput;
    
    scanf("%d", &nInput);
    while((int)nInput < nLowerBound || (int)nInput > nUpperBound )
    {
        //Clear the stdin so that program won't keep reading the wrong input ^-^
        while((character = getchar())!='\n' &&  character!=EOF); 
        printf("Invalid input, try again: ");
        scanf("%d", &nInput);
    }
 
    
}

int 
addRecord( questionFormat *questionList, int nNumOfQues) //start from index after last element, add question (s - number of existing questions/ records)
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
        for (int i = 0; i < nNumOfQues; i++)
        {
            if (!strcmp(questionList[i].question, question) && !strcmp(questionList[i].answer, answer))
                exists = 1;
        }
       
    //if record exists, print message and end function, getting back to manage data
        if (exists == 1) 
        {
            printf("\nRecord already exists!\n"); //notify user that question and answer already exist
            printf("0 - Go back to manage menu\n1 - Try again\n");
            
            //get input with validation
           nInput= getIntInput(0, 1);
            
        }
        //If the record does not already exist in the array of records/ questions
        else { 
            nInput = 0; 
            // copy the question and answer to structure in array
            strcpy(questionList[nNumOfQues].question, question);  
            strcpy(questionList[nNumOfQues].answer, answer); 
            //get the remaining information needed (topic)
            printf("Enter the topic of the question: ");
            gets(questionList[nNumOfQues].topic);
            printf("Enter choice 1: ");
            gets(questionList[nNumOfQues].choice1);
            printf("Enter choice 2: ");
            gets(questionList[nNumOfQues].choice2);
            printf("Enter choice 3: ");
            gets(questionList[nNumOfQues].choice3);

        //automatically set the question number:
            //last question number has been initialized to 0
            lastQuesNum = 0;

            for (int i = 0; i < nNumOfQues; i++) //loop through the array of structs (questions/records)
            // if the current question in loop has the same topic (as the added question) and a higher question number
                if (!strcmp(questionList[i].topic, questionList[nNumOfQues].topic) &&  questionList[i].questionNum > lastQuesNum) 
                    lastQuesNum = questionList[i].questionNum;     // set the last question number to question number of current question in loop

            //after getting the last question number,add one to it and set it as the question number of the newly added question
            questionList[nNumOfQues].questionNum = lastQuesNum+1;

            //increment the size of array (of questions/records)
            nNumOfQues++;

            //print notifying message
            printf("\nRecord added successfully!\n"); 
        }  

    }while (nInput == 1); // loop this until user chooses to go back to manage menu after failure to add or until a record has been addded
    
    return nNumOfQues; //return new array size
}

int
importData (questionFormat *questionList, FILE *filePointer){

    //declare variables
    string30 fileName;
    int nPosition = 0, strInd =0, nArrayInd = 0, nInput = 1; //CHANGE ARRAY INDEX N SET TO S IF EVER MAM SAYS NA NEED LANG APPEND, NOT REWRITE
    char cCurrentChar;

        //ask for filename and validate    
        printf("Import file name (txt) to import: ");
        scanf("%s", fileName);

        // loop while the user inputs and invalid filename and does not choose to return to manage menu
        while  (fopen(fileName, "r") == NULL && nInput == 1){
             printf("Filename does not exist!\n");
            printf("0 - Go back to manage menu\n1 - Try again\n");
            
            //get int input and validate
            nInput = getIntInput(0, 1);

            if (nInput){
                printf("Import file name (txt) to import: ");
                scanf("%s", fileName);
            }

        }   

    // IF THE USER DID NOT RETURN TO MANAGE MENU
    if (nInput == 1)
    { 
        filePointer = fopen(fileName, "r"); //Open file
        while (!feof(filePointer))
        { 
        //*Note that position (pos) refers to the member of the struct (0-6)

            //Get the character in the loop (loop through file characters)
            fscanf(filePointer, "%c", &cCurrentChar); 
            
            //if character is newline, check if we are in position 7(the separation between questions) or not
            if (cCurrentChar == '\n') 
            { 
                //if we are in position 7 (the separation between questions)
                if (nPosition == 7)
                {   
                    //increment array index, meaning we move on to the next question struct alotted in the array
                    nArrayInd++; 

                    //reset position to zero and increment struct array index
                    nPosition = 0; 
                }

                // if it is any other position than 7
                else 

                    //simply increment position
                    nPosition++; 

                // Reset string index for both cases, meaning everytime the program finishes reading one line, reset string index for next
                strInd = 0; 
            }

            //when the current character in loop is not new line
            else
            {
                switch (nPosition){

                    //concatenate the current character to the topic string
                    //The program will keep coming back to this case, so long as it does not detect a newline character and we are in position 0, same with the rest
                    case 0: catCharacter (questionList[nArrayInd].topic, &strInd, cCurrentChar);    //Topic Line
                            break;

                    //set the question num (of struct array element) to ch converted to int - 48
                    // Note: 1 was read as '1', meaning if we convert to int it is == 49. Subtracting 48 results to 1.
                    case 1: questionList[nArrayInd].questionNum = (int)cCurrentChar - 48;  
                            break;                                            
                    case 2: catCharacter (questionList[nArrayInd].question, &strInd, cCurrentChar); //Question Line
                            break;
                    case 3: catCharacter (questionList[nArrayInd].choice1, &strInd, cCurrentChar);  //Choice 1 Line
                            break;
                    case 4: catCharacter (questionList[nArrayInd].choice2, &strInd, cCurrentChar);  //Choice 2 Line
                            break;
                    case 5: catCharacter (questionList[nArrayInd].choice3, &strInd, cCurrentChar);  //Choice 3 Line
                            break;
                    case 6: catCharacter (questionList[nArrayInd].answer, &strInd, cCurrentChar);   // Answer Line
                            break;
                }
            }
        }

        //close file
        fclose(filePointer); 

        //print notifying message
        printf("\nData imported successfully!\n"); 
    }

    //return new array size
    //Note: nArrayInd is always incremented one more than the actual last index, which makes it equal to the question list size
    return nArrayInd;   

}

void 
exportData( questionFormat *questionList, int nNumOfQues, FILE *filePointer)
{
    //declare variables
    string30 strFileName;

    //ask user for filename with extension
    printf("Import file name (txt) to export to: ");
    scanf("%s", strFileName);

    //open the file
    filePointer = fopen (strFileName, "w");

    for(int i = 0; i < nNumOfQues; i++)
    {
        //print out each question (struct) member in this order:
        fprintf(filePointer, "%s\n", questionList[i].topic); 
        fprintf(filePointer, "%d\n", questionList[i].questionNum);  
        fprintf(filePointer, "%s\n", questionList[i].question);
        fprintf(filePointer, "%s\n", questionList[i].choice1);
        fprintf(filePointer, "%s\n", questionList[i].choice2);
        fprintf(filePointer, "%s\n", questionList[i].choice3);
        fprintf(filePointer, "%s\n\n", questionList[i].answer);
    }
    //close the file
    fclose(filePointer);
    printf("\nData exported successfully!\n");
}

//QUERIES
//if no record paano?? display warning?
//ADD VALIDATION NA PAG INPUT IF ZERO KASO FIRST CYCLE PALANG NAMAN - gud
// ADD VALIDATION IF NO RECORDS TAS U TRY TO EDIT - gud
// the choices
void editRecord( questionFormat *questionList, int nNumOfQues){
    //create array of topics
    string20 topics[nNumOfQues];
    string20 selectedTopic;                                     //index of the selected question in the array 
    int ctrTopics, bQuesExists, nInput, selectedIndex, nLoopCtr = 0, nMinInput = 1, nHighestQuesNum; //counter for topics array
   
    //if there are no existing records yet for the user to edit, display notifying message and set nInput to zero - meaning go back to menu
    if (nNumOfQues == 0)
    {
        printf("No existing records to edit!");
        nInput = 0;
    }
    while (nInput!=0)
    {
        //reset variables
        ctrTopics = 0, bQuesExists = 0, selectedIndex = 0; 

        //CREATE AN ARRAY OF EXISTING TOPICS:
        //loop through array of questions
        for (int i = 0; i < nNumOfQues; i++)
        {
            //loop through array of existing topics
            for (int j = 0; j < ctrTopics; j++)

                //check if the topic current question in loop already exists in the array of topics
                if (!strcmp(questionList[i].topic, topics[j])) 

                    //if it does exist, set bQuesExists to 1 (true)
                    bQuesExists = 1;
            
            //after looping through the array of topics, if it stil doesn't exist, add it to array of topics 
            if (!bQuesExists) 
            {
                strcpy(topics[ctrTopics], questionList[i].topic); 
                ctrTopics++;
            }

            //reset flag variable
            bQuesExists = 0; 
        }

    //Note: ctrTopics is equivalent to the size of topics array
    
        //if one edit has already been made, add new option to go back to manage menu
        if (nLoopCtr > 0)
        {
            printf("0 - Go back to main menu\n");

            //0 can now be a valid user input
            nMinInput = 0;
        }

        printf("Select a Topic: \n");

        //display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);
              
        /*Get user input w/ Input validation
        Through this method, we can assure that 0 will not be considered a valid output during the first cycle*/
        
        nInput = getIntInput(nMinInput, ctrTopics);
        //IF USER DID NOT CHOOSE TO EXIT EDIT RECORD
        if (nInput != 0)
        {
            /*define variable selectedTopic based on user input
            Note: -1 since index starts at 0, input starts at 1 lowest*/
            strcpy(selectedTopic, topics[nInput-1]); 
       
            //display questions for the selected topic
            printf("Enter a question number: \n");
            for (int i = 0; i < nNumOfQues; i++)
            {
                //check if the selected topic is the same as the topic of the current question in loop
                if (!strcmp(questionList[i].topic, selectedTopic))
                {
                    printf("Question %d - %s\n", questionList[i].questionNum , questionList[i].question);
                    nHighestQuesNum = questionList[i].questionNum;
                }                 
            }

            //accept user input (equivalent to question number) w/ validation
           nInput =  getIntInput(1, nHighestQuesNum);

            //loop to get index of selected question
            while (questionList[selectedIndex].questionNum != nInput || strcmp(questionList[selectedIndex].topic, selectedTopic) != 0)
                selectedIndex++; 
        
            //while (nInput != 0)
            //ask user for the field to edit
            printf("Which field would you like to edit?\n1 - Topic\n2 - Question\n3 - choice 1\n4 - choice 2\n5 - choice 3\n6 - answer\n");
           
            nInput= getIntInput(1, 6);
            printf("Input the new content of question %d ", questionList[selectedIndex].questionNum);

            //based on the user input, ask for new content in specified field
            switch (nInput)
            {
                case 1: editField ("topic", questionList[selectedIndex].topic);
                        break;
                case 2: editField ("question", questionList[selectedIndex].question);
                        break;
                case 3: editField ("choice 1", questionList[selectedIndex].choice1);
                        break;
                case 4: editField ("choice 2", questionList[selectedIndex].choice2);
                        break;
                case 5: editField ("choice 3", questionList[selectedIndex].choice3);
                        break;
                case 6: editField ("answer", questionList[selectedIndex].answer);
                        break;
            }
        /*
        if its case 3 4 5
        check if same with answer
        if same with answer, display message
        check user input
        input validation (1 or 0)
        if 1, 
            edit the field of choice
            edit the answer
        if 0, go back to fields display

        if di naman din same w answer ung choice, just edit
        int nInput
        **may var na choiceNum
        if (!strcmp(questionList[selectedIndex].choice1, questionList[selectedIndex].answer)) //if equal ung choice and answer
        {
            printf("\nThis choice contains the correct answer. Editing this choice will automatically edit the answer.\nDo you wish to proceed?");
            printf("\n1 - Proceed\n0 - Cancel");
            nInput = getIntInput (0,1);
            if (nInput){
                //edit answer n choice
               printf("Input the new content of question %d choice %d and answer", questionList[selectedIndex].questionNum, choiceNum);
               gets(questionList[selectedIndex].choice1);
               gets(questionList[selectedIndex].choice1);
               strcpy (questionList[selectedIndex].answer, questionList[selectedIndex].choice1);

            }
            else{
                nInput = 0;
            }
        }
        else
            **edit the field normally
             gets(questionList[selectedIndex].choice1);
               gets(questionList[selectedIndex].choice1);
        
        */
            printf("\nRecord edited successfully!\n\n");
            nLoopCtr ++;
        }
    } 
       
     
}//TO ADD: INPUT VALIDATION FOR EVERY QUESTIO