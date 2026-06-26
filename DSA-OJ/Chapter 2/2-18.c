#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

int main(){
    Node *p, *q = NULL, *head = NULL;
    char num[50], c = ' ';
    int Index = 0, x, dlt, sign;
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
        if(q != NULL){
            q->next = p;
        }
        q = p;
        if(head == NULL){
            head = p;
        }
        if(c == '\n'){
            break;
        }
    }
    scanf("%d", &dlt);

    p = head;
    for(int i=0; p!=NULL; ++i){
        if(dlt!=0 && i==dlt-1){
            q = p->next;
            p->next = p->next->next;
            free(q);
            break;
        }
        if(dlt == 0){
            q = head;
            head = head->next;
            free(q);
            break;
        }
        p = p->next;
    }

    p = head;
    if(p != NULL){
        while(p->next != NULL){
            printf("%d ", p->data);
            p = p->next;
        }
        printf("%d", p->data);
    }else{
        printf("NULL");
    }

    return 0;
}