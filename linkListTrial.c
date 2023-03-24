
#include <stdio.h>

struct node{
    char question[30];
    int number;
    
    struct node* next;
    int tail;
    int head;
};

int main()
{
    struct node* end;
    struct node* start;
    struct node q1;
    struct node q2;
    
    start = &q1;
    
    struct node* i;
    i = &start;
    while(i.tail != 1){
        i = i.next;
    }
    
    q1.next = &q2
    
    struct node q3;
    
    q2.tail = 0;
    q2.next = &q3;
    
    q3.tail = 1;
    end = &q3;
    
    
    
    printf("Hello World");

    return 0;
}
