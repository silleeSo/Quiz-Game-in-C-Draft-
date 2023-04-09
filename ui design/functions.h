#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define LEN1 21
#define LEN2 31
#define LEN3 151
#define SIZE 100
typedef char string20[LEN1];
typedef char string30[LEN2];
typedef char string150[LEN3];

typedef struct 
{
    string150 question;
    string30 choice1;
    string30 choice2;
    string30 choice3;
    string30 answer;
    string20 topic;
    int questionNum;

} questionFormat;
//question 150, answer and choices 30, topic 20
typedef struct {
    string30 name;
    int score;

}leaderBoardFormat;

//1. SELF-DEFINED FUNCTIONS USED IN PROCEEDING FUNCTIONS
void 
catCharacter(char *givenString, int *nIndexStr, char cNewChar);
void
editField(char *fieldName, char *field);
int 
getIntInput(int nLowerBound, int nUpperBound);
void 
editChoice(char *strChoiceName, char *strChoice, char *strAnswer, char *altChoice1, char *altChoice2);
int 
createArrayOfTopics(string20 *topics, questionFormat *questionList, int nNumOfQues);
void 
getPasswordInput(string30 strInput);
int 
getLastQuesNum(questionFormat *questionList, int nNumOfQues, string20 selectedTopic);

//2. FUNCTIONS CALLED IN manageFunc()
int 
addRecord(questionFormat *questionList, int nNumOfQues);
int 
importData(questionFormat *questionList, int nNumOfQues);
void 
exportData(questionFormat *questionList, int nNumOfQues);
void 
editRecord(questionFormat *questionList, int nNumOfQues);
int 
deleteRecord(questionFormat *questionList, int nNumOfQues);

//3. FUNCTIONS CALLED IN playFunc()
int 
playGame(questionFormat *questionList, int nNumOfQues,  int nLeaderboardSize, leaderBoardFormat *leaderboard);
void 
viewScores(int nLeaderboardSize, leaderBoardFormat *leaderboard);
void 
manageFunc(string30 password, questionFormat *questionList, int *nNumOfQues);
void
playFunc ( questionFormat *questionList, int nNumOfQues,  int *nLeaderboardSize, leaderBoardFormat *leaderBoard);
void 
printMainMenu();