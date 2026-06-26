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
    node *head, *p, *q;
    head = new node(0);
    q = head;
    int x;
    while(cin >> x){
        p = new node(x);
        q->nxt = p;
        q = p;
    }
    node *pre = head;
    node *min_pre, *min;
    while(pre->nxt){
        q = pre;
    p = q->nxt;
        int min_num = 0x7fffffff;
        while(p){
            if(p->data < min_num){
                min_pre = q;
                min = p;
                min_num = p->data;
            }
            p = p->nxt;
            q = q->nxt;
        }
        min_pre->nxt = min->nxt;
        min->nxt = pre->nxt;
        pre->nxt = min;
        pre = pre->nxt;
    }
    p = head->nxt;
    while(p){
        printf("%d ", p->data);
        p = p->nxt;
    }
    return 0;
}