#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    struct Node *next;
    char data;
}Node;

int main(){
    int n;
    char c;
    scanf("%d", &n);
    Node *head, *p, *q, *tail;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    q = head;
    while(n > 0){
        c = getchar();
        if(c!=',' && c!='\n'){
            n--;
            p = (Node*)malloc(sizeof(Node));
            p->data = c;
            p->next = NULL;
            q->next = p;
            q = p;
        }
    }

    tail = p;
    tail->next = head;
    p = head->next;
    while(p->next != head){
        printf("%c,", p->data);
        p = p->next;
    }
    printf("%c", p->data);
    return 0;
}