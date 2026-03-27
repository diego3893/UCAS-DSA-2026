#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int main(){
    Node *p, *q;
    Node *ha, *hb, *hc;
    int num, n, m;
    scanf("%d%d", &m, &n);
    p = (Node*)malloc(sizeof(Node));
    ha = p;
    ha->data = -1;
    ha->next = NULL;
    for(int i=0; i<m; ++i){
        q = p;
        p = (Node*)malloc(sizeof(Node));
        q->next = p;
        scanf("%d", &num);
        p->data = num;
        p->next = NULL;
    }
    p = (Node*)malloc(sizeof(Node));
    hb = p;
    hb->data = -1;
    hb->next = NULL;
    for(int i=0; i<n; ++i){
        q = p;
        p = (Node*)malloc(sizeof(Node));
        q->next = p;
        scanf("%d", &num);
        p->data = num;
        p->next = NULL;
    }
    if(m < n){
        hc = ha;
        p = hc;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = hb->next;
    }else{
        hc = hb;
        p = hc;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = ha->next;
    }
    p = hc->next;
    while(p->next != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("%d", p->data);
    return 0;
}