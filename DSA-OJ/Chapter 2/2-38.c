#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    int freq;
    int stamp;
    struct Node* prior;
    struct Node* next;
}Node;
Node *head, *p, *q;

void locate(int, int, int);

int main(){
    int n, num, time_stamp = 0;
    head = (Node*)malloc(sizeof(Node));
    head->prior = NULL;
    head->next = NULL;
    q = head;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        scanf("%d", &num);
        p = (Node*)malloc(sizeof(Node));
        p->data = num;
        p->stamp = -1;
        p->freq = 0;
        p->next = NULL;
        p->prior = q;
        q->next = p;
        q = p;
    }
    head->prior = p;
    p->next = head;
    while(scanf("%d", &num) == 1){
        locate(num, n, time_stamp);
        time_stamp++;
    }
    p = head->next;
    while(p != head){
        printf("%d ", p->data);
        p = p->next;
    }
    return 0;
}

void locate(int x, int n, int t) {
    Node *p, *q;

    p = head->next;
    while (p != head) {
        if (p->data == x) {
            p->freq++;
            if(p->stamp == -1){
                p->stamp = t;
            }
        }
        p = p->next;
    }

    for(int i=0; i<n-1; ++i){
        p = head->prior;
        for(int j=0; j<n-1-i; ++j){
            if((p->freq>p->prior->freq || (p->freq==p->prior->freq && p->stamp<p->prior->stamp))
                 && p->prior!=head){
                q = p->prior;
                q->prior->next = p;
                p->prior = q->prior;
                q->prior = p;
                q->next = p->next;
                p->next->prior = q;
                p->next = q;
            }
            p = p->prior;
        }
    }

    return;
}