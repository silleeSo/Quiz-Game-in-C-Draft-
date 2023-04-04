#include "functions.c"

int main()
{
    // initialize variables and arrays
    time_t timeVar; 
    questionFormat questionList[100];
    leaderBoardFormat leaderboard[100];
    string30 password = "Prog Pasado";
    int nQuesListSize=0, nMenuChoice = 0, nLeaderboardSize = 0;
    FILE *filePointer;

    do
    {
        printMainMenu();

        //ask for int input w/ validation
        nMenuChoice = getIntInput(1, 3);

        //based on input, open next menu
        switch (nMenuChoice)
        {
            case 1: manageFunc(password, questionList, &nQuesListSize, filePointer); break;
            case 2: playFunc(questionList, nQuesListSize, timeVar, &nLeaderboardSize, leaderboard); break;
            case 3: break;
        }
    } 
    while (nMenuChoice!=3);
   
    return 0;
    
}