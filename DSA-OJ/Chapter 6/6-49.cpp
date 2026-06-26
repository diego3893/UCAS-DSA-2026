#include<cstdio>
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
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
    queue<Node> q;
    q.push(tree[root]);
    bool get_null = 0, is_comp_tree = 1;
    while(!q.empty()){
        Node tmp = q.front();
        q.pop();
        if(tmp.lc >= 0){
            q.push(tree[tmp.lc]);
        }else if(tmp.lc == -2){
            Node null;
            null.data = '#';
            null.lc = -1;
            null.rc = -1;
            q.push(null);
        }
        if(tmp.rc >= 0){
            q.push(tree[tmp.rc]);
        }else if(tmp.rc == -2){
            Node null;
            null.data = '#';
            null.lc = -1;
            null.rc = -1;
            q.push(null);
        }
        if(tmp.lc==-1 && tmp.rc==-1){
            get_null = 1;
        }
        if(get_null && !(tmp.lc==-1&&tmp.rc==-1)){
            is_comp_tree = 0;
            break;
        }
    }
    if(is_comp_tree){
        printf("Yes");
    }else{
        printf("No");
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