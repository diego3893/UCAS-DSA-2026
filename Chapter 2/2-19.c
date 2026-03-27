#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int main(){
    Node *p, *q = NULL, *head = NULL, *dlt_pre = NULL, *dlt_ed = NULL;
    char num[50], c = ' ';
    int Index = 0, x, sign, mink, maxk;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    q = head;
    while(1){
        Index = 0;
        x = 0;
        while((c=getchar())!=' ' && c!='\n'){
            num[Index++] = c;
        }
        if(Index==0 && c=='\n'){
            break;
        }
        if(num[0] == '-'){
            sign = -1;
            for(int i=1; i<Index; ++i){
                x = x*10+(num[i]-'0');
            }
        }else{
            sign = 1;
            for(int i=0; i<Index; ++i){
                x = x*10+(num[i]-'0');
            }
        }
        p = (Node*)malloc(sizeof(Node));
        p->data = x*sign;
        p->next = NULL;
        q->next = p;
        q = p;
        if(c == '\n'){
            break;
        }
    }
    scanf("%d%d", &mink, &maxk);
    p = head->next;
    q = head;
    while(p != NULL){
        if(p->data>mink && dlt_pre==NULL){
            dlt_pre = q;
        }
        if(dlt_pre!=NULL && dlt_ed==NULL && q!=head && q!=dlt_pre){
            free(q);
        }
        if(p->data>=maxk && dlt_ed==NULL){
            dlt_ed = p;
        }
        q = p;
        p = p->next;
    }
    if(dlt_pre!=NULL){
        dlt_pre->next = dlt_ed;
    }
    p = head->next;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    return 0;
}