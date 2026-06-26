#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
using namespace std;

struct node{
    int data;
    node *nxt;
    node(int x) : data(x), nxt(NULL) {}
};

node* merge(node*, node*);

int main(){
    int n;
    scanf("%d", &n);
    node *head = new node(0);
    node *p, *q;
    q = head;
    for(int i=0; i<n; ++i){
        int x;
        scanf("%d", &x);
        p = new node(x);
        q->nxt = p;
        q = p;
    }
    
    queue<node*> que;

    node *cur = head->nxt;
    while(cur){
        node* run_head = cur;
        while(cur->nxt && cur->data <= cur->nxt->data){
            cur = cur->nxt;
        }
        node* next_run = cur->nxt;
        cur->nxt = NULL;
        que.push(run_head);
        cur = next_run;
    }

    while(que.size() > 1){
        node* list1 = que.front();
        que.pop();
        node* list2 = que.front();
        que.pop();
        node* mergedList = merge(list1, list2);
        que.push(mergedList);
    }

    node* result = que.front();
    while(result){
        printf("%d ", result->data);
        result = result->nxt;
    }

    return 0;
}

node* merge(node* l1, node* l2){
    node *head = new node(0);
    node *tail = head;
    
    while(l1 && l2){
        if(l1->data <= l2->data){
            tail->nxt = l1;
            l1 = l1->nxt;
        }else{
            tail->nxt = l2;
            l2 = l2->nxt;
        }
        tail = tail->nxt;
    }
    tail->nxt = (l1) ? l1 : l2;
    return head->nxt;
}