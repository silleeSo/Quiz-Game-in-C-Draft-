#include <stdio.h>
#include <string.h>
void manageData (){

}
void playGame (){

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

    printMenu();
    int menuChoice = 0;
    scanf("%d", menuChoice);
    switch (menuChoice)
    {
    case 1: manageData(); break;
    case 2: playGame(); break;
    case 3: break;
    }
   /* while (menuChoice != 3){
    
    }*/
}