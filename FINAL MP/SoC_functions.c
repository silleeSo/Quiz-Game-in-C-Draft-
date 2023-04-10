#include "SoC_header.h"

//1. SELF-DEFINED FUNCTIONS USED IN PROCEEDING FUNCTIONS

/* catCharacter concatenates a given character to a given string based on a specified index
@param *givenString - character pointer to the first character of the string
@param *nIndexStr - pointer to the string index (used so that whatever changes applied to *nIndexStr reflect in main)
@param cNewChar - the character to concatenate to a string
Pre-condition: *nIndexStr was defined before function call and is not greater than or equal to the max length of the string
*/
void 
catCharacter(char *givenString, int *nIndexStr, char cNewChar)
{
    // set the value of a character in a string (of array struct element) to ch (where ch is a character read from file)
    givenString[*nIndexStr] = cNewChar; 

    // increment the string index
    *nIndexStr += 1;             

     // concatenate null byte     
    givenString[*nIndexStr] = '\0';    
}
/* catCharacter accepts string input from the user, filtering out '\n'
@param *strInput - cthe string to store characters in
@param nMaxLength - maximum length of the given string
Pre-condition: string inputted must be within max length, or string will be truncated
*/
void 
getStrInput(char *strInput, int nMaxLength)
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

/* checkIfQuesExists checks if the newly edited question already previously existed
@param *questionList - list of questions
@param nNumOfQues - number of questions in questionList
@param nSelectedIndex - the index of the newly edited question
@return value of local variable bQuesExists (0 means does not exist, 1 means question exists already)
Pre-condition: newly edited question must be part of questionList and nSelectedIndex is defined
*/
int 
checkIfQuesExists(questionFormat *questionList, int nNumOfQues, int nSelectedIndex)
{
	int i;
    int bQuesExists = 0, bSameQuestion, bNotSelected, bSameAnswer;
    for (i = 0; i < nNumOfQues; i++)
    {
        /*1. the selected question is the same as some question 
          2. the answer of the selected question is the same as well
          3. they do not have the same index*/
        bSameQuestion = (!strcmp(questionList[i].question, questionList[nSelectedIndex].question));
        bSameAnswer = (!strcmp(questionList[i].answer, questionList[nSelectedIndex].answer));
        bNotSelected = (i != nSelectedIndex);

        if (bSameQuestion && bSameAnswer && bNotSelected)
            bQuesExists = 1;
    }
    if (bQuesExists)
	{
        system("CLS");
        printf("\n\n\t\t\t\t\t\tQuestion already exists! Please try again... ");
    }
    return  bQuesExists;
}

/* editField asks the user for the new content of a specified field, stores it, and displays a notifying message
@param *fieldName - the specified field (string/ character pointer)
@param *field - where to store the new content of the field (string/ character pointer)
Pre-condition: *fieldName and *field are both valid
*/
void 
editField(char *fieldName, char *field)
{
    int nMaxLength;
    printf("\n\n\n\t\t\t\t\t\tInput the new content of %s: ", fieldName);
    if (!strcmp(fieldName, "question"))
        nMaxLength = 150;
    else if (!strcmp(fieldName, "topic"))
        nMaxLength = 20;

    //choices
    else
        nMaxLength = 30;
    
    getStrInput(field, nMaxLength);
   
}

/* getIntInput asks the user for an integer input and validates it by using a range of valid inputs
@param nLowerBound - the minimum valid input
@param nUpperBound - the minimum valid input
@returns the valid user input
Pre-condition: nLowerBound and nUpperBound are both defined before this function is called
*/
int 
getIntInput(int nLowerBound, int nUpperBound)
{
    int character;
	int nInput;

    scanf("%d", &nInput);
    while ((int)nInput < nLowerBound || (int)nInput > nUpperBound)
    {
        // Clear the stdin so that program won't keep reading the wrong input ^-^
        while ((character = getchar()) != '\n' && character != EOF);
       
        printf("\n\t\t\t\t\t\tInvalid input, try again: ");
        scanf("%d", &nInput);
    }
    return nInput;
}

/* editChoice edits a question choice after validation. It covers edge cases, such as if the user chooses to edit the choice containing the answer 
@param *strChoiceName - the choice name in the form of a string ("choice 1"/ "choice 2"/ "choice 3")
@param nSelectedIndex - index of the question whose choice is to be edited
@param *questionList - list of questions
@param nNumOfQues - number of questions in questionList
Pre-condition: question answer and choice must be initialized or defined before calling this function
*/
void 
editChoice( char* strChoiceName, int nSelectedIndex, questionFormat *questionList, int nNumOfQues)
{
    
    // declare variable for user input
    int i;
    int nInput;
	int bQuesExists = 1;
    string30 altChoice1;
	string30 altChoice2;
    char *strChoice;

    system("CLS");
    //find choice
    
    if (!strcmp(strChoiceName, "choice 1")) 
    {
        strChoice = questionList[nSelectedIndex].choice1;
        strcpy(altChoice1, questionList[nSelectedIndex].choice2);
        strcpy(altChoice2, questionList[nSelectedIndex].choice3);
    }
    else if (!strcmp(strChoiceName, "choice 2")) 
    {
        strChoice = questionList[nSelectedIndex].choice2;
        strcpy(altChoice1, questionList[nSelectedIndex].choice1);
        strcpy(altChoice2, questionList[nSelectedIndex].choice3);
    }
    else if (!strcmp(strChoiceName, "choice 3")) 
    {
        strChoice = questionList[nSelectedIndex].choice3;
        strcpy(altChoice1, questionList[nSelectedIndex].choice2);
        strcpy(altChoice2, questionList[nSelectedIndex].choice1);
    }
        
    

    // if choice and answer are the same
    if (!strcmp(strChoice, questionList[nSelectedIndex].answer))
    {
        
        // display warning message
        printf("\n\n\n\t\t\t\t\t\tThis choice contains the correct answer. Editing this choice will automatically edit the answer.\n\t\t\t\t\t\tDo you wish to proceed?");
        printf("\n\n\n\t\t\t\t\t\t1 - Proceed\n\t\t\t\t\t\t0 - Cancel\n");
        printf("\t\t\t\t\t\tEnter a number: ");
        nInput = getIntInput(0, 1);
        system("CLS");
        if (nInput)
        {
            // edit answer n choice
            editField(strChoiceName, strChoice);
            while (!strcmp(strChoice, altChoice1) || !strcmp(strChoice, altChoice2))
            {
                system("CLS");
                printf("\n\n\n\t\t\t\t\t\tDuplicate choices are not allowed!\n\t\t\t\t\t\tPlease try again: ");
                getStrInput(strChoice, 30);
            }   
            while (bQuesExists)
            {
                //check if q&a pair already exists
                bQuesExists = 0;
                for (i = 0; i < nNumOfQues; i++)
                    if (!strcmp(questionList[i].question, questionList[nSelectedIndex].question) && i != nSelectedIndex && !strcmp(questionList[i].answer, strChoice))
                        bQuesExists = 1;
               if (bQuesExists)
               {
                    system("CLS");
                    printf("\n\n\n\t\t\t\t\t\tThis question and answer pair already exists!\n\t\t\t\t\t\tPlease try again: ");
                    getStrInput(strChoice, 30);
               }
                
            }   
    

            strcpy(questionList[nSelectedIndex].answer, strChoice);
            system("CLS");
             printf("\n\n\n\t\t\t\t\t\tRecord edited successfully!\n");
            printf("\t\t\t\t\t\tEnter 0 to return... ");
            nInput = getIntInput(0,0);
            system("CLS");
        }
    }
    else
    {
        // if the answer and choice are not the same, just edit the field normally (immediately accept input from user)
        editField(strChoiceName, strChoice);

        //if choice and answer are suddely equal after edit, ask user to edit again
        while (!strcmp(strChoice, questionList[nSelectedIndex].answer))
        {
            system("CLS");
            printf("\n\n\n\t\t\t\t\t\tThis choice can not be the same as the answer of the question!\n\t\t\t\t\t\tPlease try again: ");
            getStrInput(strChoice, 30);
        } 

        //validation for duplicate inputs
        while (!strcmp(strChoice, altChoice1) || !strcmp(strChoice, altChoice2))
        {
            system("CLS");
            printf("\n\n\n\t\t\t\t\t\tDuplicate choices are not allowed!\n\t\t\t\t\t\tPlease try again: ");
            getStrInput(strChoice, 30);
        }
        system("CLS");
        printf("\n\n\n\t\t\t\t\t\tRecord edited successfully!\n\n");
        printf("\t\t\t\t\t\tEnter 0 to return... ");
        nInput = getIntInput(0,0);
        system("CLS");
    }
        
}

/* createArrayOfTopics creates an array of existing topics based on the list of questions passed
@param *topics - the array of topics to populate
@param *questionList - the array of questions
@param nNumOfQues - the number of elements/ questions in questionList array
@returns the new (int)size of topics array 
Pre-condition: question list must be populated
*/
int 
createArrayOfTopics(string20 *topics, questionFormat *questionList, int nNumOfQues)
{
	int i;
	int j;
    // reset variables
    int nCtrTopics = 0;
	int bQuesExists = 0;

    // CREATE AN ARRAY OF EXISTING TOPICS:
    // loop through array of questions
    for (i = 0; i < nNumOfQues; i++)
    {
        // loop through array of existing topics
        for (j = 0; j < nCtrTopics; j++)

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

/* getPasswordInput accepts user input for password field and masks the text using asterisks
@param strInput - string variable where characters will be stored
Pre-condition: not more than excess 2 newlines are scanned before calling this function
*/
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
        else if (nPassInd > 0 && cInput == '\b')
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

/* getLastQuesNum gets the last question number in a specified topic
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@param selectedTopic - the specified topic to search
@returns the last question number in the topic of the newly added question
Pre-condition: question list must be populated, or it will return 0
*/
int 
getLastQuesNum(questionFormat *questionList, int nNumOfQues, string20 selectedTopic)
{
	int i;
    int nLastQuesNum = 0;

    // loop through the array of structs (questions/records)
    for (i = 0; i < nNumOfQues; i++) 

        /*if the current question in loop has the same topic (as the added question) and a higher question number
        Note: nNumOfQues = index of the newly addded question*/
        if (!strcmp(questionList[i].topic, selectedTopic) && questionList[i].questionNum > nLastQuesNum)

            // set the last question number to question number of current question in loop
            nLastQuesNum = questionList[i].questionNum; 

    return nLastQuesNum;
}

/* overwriteRecord overwrites a specific record at a certain index
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@param nSelectedIndex - the index of the record to overwrite
Pre-condition: all parameters need to be accurate or errors might occur
*/
void 
overwriteRecord(questionFormat *questionList, int nNumOfQues, int nSelectedIndex) 
{
	int i;
    int nPrevQuesNum;
     /*Move question numbers to the next question
    Initialize Previous question number to the question number of selected question */
    nPrevQuesNum = questionList[nSelectedIndex].questionNum;

    // loop through question array starting from the question after the selected questioon
    for (i = nSelectedIndex + 1; i < nNumOfQues; i++)
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
    for (i = nSelectedIndex; i < nNumOfQues; i++)
        questionList[i] = questionList[i + 1];
}
/*printEditMessage prints message after successful record edit
Pre-condition: must successfully edit questionList item before calling this function
*/
void 
printEditMessage ()
{
    int nInput;
    system("CLS");
    printf("\n\n\n\t\t\t\t\t\tRecord edited successfully!\n\n");
    printf("\t\t\t\t\t\tEnter 0 to return... ");
    scanf("%d", &nInput);
    while (nInput != 0) 
    {
        system("CLS");
        printf("\n\t\t\t\t\t\tInvalid input, please enter 0: ");
        scanf("%d", &nInput);
    }
}
/*printHoriBorder prints a horizontal border (50 characters long)
Pre-condition: must be used in a table display
*/
void 
printHoriBorder()
{
	int i;
    printf("\t\t\t\t\t\t");
    for(i = 1; i < 50; i++)
        printf("-");
}

/*printTableLine prints a table row with text
Pre-condition: text must be at leadt 17 characters for proper alignment
*/
void 
printTableLine(char *strToPrint)
{
    printf ("\n\t\t\t\t\t\t|\t\t%s\t\t|\n", strToPrint);
    printHoriBorder();
}

//2. FUNCTIONS CALLED IN manageFunc()

/* addRecord asks user to input content for a new question and stores it in question list
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@returns the new number of questions in questionList
Pre-condition: question list must be populated, or it will return 0
*/
int 
addRecord(questionFormat *questionList, int nNumOfQues) 
{
    // declare variables
    string150 question;
    string30 answer;
    string20 questionTopic;
    int i;
    int bExists;
	int nInput;
	int nLastQuesNum = 0;
	int bAnsIsInChoices = 0;
	int bIsDuplicate = 0;

    do
    {
        nInput = 1;
        bExists = 0;
        // Ask for question to add
        printf("\n\n\n\t\t\t\t\t\tEnter a question: ");
        getStrInput(question, 150);

        // ask for answer to the added question
        printf("\t\t\t\t\t\tEnter the answer to the question: ");
        getStrInput(answer, 30);

        // loop thru all elements and check if question and answered from user input already exists in array of questions
        for (i = 0; i < nNumOfQues; i++)
        {
            if (!strcmp(questionList[i].question, question) && !strcmp(questionList[i].answer, answer))
                bExists = 1;
        }

        // if record exists, print message and end function, getting back to manage data
        if (bExists == 1)
        {
            system("CLS");
            printf("\n\t\t\t\t\t\tRecord already exists!\n"); // notify user that question and answer already exist
            printf("\t\t\t\t\t\t0 - Go back to manage menu\n\t\t\t\t\t\t1 - Try again\n");

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
            printf("\t\t\t\t\t\tEnter the topic of the question: ");
            getStrInput(questionList[nNumOfQues].topic, 20);
            
            // loop while answer is not in the choices or there are duplicates
            while (bAnsIsInChoices == 0 || bIsDuplicate == 1 )
            {
                //reset variables
                bAnsIsInChoices = 0;
                bIsDuplicate = 1;
                // ask for input on the choices
                printf("\t\t\t\t\t\tEnter choice 1: ");
                getStrInput(questionList[nNumOfQues].choice1, 30);
                printf("\t\t\t\t\t\tEnter choice 2: ");
                getStrInput(questionList[nNumOfQues].choice2, 30);
                printf("\t\t\t\t\t\tEnter choice 3: ");
                getStrInput(questionList[nNumOfQues].choice3, 30);

                // compare answer with each choice, and if one of them is equal, set flag variable to 1 (it is present)
                if (!strcmp(questionList[nNumOfQues].choice1, questionList[nNumOfQues].answer) ||
                    !strcmp(questionList[nNumOfQues].choice2, questionList[nNumOfQues].answer) ||
                    !strcmp(questionList[nNumOfQues].choice3, questionList[nNumOfQues].answer))
                    bAnsIsInChoices = 1;

                if (strcmp(questionList[nNumOfQues].choice1, questionList[nNumOfQues].choice2) != 0 &&
                strcmp(questionList[nNumOfQues].choice2, questionList[nNumOfQues].choice3) != 0 &&
                strcmp(questionList[nNumOfQues].choice1, questionList[nNumOfQues].choice3) != 0)
                    bIsDuplicate = 0;

                // if the answer is not in choices, display notifying message and continue loop (asking user to re-enter choices)
                if (!bAnsIsInChoices)
                {
                    system("CLS");
                    printf("\n\t\t\t\t\t\tAnswer is not part of choices!\n");
                    printf("\t\t\t\t\t\tPlease re-enter the question choices: \n");
                }
                else if (bIsDuplicate)
                {   
                    system("CLS");
                    printf("\n\t\t\t\t\t\tDuplicate choices are not allowed!\n");
                    printf("\t\t\t\t\t\tPlease re-enter the question choices: \n");
                }
                
            }

            // automatically set the question number by first getting the last question num in the same topic
            strcpy(questionTopic, questionList[nNumOfQues].topic);
            nLastQuesNum = getLastQuesNum(questionList, nNumOfQues, questionTopic);

            // after getting the last question number,add one to it and set it as the question number of the newly added question
            questionList[nNumOfQues].questionNum = nLastQuesNum + 1;

            //update status of isUsed
             questionList[nNumOfQues].isUsed = 0;

            // increment the size of array (of questions/records)
            nNumOfQues++;

            // print notifying message
            printf("\n\t\t\t\t\t\tRecord added successfully!\n");
            printf("\t\t\t\t\t\tEnter 0 to return...");
            nInput = getIntInput(0,0);

        }

    } while (nInput == 1); // loop this until user chooses to go back to manage menu after failure to add or until a record has been addded

    //update status of isused

    return nNumOfQues; // return new array size
}

/* importData imports questions stored in a user-given text file and stores it in questionList
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@param *filePointer - file pointer to the file to import
@returns the new number of questions in questionList
Pre-condition: file to import must be populated or nothing will be imported
*/
int 
importData(questionFormat *questionList, int nNumOfQues)
{

    // declare variables
    string30 fileName;
    string20 questionTopic;
    FILE *filePointer;
    int i;
    int nPosition = 0;
	int strInd = 0; 
	int nArrayInd = nNumOfQues;
	int nInput = 1; // CHANGE ARRAY INDEX N SET TO S IF EVER MAM SAYS NA NEED LANG APPEND, NOT REWRITE
    char cCurrentChar;

    // ask for filename and validate
    printf("\n\n\n\t\t\t\t\t\tImport file name (txt) to import: ");
    getStrInput(fileName, 30);

    // loop while the user inputs and invalid filename and does not choose to return to manage menu
    while (fopen(fileName, "r") == NULL && nInput == 1)
    {
        system("CLS");

        printf("\n\t\t\t\t\t\tFilename does not exist!\n");
        printf("\t\t\t\t\t\t0 - Go back to manage menu\n\t\t\t\t\t\t1 - Try again\n");

         // get int input and validate
        printf("\t\t\t\t\t\tEnter a number: ");
        nInput = getIntInput(0, 1);

        if (nInput)
        {
            system("CLS");
            printf("\n\n\n\t\t\t\t\t\tImport file name (txt) to import: ");
            getStrInput(fileName, 30);
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
                    strcpy(questionTopic, questionList[nArrayInd].topic);
                    questionList[nArrayInd].questionNum = getLastQuesNum(questionList, nArrayInd, questionTopic) + 1;
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
        printf("\n\t\t\t\t\t\tData imported successfully!\n");
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        nInput = getIntInput(0,0);
    }

    //initialize all isUsed to 0
    for(i = 0; i < nArrayInd; i++)
        questionList[i].isUsed = 0;
    
    // return new array size
    // Note: nArrayInd is always incremented one more than the actual last index, which makes it equal to the question list size
    return nArrayInd;
}

/* exportData exports questions stored in questionList to a text file (given by user)
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@param *filePointer - file pointer to the file to export to
Pre-condition: questionList must be populated or nothing will be exported
*/
void 
exportData(questionFormat *questionList, int nNumOfQues)
{
    int nInput;
	int i;
	int j;
	int nNumOfTopics;
    // declare variables
    string30 strFileName;
    string20 arrayOfTopics[nNumOfQues];
    FILE *filePointer;
    if (nNumOfQues == 0)
    {
        printf("\n\t\t\t\t\t\tNo existing records to export!\n");
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        scanf("%d", &nInput);
        while (nInput != 0) 
		{    
            system("CLS");
            printf("\n\t\t\t\t\t\tInvalid input, please enter 0: ");
            scanf("%d", &nInput);
        }
    }
    else
    {
        
        // ask user for filename with extension
        printf("\n\n\n\t\t\t\t\t\tImport file name (txt) to export to: ");
        getStrInput(strFileName, 30);

        // open the file
        filePointer = fopen(strFileName, "w");

        //first create an array of topics
        nNumOfTopics = createArrayOfTopics(arrayOfTopics, questionList, nNumOfQues);
        for (i = 0; i < nNumOfTopics; i++)
		{
            for (j = 0; j < nNumOfQues; j++)
			{
                if (!strcmp(questionList[j].topic, arrayOfTopics[i]))
                {
                    // print out each question (struct) member in this order:
                    fprintf(filePointer, "%s\n", questionList[j].topic);
                    fprintf(filePointer, "%d\n", questionList[j].questionNum);
                    fprintf(filePointer, "%s\n", questionList[j].question);
                    fprintf(filePointer, "%s\n", questionList[j].choice1);
                    fprintf(filePointer, "%s\n", questionList[j].choice2);
                    fprintf(filePointer, "%s\n", questionList[j].choice3);
                    fprintf(filePointer, "%s\n\n", questionList[j].answer);
                }
            }
        }

        // close the file
        fclose(filePointer);
        printf("\n\t\t\t\t\t\tData exported successfully!\n");
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        scanf("%d", &nInput);
        while (nInput != 0) 
		{
            system("CLS");
            printf("\n\t\t\t\t\t\tInvalid input, please enter 0: ");
            scanf("%d", &nInput);
        }
    }
    
}

/* editRecord allsows the user to edit a field in a specific question
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
Pre-condition: questionList must be populated or the function will only display a message
*/
void 
editRecord(questionFormat *questionList, int nNumOfQues)
{
    // create array of topics
    string20 topics[nNumOfQues];
    string20 selectedTopic;
    string30 choice1;
	string30 choice2;
	string30 choice3;                                                         
	int i;
    int ctrTopics;
	int nInput = 1;
	int nSelectedIndex;
	int nLoopCtr = 0;
	int nMinInput = 1;
	int nHighestQuesNum;
	int bQuesExists = 1; 

    system("CLS");

    // if there are no existing records yet for the user to edit, display notifying message and set nInput to zero - meaning go back to menu
    if (nNumOfQues == 0)
    {   
        printf("\n\t\t\t\t\t\tNo existing records to edit!\n");
        printf("\t\t\t\t\t\tEnter 0 to return...");
        nInput = getIntInput(0,0);
    }
    while (nInput != 0)
    {
        // reset the index of selected question
        nSelectedIndex = 0;

        /*CREATE AN ARRAY OF EXISTING TOPICS:
        Note: ctrTopics is equivalent to the size of topics array*/
        ctrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);

        system("CLS");

        //print top border
        printHoriBorder();
 
        printTableLine("- SELECT A TOPIC - ");
        
        // display topics
        for (int i = 0; i < ctrTopics; i++)
        {
            printf("\n\t\t\t\t\t\t\t\t%d - %s\t\t\t\n", i + 1, topics[i]);

            //print border
            printHoriBorder();
        }
        // if one edit has already been made, add new option to go back to manage menu
        if (nLoopCtr > 0)
        {
            printf("\n\t\t\t\t\t\t\t\t0 -  Go back to main menu\n");
            printHoriBorder();

            // 0 can now be a valid user input
            nMinInput = 0;
        }
        printf("\n\t\t\t\t\t\tEnter a number: ");

        /*Get user input w/ Input validation
        Through this method, we can assure that 0 will not be considered a valid output during the first cycle*/

        nInput = getIntInput(nMinInput, ctrTopics);
        // IF USER DID NOT CHOOSE TO EXIT EDIT RECORD
        if (nInput != 0)
        {
            /*define variable selectedTopic based on user input
            Note: -1 since index starts at 0, input starts at 1 lowest*/
            strcpy(selectedTopic, topics[nInput - 1]);

            system("CLS");

            // display questions for the selected topic
            printf("\n\n\n\t\t\t\t\t\tEnter a question number: \n");
            for (i = 0; i < nNumOfQues; i++)
            {
                // check if the selected topic is the same as the topic of the current question in loop
                if (!strcmp(questionList[i].topic, selectedTopic))
                {
                    printf("\t\t\t\t\t\tQuestion %d - %s\n", questionList[i].questionNum, questionList[i].question);
                    nHighestQuesNum = questionList[i].questionNum;
                }
            }

            // accept user input (equivalent to question number) w/ validation
            printf("\n\t\t\t\t\t\tEnter a number: ");
            nInput = getIntInput(1, nHighestQuesNum);

            // loop to get index of selected question
            while (questionList[nSelectedIndex].questionNum != nInput || strcmp(questionList[nSelectedIndex].topic, selectedTopic) != 0)
                nSelectedIndex++;

            system("CLS");
            //print the question data
            printf("\t\t\t\t\t\tTopic: %s\n", questionList[nSelectedIndex].topic);
            printf("\t\t\t\t\t\tQuestion: %s\n", questionList[nSelectedIndex].question);
            printf("\t\t\t\t\t\tChoice 1: %s\n", questionList[nSelectedIndex].choice1);
            printf("\t\t\t\t\t\tChoice 2: %s\n", questionList[nSelectedIndex].choice2);
            printf("\t\t\t\t\t\tChoice 3: %s\n", questionList[nSelectedIndex].choice3);
            printf("\t\t\t\t\t\tAnswer: %s\n\n", questionList[nSelectedIndex].answer);
            //print border
           

            // ask user for the field to edit
            printHoriBorder();
            printf("\n\t\t\t\t\t\t|\tWhich field would you like to edit?\t|\n");
            printHoriBorder();
            printTableLine("1 - Topic         ");
            printTableLine("2 - Question      ");
            printTableLine("3 - Choice 1      ");
            printTableLine("4 - Choice 2      ");
            printTableLine("5 - Choice 3      ");
            printTableLine("6 - Answer        ");

            printf("\n\t\t\t\t\t\tEnter a number: ");
            nInput = getIntInput(1, 6);

            //copy choices to local variable for readability
            strcpy(choice1, questionList[nSelectedIndex].choice1);
            strcpy(choice2, questionList[nSelectedIndex].choice2);
            strcpy(choice3, questionList[nSelectedIndex].choice3);

            system("CLS");

            // based on the user input, ask for new content in specified field
            questionFormat dummyQuestion;
            switch (nInput)
            {
            case 1:      
                //copy into dummy varibales, delete, than paste
                dummyQuestion = questionList[nSelectedIndex];
                overwriteRecord(questionList, nNumOfQues, nSelectedIndex);
                //copy new topic into temp struct var
                editField("topic", dummyQuestion.topic);
                         
                //basically delete the record and then repaste it wwith new topic and number
                dummyQuestion.questionNum = getLastQuesNum(questionList, nNumOfQues, dummyQuestion.topic) + 1;
                questionList[nNumOfQues - 1] = dummyQuestion;
                printEditMessage();
                
                break;

            case 2:
                do
                {
                    editField("question", questionList[nSelectedIndex].question);
                    
                    //check if the question already exists
                    bQuesExists = checkIfQuesExists(questionList, nNumOfQues, nSelectedIndex);    
                } while(bQuesExists);
                printEditMessage();
                break;

            case 3:
                editChoice("choice 1", nSelectedIndex, questionList, nNumOfQues);
                break;
            case 4:
                editChoice("choice 2", nSelectedIndex, questionList, nNumOfQues);
                break;
            case 5:
                editChoice("choice 3", nSelectedIndex, questionList, nNumOfQues);
                break;
            case 6:
                do
                {
                //display choices
                printf("\n\n\t\t\t\t\t\tChoice 1 - %s", questionList[nSelectedIndex].choice1);
                printf("\n\t\t\t\t\t\tChoice 2 - %s", questionList[nSelectedIndex].choice2);
                printf("\n\t\t\t\t\t\tChoice 3 - %s", questionList[nSelectedIndex].choice3);

                //choose from choice
                printf("\n\n\t\t\t\t\t\tEnter a choice number (1-3): ");
                nInput = getIntInput(1, 3);

                //find new correct choice and edit answer
                if (nInput == 1)
                    strcpy(questionList[nSelectedIndex].answer, questionList[nSelectedIndex].choice1);
                else if (nInput == 2)
                    strcpy(questionList[nSelectedIndex].answer, questionList[nSelectedIndex].choice2);
                else if (nInput == 3)
                    strcpy(questionList[nSelectedIndex].answer, questionList[nSelectedIndex].choice3);

                 //check if the question and answer pair already exists
                    bQuesExists = checkIfQuesExists(questionList, nNumOfQues, nSelectedIndex);
                }while (bQuesExists);

                // print message
                printEditMessage();
                 
                break;
            }

            // how many times the user has gone back to edit menu
            nLoopCtr++;
        }
    }
}

/* deleteRecord allows the user to delete a specific question
@param *questionList - the list of questions
@param nNumOfQues - the size or number of question in questionList
@returns the new number of questions in questionList
Pre-condition: questionList must be populated or the function will only display a message
*/
int 
deleteRecord(questionFormat *questionList, int nNumOfQues)
{
    // create array of topics
    string20 topics[nNumOfQues];
    string20 selectedTopic;    
                            
    int i;
    int ctrTopics; 
	int nInput = 1;
	int nSelectedIndex;
	int nHighestQuesNum;

    if (nNumOfQues == 0)
    {
        printf("\n\t\t\t\t\t\tNo existing delete to edit!\n");
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        nInput = getIntInput(0,0);
    }
    while (nInput != 0)
    {   
        system("CLS");

        // reset index of selected question
        nSelectedIndex = 0;

        // create array of topics
        ctrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);    

        //print top border
        printHoriBorder();
        printTableLine("- SELECT A TOPIC - ");
        
        // display topics
        for (int i = 0; i < ctrTopics; i++)
        {
            printf("\n\t\t\t\t\t\t\t\t%d - %s\t\t\t\n", i + 1, topics[i]);

            //print border
            printHoriBorder();
        }
        printf("\n\t\t\t\t\t\t\t\t0 -  Go back to main menu\n");
        printHoriBorder();

        // get user input with validation
        printf("\n\t\t\t\t\t\tEnter a number: ");
        nInput = getIntInput(0, ctrTopics);

        if (nInput != 0 && nNumOfQues != 0)
        {
            /*Define selectedTopic by copying the topic from the topics array
              minus 1 since index starts at 0, input starts at 1 lowest*/
            strcpy(selectedTopic, topics[nInput - 1]);

           
            system("CLS");

            // display questions from the selected topic and get highest question number
            printf("\n\n\n\t\t\t\t\t\tEnter a question number: \n");
            for (i = 0; i < nNumOfQues; i++)
            {
                // check if the selected topic is the same as the topic of the current question in loop
                if (!strcmp(questionList[i].topic, selectedTopic))
                {
                    printf("\t\t\t\t\t\tQuestion %d - %s\n", questionList[i].questionNum, questionList[i].question);
                    nHighestQuesNum = questionList[i].questionNum;
                }
            }
            printf("\n\n\n\t\t\t\t\t\tEnter a question number: ");
            nInput = getIntInput(1, nHighestQuesNum);

            /* GET THE INDEX (IN QUESTIONLIST ARRAY) OF THE SELECTED QUESTION
            while the question number of the current question in loop is not the same as the selected question number
            OR while the topic of the currrent question in loop is not the same as selected topic
            increment nSelectedIndex*/
            while (questionList[nSelectedIndex].questionNum != nInput 
				   || strcmp(questionList[nSelectedIndex].topic, selectedTopic) != 0) // take question index in 1d array
                nSelectedIndex++;
            
			system("CLS");
            // at this point, nInput is still = ques num
            printf("\n\t\t\t\t\t\tAre you sure you want to delete question number %d of %s?\n\t\t\t\t\t\t0 - No\n\t\t\t\t\t\t1 - Yes", nInput, selectedTopic);
            printf("\n\n\n\t\t\t\t\t\tEnter a number: ");
            nInput = getIntInput(0, 1);
            system("CLS");
            // If user selects 1 (yes)
            if (nInput)
            {
                //function
                //overwrite the selected question
               overwriteRecord(questionList, nNumOfQues, nSelectedIndex);

                // subtract question number by one
                nNumOfQues--;

                printf("\n\n\n\t\t\t\t\t\tRecord deleted successfully!\n");
            }
            printf("\n\t\t\t\t\t\t0 - Go back to manage data menu\n\t\t\t\t\t\t1 - Delete another record");
            // get input with validation
            printf("\n\n\n\t\t\t\t\t\tEnter a number: ");
            nInput = getIntInput(0, 1);

            
            system("CLS");
            if (nNumOfQues == 0 && nInput == 1)
            {
                printf("\n\n\n\t\t\t\t\t\tNo more existing records to delete!");
                printf("\n\t\t\t\t\t\tEnter 0 to return... ");
                nInput = getIntInput(0,0);
            }
                
        }
    }
    return nNumOfQues;
}


//3. FUNCTIONS CALLED IN playFunc()

/* playGame allows the user to play the quiz game, answering the questions from questionList
@param *questionList - the list of questions
@param nNumOfQues - the size or number of questions in questionList
@param timeVar - time variable used for randomization
@param nLeaderboardSize - the size or number of entries of leaderboard
@param *leaderboard - pointer to leaderboard array
@returns the new number of questions in questionList
Pre-condition: questionList must be populated or the function will only display a message
*/
void 
playGame(questionFormat *questionList, int nNumOfQues, leaderBoardFormat *roundsLB, leaderBoardFormat *accumulatedLB, int *nRoundsLBSize, int *nAccLBSize)
{
    // declare and define variables
    string20 topics[nNumOfQues];
    string20 selectedTopic;
    time_t timeVar; 
    int i;
    int nCtrTopics = 0;
	int nInput = 1;
	int nCorrectAnswer;
	int nLastQuesNum = 0;
	int nRandQuesInd;
	int accLBInd = -1; // reset variables

    //reset isUsed member of all questions
    for (i = 0; i < nNumOfQues; i++)
        questionList[i].isUsed = 0;

    // get seed from time
    srand(time(&timeVar));
    if (nNumOfQues == 0)
    {
        printf("\n\t\t\t\t\t\tNo existing records to use in game!\n");
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        nInput = getIntInput(0, 0);
        system("CLS");
    }
    if (nInput != 0)
    {
        
        // initialize score for this round as 0
        roundsLB[*nRoundsLBSize].score = 0; 

        // create array of topics
        nCtrTopics = createArrayOfTopics(topics, questionList, nNumOfQues);

        // ask for name and store it to the current leaderboard row
        printf("\n\t\t\t\t\t\tPlease enter your name: ");
        scanf("%s", roundsLB[*nRoundsLBSize].name); 
        

        //get index of name in accumulated
        for(i = 0; i < *nAccLBSize; i++)
        {
            if (!strcmp(roundsLB[*nRoundsLBSize].name, accumulatedLB[i].name))
                accLBInd = i;
        }

        /*if name not found in accumulated, start a new leaderboard record
        Set index to accumulated leader board to size
        Initialize score to 0*/
        if (accLBInd == -1)
		{
            accLBInd = *nAccLBSize;
            accumulatedLB[accLBInd].score = 0;
            //increment accumulated leaderboard size
            *nAccLBSize += 1;
        }
        strcpy(accumulatedLB[accLBInd].name, roundsLB[*nRoundsLBSize].name);
    
        do
        {
            //print top border
            system("CLS");
            printHoriBorder();
            printTableLine("- SELECT A TOPIC - ");
        
            // display topics
            for (i = 0; i < nCtrTopics; i++)
            {
                printf("\n\t\t\t\t\t\t\t\t%d - %s\t\t\t\n", i + 1, topics[i]);
                printHoriBorder();
            }

            // print score
            printf("\n\t\t\t\t\t\t\t\tScore: %d\n", roundsLB[*nRoundsLBSize].score);
            printHoriBorder();
            printTableLine("0 - End the Game ");

            // get input (for which topic) with validation
            printf("\n\t\t\t\t\t\tEnter a number: ");
            nInput = getIntInput(0, nCtrTopics);
            system("CLS");

            //if user inputs a topic (does not end the game)
            if (nInput > 0)
            {
                /*by this time, input is no longer zero
                Note: minus 1 since index starts at 0, input starts at 1 lowest*/
                strcpy(selectedTopic, topics[nInput - 1]);

                //get last question num in that topic
                nLastQuesNum = getLastQuesNum(questionList, nNumOfQues, selectedTopic);

                // reset question list index and flag variable
                int quesInds[nLastQuesNum];
                //size of array of indices
                int nIndexArrSize = 0; 

                //create an array of not yet used questions in the selected topic
                //loop thru questionlist
                for (i = 0; i < nNumOfQues; i++)
				{ 
                    //everytime u hit a question with the same topic and has not been used, add its index to the array of indices
                    if (!strcmp(questionList[i].topic, selectedTopic) && !questionList[i].isUsed)
					{ 
                        quesInds[nIndexArrSize] = i;
                        nIndexArrSize++;
                    }
                } 

                //if array of indices is empty, it means that all questions have been used, display message
                if (nIndexArrSize == 0){
                    system("CLS");
                    printf("\n\t\t\t\t\t\tAll questions in this topic have been used!");
                    printf("\n\t\t\t\t\t\tEnter 1 to return to topics... ");
                    nInput = getIntInput(1, 1);            
                }
               
                if (nIndexArrSize != 0){
                    
                    //generate a random number to access an element in array of indices
                    //nIndexArrSize = the size of array of indices
                    int nRandomNum = rand() % (nIndexArrSize); 

                    //use random num to access element from array of indices, set it to the question index to be used
                    nRandQuesInd = quesInds[nRandomNum];

                    // display question
                    system("CLS");
                    printHoriBorder();
                    printTableLine("Your question is...");
                    printf("\n\t\t\t\t\t\t%s\n", questionList[nRandQuesInd].question);
                    printHoriBorder();

                    // print choices, accept input
                    printf("\n\t\t\t\t\t\t\t\t1 - %s\n", questionList[nRandQuesInd].choice1);
                    printHoriBorder();
                    printf("\n\t\t\t\t\t\t\t\t2 - %s\n", questionList[nRandQuesInd].choice2);
                    printHoriBorder();
                    printf("\n\t\t\t\t\t\t\t\t3 - %s\n", questionList[nRandQuesInd].choice3);
                    printHoriBorder();
                    printf("\n\t\t\t\t\t\t\t\tScore: %d\n", roundsLB[*nRoundsLBSize].score);
                    printHoriBorder();
                    printf("\n\t\t\t\t\t\tEnter a number (1-3): ");
                    nInput = getIntInput(1, 3);
                    system("CLS");

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
                        printf("\n\t\t\t\t\t\tCorrect! (+5 pnts)");
                        // 2. add score
                        roundsLB[*nRoundsLBSize].score += 5;
                        accumulatedLB[accLBInd].score += 5;
                    }
                    else
                        printf("\n\t\t\t\t\t\tSorry! Wrong answer.");

                    // print updated score, give user option to continue or end game
                    printf("\n\n\t\t\t\t\t\tScore: %d\n\n\t\t\t\t\t\t0 - End game\n\t\t\t\t\t\t1 - Next question\n", roundsLB[*nRoundsLBSize].score);
                    printf("\t\t\t\t\t\tEnter a number: ");
                    nInput = getIntInput(0, 1);
                }
                    //update isUsed status
                    questionList[nRandQuesInd].isUsed = 1;
                    // loop until user does not choose to end game
            }
        } while (nInput != 0 );

        // after game ends
        system("CLS");
        printf("\n\t\t\t\t\t\tCONGRATULATIONS, \n\t\t\t\t\t\tYOUR FINAL SCORE FOR THIS ROUND IS: %d\n\n", roundsLB[*nRoundsLBSize].score);
        printf("\n\t\t\t\t\t\tEnter 0 to return... ");
        nInput = getIntInput(0,0);
        system("CLS");

       //increment rounds leaderboard size
       *nRoundsLBSize += 1;
    }

}

/*viewScores prints the leaderboard showing scores from every game played and the leaderboard showing accumulated scores
@param *roundsLB - the leaderboard or list of leaderboard entires in every single different game
@param nRoundsLBSize - the number of leaderboard entries
Pre-condition: leaderboard must be populated or the function will only display message
*/
void 
viewScores( leaderBoardFormat *roundsLB, leaderBoardFormat *accumulatedLB, int nRoundsLBSize, int nAccLBSize)
{
	int i;
	int j;
    int nInput;
	int nMaxInd;
    leaderBoardFormat temp;

    if (nRoundsLBSize == 0)
        printf ("\n\n\t\t\t\t\t\tNo existing entries to display!\n\n");

    else
	{

        //SORT ROUND SCORES LEADERBOARD
        for(i = 0; i < nRoundsLBSize-1; i++)
        {
            nMaxInd = i;
            for(j = i+1 ; j < nRoundsLBSize; j++)
            {
                if (roundsLB[nMaxInd].score < roundsLB[j].score)
                nMaxInd = j;
            }
            if(nMaxInd != i)
            {
                temp = roundsLB[i];
                roundsLB[i] = roundsLB[nMaxInd];
                roundsLB[nMaxInd] = temp;
            }
        }

        //SORT ACCUMULATED LEADERBOARD SCORES
        for(i = 0; i < nAccLBSize-1; i++)
        {
            nMaxInd = i;
            for(j = i+1 ; j < nAccLBSize; j++)
            {
                if (accumulatedLB[nMaxInd].score < accumulatedLB[j].score)
                nMaxInd = j;
            }
            if(nMaxInd != i)
            {
                temp = accumulatedLB[i];
                accumulatedLB[i] = accumulatedLB[nMaxInd];
                accumulatedLB[nMaxInd] = temp;
            }
        }

        //PRINT ACCUMULAATED SCORES
        printHoriBorder();
        printf("\n\t\t\t\t\t\t|\t    - ACCUMULATED SCORES -\t\t|\n");
        printHoriBorder();
        printf("\n\t\t\t\t\t\t\tRow\tPlayer Name\tScore\n");
        printHoriBorder();
        for(i = 0; i < nAccLBSize; i++)
        {
            printf("\n\t\t\t\t\t\t\t%d%17s\t%d\n", i+1, accumulatedLB[i].name, accumulatedLB[i].score );
            printHoriBorder();
        }   
        printf("\n\n");


        //PRINT ROUND SCORES
        printHoriBorder();
        printTableLine("- ROUND SCORES - ");
        printf("\n\t\t\t\t\t\t\tRow\tPlayer Name\tScore\n");
        printHoriBorder();
        for(i = 0; i < nRoundsLBSize; i++)
        {
            printf("\n\t\t\t\t\t\t\t%d%17s\t%d\n", i+1, roundsLB[i].name, roundsLB[i].score );
            printHoriBorder();
        }   
    }
    //get int input with validation
    printf("\n\t\t\t\t\t\tEnter 0 to go back... ");
    scanf("%d", &nInput);
    while (nInput != 0) 
    {  
        system("CLS");
        printf("\n\t\t\t\t\t\tInvalid input, please enter 0: ");
        scanf("%d", &nInput);
    }
    system("CLS");
}

//4. FUNCTIONS CALLED IN MAIN

/* manageFunc displays the manage menu, accepts user input, and calls a corresponding function based on user input
@param password - the correct password
@param *questionList - the list of questions
@param nNumOfQues - the size or number of questions in questionList
@param *filePointer - file pointer to pass in importData() and exportData()
Pre-condition: correct password required before proceeding
*/
void 
manageFunc(string30 password, questionFormat *questionList, int *nNumOfQues)
{
    // declare variables
    int i;
    string30 strInput;
    int nInput = 1;

    system("CLS");
    
    // ask for password input with asterisk masking
    printf("\n\n\n\t\t\t\t\t\tEnter the password: ");
    getPasswordInput(strInput);

    // password validation
    while (strcmp(password, strInput) != 0 && nInput == 1)
    { 
        system("CLS");
        // test if password is not the same, nInput = 0 means that user wants to try again
        printf("\n\n\n\t\t\t\t\t\tIncorrect Password\n\t\t\t\t\t\t0 - Go back to main menu\n\t\t\t\t\t\t1 - Try again\n");
        printf("\t\t\t\t\t\tEnter a number: ");
        nInput = getIntInput(0, 1);

        // if user chose to try again
        if (nInput)
        {
            system("CLS");
            printf("\n\n\n\t\t\t\t\t\tEnter the password: ");
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
            system("CLS");
            printf("\t\t\t\t\t\t");
            for(i = 1; i < 50; i++)
                printf("-");
            printTableLine("MANAGE DATA MENU");
            //printf("\n\nMANAGE DATA MENU\n");
            printTableLine("1: Add a record  ");
            printTableLine("2: Edit a record");
            printTableLine("3: Delete a record");
            printTableLine("4: Import data   ");
            printTableLine("5: Export data   ");
            printTableLine("6: Go back to main menu");
            printf("\n\t\t\t\t\t\tEnter a number: ");

            // get input with validation
            nInput = getIntInput(1, 6);
            system("CLS");
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
                *nNumOfQues = importData(questionList, *nNumOfQues);
                break;
            case 5:
                exportData(questionList, *nNumOfQues);
                break;
            }

        } while (nInput != 6);
    }
}

/* playFunc displays the play menu, accepts user input, and calls a corresponding function based on user input
@param *questionList - the list of questions
@param nNumOfQues - the size or number of questions in questionList
@param timeVar - time variable used for randomization
@param nLeaderboardSize - the size or number of entries of leaderboard
@param *leaderboard - pointer to leaderboard array
Pre-condition: all values passed to parameters must be valid
*/
void 
playFunc ( questionFormat *questionList, int nNumOfQues,  leaderBoardFormat *roundsLB, leaderBoardFormat *accumulatedLB, int *nRoundsLBSize, int *nAccLBSize)
{

    //declare varibales
    int i;
    FILE *fp;
    int nInput;
    
    system("CLS");
    do
    {   
        //open scores file
        fp = fopen("scores.txt", "w");
   
        //update leaderboard everytime player returns to play menu
        for (i = 0; i < *nAccLBSize; i++)
		{
            fprintf(fp, "%s\n", accumulatedLB[i].name);
            fprintf(fp, "%d\n\n", accumulatedLB[i].score);       
        }
        fclose(fp);

        //print header
        printHoriBorder();
        printTableLine("- PLAY MENU -    ");

        //print play menu items
        printTableLine("1 - Play Game    ");
        printTableLine("2 - View Scores  ");
        printTableLine("3 - Exit         ");

        //get input with validation
        printf("\n\t\t\t\t\t\tEnter a number: ");
        nInput = getIntInput(1, 3);
        system("CLS");

       //based on user input, open next menu 
        switch (nInput)
        {
            case 1: playGame(questionList, nNumOfQues, roundsLB, accumulatedLB, nRoundsLBSize, nAccLBSize); 
                    break;
            case 2: viewScores(roundsLB, accumulatedLB, *nRoundsLBSize, *nAccLBSize); 
                    break;
            case 3: break;
        }

    //loop while user does not choose to exit play menu
    }while (nInput!=3);

}

/* printMainMenu prints the main menu
Pre-condition: must only be called in main menu
*/

void printMainMenu()
{
	int i;
    printf("\t\t\t\t\t\t");
    for(i = 1; i < 50; i++)
        printf("-");
   
    printTableLine("- QUIZ GAME -     ");
    printTableLine("1: Manage Data     ");
    printTableLine("2: Play Game     ");
    printTableLine("3: Exit          ");

    printf("\n\t\t\t\t\t\tEnter a number: ");
}