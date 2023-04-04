#include "functions.h"

// TO CLEAN: IMPORT, EDIT, DELETE, PLAY
// TO ORGANIZE: ALL

// MANAGE

void 
catCharacter(char *strPointer, int *nIndexStr, char cNewChar)
{
    strPointer[*nIndexStr] = cNewChar; // set the value of a character in a string (of array struct element) to ch (where ch is a character read from file)
    *nIndexStr += 1;                   // increment the string index
    strPointer[*nIndexStr] = '\0';     // concatenate null byte
}

void 
editField(char *fieldName, char *field)
{
    printf("Input the new content of %s: ", fieldName);
    gets(field);
    gets(field);
    printf("\nRecord edited successfully!\n\n");
}

int 
getIntInput(int nLowerBound, int nUpperBound)
{
    int character, nInput;

    scanf("%d", &nInput);
    while ((int)nInput < nLowerBound || (int)nInput > nUpperBound)
    {
        // Clear the stdin so that program won't keep reading the wrong input ^-^
        while ((character = getchar()) != '\n' && character != EOF)
            ;
        printf("Invalid input, try again: ");
        scanf("%d", &nInput);
    }
}

void 
editChoice(char *strChoiceName, char *strChoice, char *strAnswer)
{
    // declare variable for user input
    int nInput;

    // if choice and answer are the same
    if (!strcmp(strChoice, strAnswer))
    {
        // display warning message
        printf("\nThis choice contains the correct answer. Editing this choice will automatically edit the answer.\nDo you wish to proceed?");
        printf("\n1 - Proceed\n0 - Cancel\n");
        nInput = getIntInput(0, 1);
        if (nInput)
        {
            // edit answer n choice
            editField(strChoiceName, strChoice);
            strcpy(strAnswer, strChoice);
        }
    }
    else
        // if the answer and choice are not the same, just edit the field normally (immediately accept input from user)
        editField(strChoiceName, strChoice);
}

int 
createArrayOfTopics(string20 *topics, questionFormat *questionList, int nNumOfQues)
{
    // reset variables
    int nCtrTopics = 0, bQuesExists = 0;

    // CREATE AN ARRAY OF EXISTING TOPICS:
    // loop through array of questions
    for (int i = 0; i < nNumOfQues; i++)
    {
        // loop through array of existing topics
        for (int j = 0; j < nCtrTopics; j++)

            // check if the topic current question in loop already exists in the array of topics
            if (!strcmp(questionList[i].topic, topics[j]))

                // if it does exist, set bQuesExists to 1 (true)
                bQuesExists = 1;

        // after looping through the array of topics, if it stil doesn't exist, add it to array of topics
        if (!bQuesExists)
        {
            strcpy(topics[nCtrTopics], questionList[i].topic);
            nCtrTopics++;
        }

        // reset flag variable
        bQuesExists = 0;
    }
    return nCtrTopics;
}

void 
getPasswordInput(string30 strInput)
{

    /*  cInput - character Input
        nPassInd - String index (character is stored into string, position based on this index)*/
    char cInput;
    int nPassInd = 0;

    do
    {
        // get character
        cInput = getch();

        // limits characters to symbols, letters, and numbers
        if (cInput >= 32 && cInput <= 126)
        {
            printf("*");
            strInput[nPassInd] = cInput;
            nPassInd++;
            strInput[nPassInd] = '\0';
        }

        // in case user presses backspace
        else if (nPassInd >= 0 && cInput == '\b')
        {
            // substract password index so that next character input overwrites
            nPassInd--;

            // print backspace
            printf("\b \b");
            strInput[nPassInd] = '\0';
        }

        /*
        1 - minimum strInput length
        30 - max strInput length
        \r -carriange return; moves cursor/print head to the begining of current line
        */
    } while (strlen(strInput) < 1 || (strlen(strInput) <= 30 && cInput != '\r'));
}

int 
addRecord(questionFormat *questionList, int nNumOfQues) // start from index after last element, add question (s - number of existing questions/ records)
{
    // declare variables
    string150 question;
    string30 answer;
    int exists, nInput, lastQuesNum = 0, bAnsIsInChoices = 0;

    do
    {
        nInput = 1;
        exists = 0;
        // Ask for question to add
        printf("Enter a question: ");
        gets(question); // excess for newline
        gets(question);

        // ask for answer to the added question
        printf("Enter the answer to the question: ");
        gets(answer);

        // loop thru all elements and check if question and answered from user input already exists in array of questions
        for (int i = 0; i < nNumOfQues; i++)
        {
            if (!strcmp(questionList[i].question, question) && !strcmp(questionList[i].answer, answer))
                exists = 1;
        }

        // if record exists, print message and end function, getting back to manage data
        if (exists == 1)
        {
            printf("\nRecord already exists!\n"); // notify user that question and answer already exist
            printf("0 - Go back to manage menu\n1 - Try again\n");

            // get input with validation
            nInput = getIntInput(0, 1);
        }
        // If the record does not already exist in the array of records/ questions
        else
        {
            nInput = 0;
            // copy the question and answer to structure in array
            strcpy(questionList[nNumOfQues].question, question);
            strcpy(questionList[nNumOfQues].answer, answer);
            // get the remaining information needed (topic)
            printf("Enter the topic of the question: ");
            gets(questionList[nNumOfQues].topic);

            // loop while answer is not in the choices
            while (bAnsIsInChoices == 0)
            {
                // ask for input on the choices
                printf("Enter choice 1: ");
                gets(questionList[nNumOfQues].choice1);
                printf("Enter choice 2: ");
                gets(questionList[nNumOfQues].choice2);
                printf("Enter choice 3: ");
                gets(questionList[nNumOfQues].choice3);

                // compare answer with each choice, and if one of them is equal, set flag variable to 1 (it is present)
                if (!strcmp(questionList[nNumOfQues].choice1, questionList[nNumOfQues].answer) ||
                    !strcmp(questionList[nNumOfQues].choice2, questionList[nNumOfQues].answer) ||
                    !strcmp(questionList[nNumOfQues].choice3, questionList[nNumOfQues].answer))
                    bAnsIsInChoices = 1;

                // if the answer is not in choices, display notifying message and continue loop (asking user to re-enter choices)
                if (!bAnsIsInChoices)
                {
                    printf("\nAnswer is not part of choices! Please re-enter the question choices\n");
                }
            }

            // automatically set the question number:
            // last question number has been initialized to 0
            lastQuesNum = 0;

            for (int i = 0; i < nNumOfQues; i++) // loop through the array of structs (questions/records)
                // if the current question in loop has the same topic (as the added question) and a higher question number
                if (!strcmp(questionList[i].topic, questionList[nNumOfQues].topic) && questionList[i].questionNum > lastQuesNum)
                    lastQuesNum = questionList[i].questionNum; // set the last question number to question number of current question in loop

            // after getting the last question number,add one to it and set it as the question number of the newly added question
            questionList[nNumOfQues].questionNum = lastQuesNum + 1;

            // increment the size of array (of questions/records)
            nNumOfQues++;

            // print notifying message
            printf("\nRecord added successfully!\n");
        }

    } while (nInput == 1); // loop this until user chooses to go back to manage menu after failure to add or until a record has been addded

    return nNumOfQues; // return new array size
}

int 
importData(questionFormat *questionList, FILE *filePointer)
{

    // declare variables
    string30 fileName;
    int nPosition = 0, strInd = 0, nArrayInd = 0, nInput = 1; // CHANGE ARRAY INDEX N SET TO S IF EVER MAM SAYS NA NEED LANG APPEND, NOT REWRITE
    char cCurrentChar;

    // ask for filename and validate
    printf("Import file name (txt) to import: ");
    scanf("%s", fileName);

    // loop while the user inputs and invalid filename and does not choose to return to manage menu
    while (fopen(fileName, "r") == NULL && nInput == 1)
    {
        printf("Filename does not exist!\n");
        printf("0 - Go back to manage menu\n1 - Try again\n");

        // get int input and validate
        nInput = getIntInput(0, 1);

        if (nInput)
        {
            printf("Import file name (txt) to import: ");
            scanf("%s", fileName);
        }
    }

    // IF THE USER DID NOT RETURN TO MANAGE MENU
    if (nInput == 1)
    {
        filePointer = fopen(fileName, "r"); // Open file
        while (!feof(filePointer))
        {
            //*Note that position (pos) refers to the member of the struct (0-6)

            // Get the character in the loop (loop through file characters)
            fscanf(filePointer, "%c", &cCurrentChar);

            // if character is newline, check if we are in position 7(the separation between questions) or not
            if (cCurrentChar == '\n')
            {
                // if we are in position 7 (the separation between questions)
                if (nPosition == 7)
                {
                    // increment array index, meaning we move on to the next question struct alotted in the array
                    nArrayInd++;

                    // reset position to zero and increment struct array index
                    nPosition = 0;
                }

                // if it is any other position than 7
                else

                    // simply increment position
                    nPosition++;

                // Reset string index for both cases, meaning everytime the program finishes reading one line, reset string index for next
                strInd = 0;
            }

            // when the current character in loop is not new line
            else
            {
                switch (nPosition)
                {

                // concatenate the current character to the topic string
                // The program will keep coming back to this case, so long as it does not detect a newline character and we are in position 0, same with the rest
                case 0:
                    catCharacter(questionList[nArrayInd].topic, &strInd, cCurrentChar); // Topic Line
                    break;

                // set the question num (of struct array element) to ch converted to int - 48
                //  Note: 1 was read as '1', meaning if we convert to int it is == 49. Subtracting 48 results to 1.
                case 1:
                    questionList[nArrayInd].questionNum = (int)cCurrentChar - 48;
                    break;
                case 2:
                    catCharacter(questionList[nArrayInd].question, &strInd, cCurrentChar); // Question Line
                    break;
                case 3:
                    catCharacter(questionList[nArrayInd].choice1, &strInd, cCurrentChar); // Choice 1 Line
                    break;
                case 4:
                    catCharacter(questionList[nArrayInd].choice2, &strInd, cCurrentChar); // Choice 2 Line
                    break;
                case 5:
                    catCharacter(questionList[nArrayInd].choice3, &strInd, cCurrentChar); // Choice 3 Line
                    break;
                case 6:
                    catCharacter(questionList[nArrayInd].answer, &strInd, cCurrentChar); // Answer Line
                    break;
                }
            }
        }

        // close file
        fclose(filePointer);

        // print notifying message
        printf("\nData imported successfully!\n");
    }

    // return new array size
    // Note: nArrayInd is always incremented one more than the actual last index, which makes it equal to the question list size
    return nArrayInd;
}

void 
exportData(questionFormat *questionList, int nNumOfQues, FILE *filePointer)
{
    // declare variables
    string30 strFileName;

    // ask user for filename with extension
    printf("Import file name (txt) to export to: ");
    scanf("%s", strFileName);

    // open the file
    filePointer = fopen(strFileName, "w");

    for (int i = 0; i < nNumOfQues; i++)
    {
        // print out each question (struct) member in this order:
        fprintf(filePointer, "%s\n", questionList[i].topic);
        fprintf(filePointer, "%d\n", questionList[i].questionNum);
        fprintf(filePointer, "%s\n", questionList[i].question);
        fprintf(filePointer, "%s\n", questionList[i].choice1);
        fprintf(filePointer, "%s\n", questionList[i].choice2);
        fprintf(filePointer, "%s\n", questionList[i].choice3);
        fprintf(filePointer, "%s\n\n", questionList[i].answer);
    }
    // close the file
    fclose(filePointer);
    printf("\nData exported successfully!\n");
}

void 
editRecord(questionFormat *questionList, int nNumOfQues)
{
    // create array of topics
    string20 topics[nNumOfQues];
    string20 selectedTopic;                                                              // index of the selected question in the array
    int ctrTopics, nInput, nSelectedIndex, nLoopCtr = 0, nMinInput = 1, nHighestQuesNum; // counter for topics array

    // if there are no existing records yet for the user to edit, display notifying message and set nInput to zero - meaning go back to menu
    if (nNumOfQues == 0)
    {
        printf("\nNo existing records to edit!\n");
        nInput = 0;
    }
    while (nInput != 0)
    {
        // reset the index of selected question
        nSelectedIndex = 0;

        /*CREATE AN ARRAY OF EXISTING TOPICS:
        Note: ctrTopics is equivalent to the size of topics array*/
        ctrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);

        // if one edit has already been made, add new option to go back to manage menu
        if (nLoopCtr > 0)
        {
            printf("0 - Go back to main menu\n");

            // 0 can now be a valid user input
            nMinInput = 0;
        }

        printf("Select a Topic: \n");

        // display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i + 1, topics[i]);

        /*Get user input w/ Input validation
        Through this method, we can assure that 0 will not be considered a valid output during the first cycle*/

        nInput = getIntInput(nMinInput, ctrTopics);
        // IF USER DID NOT CHOOSE TO EXIT EDIT RECORD
        if (nInput != 0)
        {
            /*define variable selectedTopic based on user input
            Note: -1 since index starts at 0, input starts at 1 lowest*/
            strcpy(selectedTopic, topics[nInput - 1]);

            // display questions for the selected topic
            printf("Enter a question number: \n");
            for (int i = 0; i < nNumOfQues; i++)
            {
                // check if the selected topic is the same as the topic of the current question in loop
                if (!strcmp(questionList[i].topic, selectedTopic))
                {
                    printf("Question %d - %s\n", questionList[i].questionNum, questionList[i].question);
                    nHighestQuesNum = questionList[i].questionNum;
                }
            }

            // accept user input (equivalent to question number) w/ validation
            nInput = getIntInput(1, nHighestQuesNum);

            // loop to get index of selected question
            while (questionList[nSelectedIndex].questionNum != nInput || strcmp(questionList[nSelectedIndex].topic, selectedTopic) != 0)
                nSelectedIndex++;

            // ask user for the field to edit
            printf("Which field would you like to edit?\n1 - Topic\n2 - Question\n3 - choice 1\n4 - choice 2\n5 - choice 3\n6 - answer\n");

            nInput = getIntInput(1, 6);

            // based on the user input, ask for new content in specified field
            switch (nInput)
            {
            case 1:
                editField("topic", questionList[nSelectedIndex].topic);
                break;
            case 2:
                editField("question", questionList[nSelectedIndex].question);
                break;
            case 3:
                editChoice("choice 1", questionList[nSelectedIndex].choice1, questionList[nSelectedIndex].answer);
                break;
            case 4:
                editChoice("choice 2", questionList[nSelectedIndex].choice2, questionList[nSelectedIndex].answer);
                break;
            case 5:
                editChoice("choice 3", questionList[nSelectedIndex].choice3, questionList[nSelectedIndex].answer);
                break;
            case 6:
                editField("answer", questionList[nSelectedIndex].answer);
                break;
            }

            // how many times the user has gone back to edit menu
            nLoopCtr++;
        }
    }
}

int 
deleteRecord(questionFormat *questionList, int nNumOfQues)
{
    // create array of topics
    string20 topics[nNumOfQues];
    string20 selectedTopic; // index of the selected question in the array
                            // counter for topics array
    int nPrevQuesNum = 0, ctrTopics, nInput = 1, nSelectedIndex, nHighestQuesNum;

    if (nNumOfQues == 0)
    {
        printf("\nNo existing delete to edit!\n");
        nInput = 0;
    }
    while (nInput != 0)
    {
        // reset index of selected question
        nSelectedIndex = 0;

        // create array of topics
        ctrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);

        printf("0 - Go back to main menu\n");
        printf("Select a Topic: \n");

        // display topics
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i + 1, topics[i]);

        // get user input with validation
        nInput = getIntInput(0, ctrTopics);

        if (nInput != 0)
        {
            /*Define selectedTopic by copying the topic from the topics array
              minus 1 since index starts at 0, input starts at 1 lowest*/
            strcpy(selectedTopic, topics[nInput - 1]);

            // display questions from the selected topic and get highest question number
            printf("Enter a question number: \n");
            for (int i = 0; i < nNumOfQues; i++)
            {
                // check if the selected topic is the same as the topic of the current question in loop
                if (!strcmp(questionList[i].topic, selectedTopic))
                {
                    printf("Question %d - %s\n", questionList[i].questionNum, questionList[i].question);
                    nHighestQuesNum = questionList[i].questionNum;
                }
            }

            nInput = getIntInput(1, nHighestQuesNum);

            /* GET THE INDEX (IN QUESTIONLIST ARRAY) OF THE SELECTED QUESTION
            while the question number of the current question in loop is not the same as the selected question number
            OR while the topic of the currrent question in loop is not the same as selected topic
            increment nSelectedIndex*/
            while (questionList[nSelectedIndex].questionNum != nInput || strcmp(questionList[nSelectedIndex].topic, selectedTopic) != 0) // take question index in 1d array
                nSelectedIndex++;

            // UP TO HERE SAME W EDIT !!!
            // at this point, nInput is still = ques num
            printf("Are you sure you want to delete question number %d of %s?\n0 - No\n1 - Yes\n", nInput, selectedTopic);
            nInput = getIntInput(0, 1);

            // If user selects 1 (yes)
            if (nInput)
            {

                /*Move question numbers to the next question
                Initialize Previous question number to the question number of selected question */
                nPrevQuesNum = questionList[nSelectedIndex].questionNum;

                // loop through question array starting from the question after the selected questioon
                for (int i = nSelectedIndex + 1; i < nNumOfQues; i++)
                {
                    // if the topic of the selected question is equal to the topic of the current question in loop
                    if (!strcmp(questionList[nSelectedIndex].topic, questionList[i].topic))
                    {
                        /*set the question number of the current question in loop TO the previous question number (in the specified topic)
                        then increment nPrevQuesNum*/
                        questionList[i].questionNum = nPrevQuesNum;
                        nPrevQuesNum++;
                    }
                }

                // overwrite the selected question struct by copying next question in the topic TO the current question in the same topic
                for (int i = nSelectedIndex; i < nNumOfQues; i++)
                    questionList[i] = questionList[i + 1];

                // subtract question number by one
                nNumOfQues--;

                printf("\n Record deleted successfully!\n");
            }
            printf("\n0 - Go back to manage data menu\n1 - Delete another record\n");

            // get input with validation
            nInput = getIntInput(0, 1);
        }
    }
    return nNumOfQues;
}

void 
manageFunc(string30 password, questionFormat *questionList, int *nNumOfQues, FILE *filePointer)
{
    // declare variables
    string30 strInput;
    int nInput = 1, i = 0, nPassInd = 0;
    char cInput;

    // for new line
    scanf("%c", strInput);
    printf("Enter the password: ");

    // ask for password input with asterisk masking
    getPasswordInput(strInput);

    // password validation
    while (strcmp(password, strInput) != 0 && nInput == 1)
    { // test if password is not the same, nInput = 0 means that user wants to try again
        printf("\nIncorrect Password\n0 - Go back to main menu\n1 - Try again\n");
        nInput = getIntInput(0, 1);

        // if user chose to try again
        if (nInput)
        {
            printf("Enter the password: ");
            getPasswordInput(strInput);
        }
    }

    // if the the nInput remains as 1 (use tried again/ user did not pick to go back)
    if (nInput)
    {
        do
        {
            /*while the user doesnt choose to go back to main menu from manage data menu
            display menu list*/
            printf("\n\nMANAGE DATA MENU\n");
            printf("1: Add a record\n");
            printf("2: Edit a record\n");
            printf("3: Delete a record\n");
            printf("4: Import data\n");
            printf("5: Export data\n");
            printf("6: Go back to main menu\n");

            // get input with validation
            nInput = getIntInput(1, 6);

            switch (nInput) // switch case for user input from manage data
            {
            case 1:
                *nNumOfQues = addRecord(questionList, *nNumOfQues);
                break; // REMOVE PRINT AFTER, ONLY FOR TTEST printInFile(A, *s, fp);
            case 2:
                editRecord(questionList, *nNumOfQues);
                break; // to add 2, 3, 5
            case 3:
                *nNumOfQues = deleteRecord(questionList, *nNumOfQues);
                break;
            case 4:
                *nNumOfQues = importData(questionList, filePointer);
                break;
            case 5:
                exportData(questionList, *nNumOfQues, filePointer);
                break;
            }

        } while (nInput != 6);
    }
}

int 
playGame(questionFormat *questionList, int nNumOfQues, time_t timeVar, int leaderBoardSize, leaderBoardFormat *leaderBoard)
{
    // declare and define variables
    string20 topics[nNumOfQues];
    string20 selectedTopic;
    int nCtrTopics = 0, nInput, nCorrectAnswer, nLastQuesNum = 0, nRandQuesInd, bIsfound = 0, nQuesIndex = 0; // reset variables

    // initialize score for this round as 0
    leaderBoard[leaderBoardSize].score = 0;

    // get seed from time
    srand(time(&timeVar));

    // create array of topics
    nCtrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);

    // ask for name
    printf("Please enter your name: ");
    scanf("%s", leaderBoard[leaderBoardSize].name); // get name and store it to the current leaderboard row

    do
    {
        printf("\nSelect a topic\n");

        // display the topics
        for (int i = 0; i < nCtrTopics; i++)
            printf("%d - %s\n", i + 1, topics[i]);

        // print score
        printf("Score: %d\n", leaderBoard[leaderBoardSize].score);

        // get input (for which topic) with validation
        nInput = getIntInput(1, nCtrTopics);

        /*by this time, hindi na 0 yung input
        Note: minus 1 since index starts at 0, input starts at 1 lowest*/
        strcpy(selectedTopic, topics[nInput - 1]);

        /*get last question num in that topic
        loop through the array of questions, and everytime there is a question that matches, redefine last question number*/
        for (nQuesIndex = 0; nQuesIndex < nNumOfQues; nQuesIndex++)

            // look for the question with the same topic (as added question) with a higher number
            if (!strcmp(questionList[nQuesIndex].topic, selectedTopic) && questionList[nQuesIndex].questionNum > nLastQuesNum)

                // redefine last question num variable when conditions are passed
                nLastQuesNum = questionList[nQuesIndex].questionNum;

        // generate random odd value from 1 to last question num
        int nRandomNum = rand() % (nLastQuesNum + 1);

        // if random value generated happens to be 0, increment so it becomes 1 (a valid number)
        if (nRandomNum == 0)
            nRandomNum++;

        // reset question list index
        nQuesIndex = 0;

        // based on the index inputted, loop through array to get the corresponding question with the same topic ad the random num generated
        while (!bIsfound)
        {
            /*if the current question in loop has same topic as the selected topic
            and its question num is the same as the random number generated, then save its index for later use
            - Set flag variable to 1 when found*/
            if (!strcmp(questionList[nQuesIndex].topic, selectedTopic) && questionList[nQuesIndex].questionNum == nRandomNum)
            {
                nRandQuesInd = nQuesIndex;
                bIsfound = 1;
            }
            // increment question list index with every loop
            nQuesIndex++;
        }

        // display question
        printf("\nYour question is...\n\n%s\n", questionList[nRandQuesInd].question);

        // print answer, accept input
        printf("1 - %s\n2 - %s\n3 - %s\nAnswer (1-3): ", questionList[nRandQuesInd].choice1, questionList[nRandQuesInd].choice2, questionList[nRandQuesInd].choice3);
        printf("\nScore: %d\n", leaderBoard[leaderBoardSize].score);
        nInput = getIntInput(1, 3);

        // check which choice is supposed to be the right answer
        if (!strcmp(questionList[nRandQuesInd].choice1, questionList[nRandQuesInd].answer))
            nCorrectAnswer = 1;
        else if (!strcmp(questionList[nRandQuesInd].choice2, questionList[nRandQuesInd].answer))
            nCorrectAnswer = 2;
        else
            nCorrectAnswer = 3;

        // if input is the same as the correct answer
        if (nInput == nCorrectAnswer)
        {
            // 1. print
            printf("\nCorrect! (+5 pnts)");
            // 2. add score
            leaderBoard[leaderBoardSize].score += 5;
        }
        else
            printf("\nSorry! Wrong answer.");

        // print updated score, give user option to continue or end game
        printf("\n\nScore: %d\n\n0 - End game\n1 - Next question\n", leaderBoard[leaderBoardSize].score);
        nInput = getIntInput(0, 1);

        // loop until user does not choose to end game
    } while (nInput != 0);

    // after game ends
    printf("\nCONGRATULATIONS, YOUR FINAL SCORE IS: %d\n\n", leaderBoard[leaderBoardSize].score);
    // return incremented leaderboard size
    return leaderBoardSize + 1;
}

void 
viewScores(int nLeaderboardSize, leaderBoardFormat *leaderboard)
{

    //declare variable for user int input
    int nInput;

    //print header
    printf("Row\tPlayer Name\tScore\n");

    //print name and scores
    for(int i = 0; i < nLeaderboardSize; i++)
        printf("%d%+17s\t%d\n", i+1, leaderboard[i].name, leaderboard[i].score );
    
    printf("\nPress 0 to go back: ");

    //get int input with validation
    nInput = getIntInput(0, 0);
}

void 
playFunc ( questionFormat *questionList, int nNumOfQues, time_t timeVar, int *nLeaderboardSize, leaderBoardFormat *leaderBoard){

    //declare varibales
    FILE *fp;
    int nInput;

    do
    {   
        //open scores file
        fp = fopen("scores.txt", "w");
   
        //update leaderboard everytime play is clicked from main menu
        for (int i = 0; i < *nLeaderboardSize; i++){
            fprintf(fp, "%s\n", leaderBoard[i].name);
            fprintf(fp, "%d\n\n", leaderBoard[i].score);       
        }
        fclose(fp);

        //print play menu items
        printf("1 - Play Game\n2 - View Scores\n3 - Exit\n");

        //get input with validation
        nInput = getIntInput(1, 3);

       //based on user input, open next menu 
        switch (nInput)
        {
            case 1: *nLeaderboardSize = playGame(questionList, nNumOfQues, timeVar, *nLeaderboardSize, leaderBoard); 
                    break;
            case 2: viewScores(*nLeaderboardSize, leaderBoard); 
                    break;
            case 3: break;
        }

    //loop while user does not choose to exit play menu
    }while (nInput!=3);

}

void 
printMainMenu()
{
    char cTRCorner = 191, cTLCorner = 218, cBRCorner = 217, cBLCorner = 192, cHorizontalBorder = 196, cVerticalBorder = 179;
    printf("%c", cTLCorner);
    for (int i =0; i <31; i++)
    {
         printf("%c", cHorizontalBorder);
    }
    printf("%c\n", cTRCorner);
    printf ("%c\t1: Manage Data\t\t%c\n", cVerticalBorder, cVerticalBorder);
    printf ("%c\t2: Play Game\t\t%c\n", cVerticalBorder, cVerticalBorder);
    printf ("%c\t3: Exit\t\t\t%c\n", cVerticalBorder, cVerticalBorder);
    printf("%c", cBLCorner);
    for (int i =0; i <31; i++)
    {
         printf("%c", cHorizontalBorder);
    }
    printf("%c\n", cBRCorner);
    
}
