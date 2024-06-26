/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Chrysille Grace So, DLSU ID# 12209589
*********************************************************************************************************/

#include "functions.c"

int main()
{
    // initialize variables and arrays
    
    questionFormat questionList[SIZE];
    leaderBoardFormat roundsLB[SIZE]; 
    leaderBoardFormat accumulatedLB[SIZE];
    string30 password = "china";
    int nQuesListSize = 0, nMenuChoice = 0, nRoundsLBSize = 0, nAccLBSize = 0;

    

    do
    {
        system("CLS");
        printMainMenu();

        //ask for int input w/ validation
        nMenuChoice = getIntInput(1, 3);
        system("CLS");
        //based on input, open next menu
        switch (nMenuChoice)
        {
            case 1: manageFunc(password, questionList, &nQuesListSize); break;
            case 2: playFunc(questionList, nQuesListSize, roundsLB, accumulatedLB, &nRoundsLBSize, &nAccLBSize); break;
            case 3: break;
        }
    } 
    while (nMenuChoice!=3);
   
    return 0;
    
}