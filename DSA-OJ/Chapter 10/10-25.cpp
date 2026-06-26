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
    node(int d): data(d), nxt(NULL) {}
};

int main(){
    int n;
    scanf("%d", &n);
    node *head, *p, *q;
    head = new node(0);
    q = head;
    for(int i=0; i<n; ++i){
        int x;
        scanf("%d", &x);
        p = new node(x);
        q->nxt = p;
        q = p;
    }
    if(n == 1){
        printf("%d", head->nxt->data);
        return 0;
    }
    node *cur = head->nxt->nxt;
    node *pre = head->nxt;
    while(cur){
        if(pre->data <= cur->data){
            pre = pre->nxt;
            cur = cur->nxt;
            continue;
        }
        p = head;
        while(p->nxt!=cur && p->nxt->data<cur->data){
            p = p->nxt;
        }
        pre->nxt = cur->nxt; // delete cur
        cur->nxt = p->nxt;
        p->nxt = cur;
        cur = pre->nxt;
    }
    p = head->nxt;
    while(p){
        printf("%d ", p->data);
        p = p->nxt;
    }
    return 0;
}