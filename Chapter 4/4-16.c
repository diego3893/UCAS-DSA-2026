#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char c;
    struct Node *next;
}Node;

int main(){
    char c;
    Node *ha, *hb, *p, *q;
    int ans = 0;
    ha = (Node*)malloc(sizeof(Node));
    ha->next = NULL;
    hb = (Node*)malloc(sizeof(Node));
    hb->next = NULL;
    q = ha;
    while((c=getchar()) != ' '){
        p = (Node*)malloc(sizeof(Node));
        p->next = NULL;
        q->next = p;
        q = p;
        p->c = c;
    }
    q = hb;
    while((c=getchar())!='\n' && c!=EOF){
        p = (Node*)malloc(sizeof(Node));
        p->next = NULL;
        q->next = p;
        q = p;
        p->c = c;
    }
    p = ha->next;
    q = hb->next;
    while(p!=NULL && q!=NULL){
        if(p->c == q->c){
            p = p->next;
            q = q->next;
            continue;
        }
        if(p->c > q->c){
            ans = 1;
            break;
        }
        if(p->c < q->c){
            ans = -1;
            break;
        }
    }
    if(ans == 0){
        if(q != NULL){
            ans = -1;
        }
        if(p != NULL){
            ans = 1;
        }
    }
    printf("%d", ans);
    return 0;
}