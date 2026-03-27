#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char c;
    struct Node *next;
    struct Node *prior;
}Node;

int main(){
    char c;
    Node *head, *p, *q;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    head->prior = NULL;
    q = head;
    while((c=getchar())!='\n' && c!=EOF){
        p = (Node*)malloc(sizeof(Node));
        q->next = p;
        p->next = NULL;
        p->prior = q;
        q = p;
        p->c = c;
    }
    while(p != head){
        printf("%c", p->c);
        p = p->prior;
    }
    return 0;
}