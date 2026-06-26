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
    int lc, rc;
    node(int d, int l, int r): data(d), lc(l), rc(r) {}
};
bool check_BST(vector<node>, int);

int main(){
    vector<node> t;
    int data, lc, rc;
    while(scanf("%d%d%d", &data, &lc, &rc) == 3){
        node tmp(data, lc, rc);
        t.push_back(tmp);
    }
    int n = t.size();
    int f[n+5];
    for(int i=0; i<n; ++i){
        f[i] = i;
    }
    for(int i=0; i<n; ++i){
        if(t[i].lc != -1){
            f[t[i].lc] = i;
        }
        if(t[i].rc != -1){
            f[t[i].rc] = i;
        }
    }
    int root;
    for(int i=0; i<n; ++i){
        if(f[i] == i){
            root = i;
            break;
        }
    }
    if(check_BST(t, root)){
        printf("1");
    }else{
        printf("0");
    }
    return 0;
}

bool check_BST(vector<node> t, int idx){
    int l = t[idx].lc, r = t[idx].rc;
    if(l==-1 && r==-1){
        return 1;
    }
    if((l==-1 || (l!=-1 && t[l].data<t[idx].data)) && 
       (r==-1 || (r!=-1 && t[r].data>t[idx].data))){
        if(l != -1){
            if(!check_BST(t, l)){
                return 0;
            }
        }
        if(r != -1){
            if(!check_BST(t, r)){
                return 0;
            }
        }
        return 1;
    }else{
        return 0;
    }
}