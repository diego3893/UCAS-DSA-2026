#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char data;
    struct Node* next;
}Node;

Node* creat_lklst();

int main(){
    Node *ha, *hb, *hc;
    Node *Index_a, *Index_b, *Index_c, *pre;
    ha = creat_lklst();
    hb = creat_lklst();
    hc = creat_lklst();
    Index_a = ha->next;
    Index_b = hb->next;
    Index_c = hc->next;
    pre = ha;
    
    // Index_a = ha;
    // while(Index_a->next != NULL){
    //     if(Index_a != ha){
    //         printf("%c,", Index_a->data);
    //     }
    //     Index_a = Index_a->next;
    // }
    // if(Index_a != ha){
    //     printf("%c", Index_a->data);
    // }

    while(Index_a != NULL){
        while(Index_b!=NULL && Index_a->data>Index_b->data){
            Index_b = Index_b->next;
        }
        while(Index_c!=NULL && Index_a->data>Index_c->data){
            Index_c = Index_c->next;
        }
        if(Index_c==NULL || Index_b==NULL){
            break;
        }
        if(Index_a->data==Index_b->data && Index_b->data==Index_c->data){
            pre->next = Index_a->next;
            free(Index_a);
            Index_a = pre->next;
        }else{
            pre = Index_a;
            Index_a = Index_a->next;
        }
    }

    Index_a = ha;
    while(Index_a->next != NULL){
        if(Index_a != ha){
            printf("%c,", Index_a->data);
        }
        Index_a = Index_a->next;
    }
    if(Index_a != ha){
        printf("%c", Index_a->data);
    }


    return 0;
}

Node* creat_lklst(){
    char c;
    Node *p, *q, *head;
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
    return head;
}