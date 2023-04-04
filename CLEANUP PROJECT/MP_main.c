

/*  THINGS TO MODULARIzED
    1. make topics array
    2. match question topic and question num to a specific question in array of struct

*/
#include "functions.c"




/*PLAY FUNCTIONS/
1. NAME
2. Every turn: choose form topic
3. give random question
4. if correct add score, if not display sorry message
5. ask for another topic again
**have an end game option for every turn
    if end game is selected, display final message showing accumulated score, return to the (play?) menu

*/


int playGame ( questionFormat *A, int s, time_t timeVar, int leaderBoardSize, leaderBoardFormat *leaderBoard){
    //create array of topics
    string20 topics[s];
    string20 selectedTopic;     
    string150 name;  
    leaderBoard[leaderBoardSize].score = 0;               
    srand( time(&timeVar));
                   //index of the selected question in the array 
   int ctrTopics = 0, exists = 0, arrayTopicsSize = 0, selectedIndex = 0, nInput, correctAnswer; //reset variables
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
     //ask for name
    printf("Please enter your name: ");
    scanf("%s", leaderBoard[leaderBoardSize].name); //get name and store it to the current leaderboard row
    
do{
       
    //TOPICS ARRAY CREATION SAME AS EDIT FUNCTION, CAN MODULARIZE INTO ONE FUNCTION

   
    printf("\nSelect a topic\n");
     
    //display the topics 
        for (int i = 0; i < ctrTopics; i++)
            printf("%d - %s\n", i+1, topics[i]);

         printf("Score: %d\n", leaderBoard[leaderBoardSize].score);//print score
         //get input
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
            for (int j = 0; j < s; j++) //loop through the array of structs 
           // look for the question with the same topic (as added question) with the highest num 
                if (!strcmp(A[j].topic, selectedTopic) &&  A[j].questionNum > lastQuesNum)
                    lastQuesNum = A[j].questionNum;
                //take the last num and add one to it, set it as the new question num
               // A[s].questionNum = lastQuesNum+1;
               
               //**you now have the last q num
    
    //generate random number within 1 - the last num
    
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
printf("\nYour question is...\n\n%s\n", A[randomQuestionInd].question);
//print answer, accept
printf("1 - %s\n2 - %s\n3 - %s\nAnswer (1-3): ", A[randomQuestionInd].choice1,  A[randomQuestionInd].choice2,  A[randomQuestionInd].choice3);
printf("\nScore: %d\n", leaderBoard[leaderBoardSize].score);
scanf("%d", &nInput);
while (nInput < 1 || nInput > 3){
    printf("Invalid Input, try again: ");
    scanf("%d", &nInput);
}

// check which choice is supposed to be the right answer
if (!strcmp(A[randomQuestionInd].choice1, A[randomQuestionInd].answer))
    correctAnswer = 1;
else if (!strcmp(A[randomQuestionInd].choice2, A[randomQuestionInd].answer))
    correctAnswer = 2;
else
    correctAnswer = 3;

//if input is the same as the correct answer
if (nInput == correctAnswer){
    //1. print
    printf("\nCorrect! (+5 pnts)");
    //2. add score
    leaderBoard[leaderBoardSize].score += 5;
   
    //3. update leaderboard
    //4. ask if want to end game
    
}
else
    printf("\nSorry! Wrong answer.");

//give user option to continue or end game
printf("\n\nScore: %d\n\n1 - Next question\n0 - End game\n", leaderBoard[leaderBoardSize].score);
scanf("%d", &nInput);
}while (nInput != 0);

printf("\nCONGRATULATIONS, YOUR FINAL SCORE IS: %d\n\n", leaderBoard[leaderBoardSize].score);

//printf("leader board size: %d\n", leaderBoardSize);   TESTER
return leaderBoardSize + 1; //return incremented leaderboard size
 
}

void viewScores(int leaderBoardSize, leaderBoardFormat *leaderBoard){
    int nInput;
    printf("Row\tPlayer Name\tScore\n");
    for(int i = 0; i < leaderBoardSize; i++)
        printf("%d%+17s\t%d\n", i+1, leaderBoard[i].name, leaderBoard[i].score );
    printf("\nPress 0 to go back: ");
    scanf("%d", &nInput);
    while (nInput!=0){
        printf("Invalid Input\n");
        scanf("%d", &nInput);
    }
}
void playFunc ( questionFormat *A, int s, time_t timeVar, int *leaderBoardSize, leaderBoardFormat *leaderBoard){
    FILE *fp;
    int nInput;
    do{
    fp = fopen("scores.txt", "w");
   
    //printf("leader board size: %d\n", *leaderBoardSize);  TESTER
    for (int i = 0; i < *leaderBoardSize; i++){
        fprintf(fp, "%s\n", leaderBoard[i].name);
        fprintf(fp, "%d\n\n", leaderBoard[i].score);       
    }
    fclose(fp);
    
    printf("1 - Play Game\n2 - View Scores\n3 - Exit\n");
    scanf("%d", &nInput);
    while (nInput < 1 || nInput > 3){
        printf("Invalid Input, try again: ");
        scanf("%d", &nInput);
    }

    
    switch (nInput)
    {
    case 1: *leaderBoardSize = playGame(A, s, timeVar, *leaderBoardSize, leaderBoard); break;
    case 2: viewScores(*leaderBoardSize, leaderBoard); break;
    
    case 3:
        break;
    }
    }while (nInput!=3);

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
    leaderBoardFormat leaderBoard[100];
    string30 password = "Mam quatro po";
    int size=0;
    int menuChoice = 0, leaderBoardSize = 0;
    FILE *fp;
    do{
        printMenu();
    
        scanf("%d", &menuChoice);
        switch (menuChoice)
        {
            case 1: manageFunc(password, questions, &size, fp); break;
            case 2: playFunc(questions, size, timeVar, &leaderBoardSize, leaderBoard); break;
            case 3: break;
        }


    }while (menuChoice!=3);
   
  return 0;
}