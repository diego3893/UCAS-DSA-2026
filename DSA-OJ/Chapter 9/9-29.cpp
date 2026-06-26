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
    node* next;
};
int first_output = 1;
void print(int);

int main(){
    node *h, *t, *p, *q = NULL;
    int x;
    string s;
    stringstream ss;
    getline(cin, s);
    ss.str(s);
    while(ss >> x){
        p = new node;
        p->data = x;
        p->next = NULL;
        if(!q){
            h = p;
            q = p;
        }else{
            q->next = p;
            q = p;
        }
    }
    p->next = h;
    t = h;
    s.clear();
    ss.clear();
    getline(cin, s);
    ss.str(s);
    while(ss >> x){
        // printf("%d:\n", x);
        if(t->data == x){
            print(1);
            continue;
        }
        if(t->data < x){
            p = t->next;
            while(p!=h && p->data!=x){
                p = p->next;
            }
            if(p == h){
                print(0);
            }else{
                print(1);
                t = p;
            }
        }
        if(t->data > x){
            p = h;
            while(p->data<x && p->next!=h){
                p = p->next;
            }
            if(p->next != h){
                if(p->data == x){
                    print(1);
                }else{
                    print(0);
                }
            }else{
                p = p->next;
                if(p->data == x){
                    print(1);
                }else{
                    print(0);
                }
            }
        }
    }
    return 0;
}

void print(int num){
    if(first_output){
        printf("%d", num);
        first_output = 0;
    }else{
        printf(" %d", num);
    }
    return;
}