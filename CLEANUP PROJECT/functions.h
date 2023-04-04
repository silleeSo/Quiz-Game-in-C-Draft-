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
    string20 topic;
    int questionNum;
    string150 question;
    string30 choice1;
    string30 choice2;
    string30 choice3;
    string30 answer;

} questionFormat;
//question 150, answer and choices 30, topic 20
typedef struct {
    string30 name;
    int score;

}leaderBoardFormat;


void catCharacter(char *strPointer, int *strIndex, char cNewChar);
int getIntInput (int nLowerBound, int nUpperBound);
void editField(char *fieldName, char *field);
void editChoice(char *strChoiceName, char *strChoice,  char *strAnswer);
int addRecord( questionFormat *questionList, int nNumOfQues);
int importData( questionFormat *questionList, FILE *filePointer);
void exportData( questionFormat *questionList, int nNumOfQues, FILE *filePointer);
void editRecord( questionFormat *questionList, int nNumOfQues);
int deleteRecord( questionFormat *A, int s);
void manageFunc (string30 password,  questionFormat A[], int *s, FILE *fp);
int playGame ( questionFormat *A, int s, time_t timeVar, int leaderBoardSize, leaderBoardFormat *leaderBoard);
void viewScores(int leaderBoardSize, leaderBoardFormat *leaderBoard);
void playFunc ( questionFormat *A, int s, time_t timeVar, int *leaderBoardSize, leaderBoardFormat *leaderBoard);
void printMenu();
