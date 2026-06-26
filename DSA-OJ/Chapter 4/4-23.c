#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char c;
    struct Node *next;
    struct Node *prior;
}Node;

int main(){
    int n, flag = 1;
    char c;
    scanf("%d", &n);
    getchar();
    Node *head, *p, *q;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    head->prior = NULL;
    q = head;
    for(int i=0; i<n; ++i){
        c = getchar();
        p = (Node*)malloc(sizeof(Node));
        q->next = p;
        p->next = NULL;
        p->prior = q;
        q = p;
        p->c = c;
    }
    p = head->next;
    for(int i=0; i<n/2; ++i){
        if(p->c == q->c){
            p = p->next;
            q = q->prior;
        }else{
            flag = 0;
            break;
        }
    }
    printf("%d", flag);
    return 0;
}