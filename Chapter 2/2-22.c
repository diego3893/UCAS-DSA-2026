#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char data;
    struct Node* next;
}Node;

int main(){
    Node *head=NULL, *p, *q = NULL;
    Node *cur, *pre, *next;
    char c;
    int flag = 0;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    q = head;
    while((c=getchar())!='\n' && c!=EOF){
        if(c!=','){
            p = (Node*)malloc(sizeof(Node));
            p->next = NULL;
            p->data = c;
            q->next = p;
            q = p;
        }
    }

    // p = head;
    // while(p->next != NULL){
    //     if(p != head){
    //         printf("%c,", p->data);
    //     }
    //     p = p->next;
    // }
    // printf("%c", p->data);
    
    cur = head->next;
    pre = NULL;
    while(cur != NULL){
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = pre;

    p = head;
    while(p->next != NULL){
        if(p != head){
            printf("%c,", p->data);
        }
        p = p->next;
    }
    if(p != head){
        printf("%c", p->data);
    }
    return 0;
}