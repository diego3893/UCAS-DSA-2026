#include<cstdio>
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<cstring>
using namespace std;

struct Node{
    char data;
    int lc, rc;
};

void merge(int[], vector<Node>);

int main(){
    vector<Node> tree;
    char c;
    int l, r;
    while(cin>>c>>l>>r){
        Node tmp;
        tmp.data = c;
        tmp.lc = l-1;
        tmp.rc = r-1;
        tree.push_back(tmp);
    }
    int f[tree.size()+5];
    for(int i=0; i<tree.size(); ++i){
        f[i] = i;
    }
    merge(f, tree);
    int root = -1;
    for(int i=0; i<tree.size(); ++i){
        if(f[i] == i){
            root = i;
            break;
        }
    }
    stack<Node> s;
    s.push(tree[root]);
    while(!s.empty()){
        Node top = s.top();
        s.pop();
        if(top.rc != -2){
            s.push(tree[top.rc]);
        }
        if(top.lc != -2){
            s.push(tree[top.lc]);
        }
        printf("%c ", top.data);
    }
    return 0;
}

void merge(int f[], vector<Node>t){
    for(int i=0; i<t.size(); ++i){
        if(t[i].lc != -2){
            f[t[i].lc] = f[i];
        }
        if(t[i].rc != -2){
            f[t[i].rc] = f[i];
        }
    }
    return;
}