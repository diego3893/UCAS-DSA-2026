#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char data;
    struct Node* next;
}Node;

int main(){
    Node *ha = NULL, *hb = NULL, *p, *q = NULL;
    char c;
    int flag = 0;
    ha = (Node*)malloc(sizeof(Node));
    ha->next = NULL;
    q = ha;
    while((c=getchar()) != '\n'){
        if('a'<=c && c<='z'){
            p = (Node*)malloc(sizeof(Node));
            p->next = NULL;
            p->data = c;
            q->next = p;
            q = p;
        }
    }
    hb = (Node*)malloc(sizeof(Node));
    hb->next = NULL;
    q = hb;
    while((c=getchar())!='\n' && c!=EOF){
        if('a'<=c && c<='z'){
            p = (Node*)malloc(sizeof(Node));
            p->next = NULL;
            p->data = c;
            q->next = p;
            q = p;
        }
    }
    p = ha;
    q = hb;
    while(p->next!=NULL && q->next!=NULL){
        if(p->data > q->data){
            printf("2");
            flag = 1;
            break;
        }
        if(p->data < q->data){
            printf("1");
            flag = 1;
            break;
        }
        p = p->next;
        q = q->next;
    }
    if(!flag){
        if(p->next==NULL && q->next!=NULL){
            printf("1");
        }
        if(p->next!=NULL && q->next==NULL){
            printf("2");
        }
        if(p->next==NULL && q->next==NULL){
            printf("0");
        }
    }
    return 0;
}