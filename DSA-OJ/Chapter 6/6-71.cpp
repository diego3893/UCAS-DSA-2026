#include<cstdio>
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<cstring>
using namespace std;

struct Node{
    char data;
    int child, next;
    int depth;
};

void merge(int[], vector<Node>);
vector<Node> get_depth(int, vector<Node>);

int main(){
    vector<Node> tree;
    char c;
    int child, nxt;
    while(cin>>c>>child>>nxt){
        Node tmp;
        tmp.data = c;
        tmp.child = child-1;
        tmp.next = nxt-1;
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
    tree = get_depth(root, tree);
    stack<Node> s;
    s.push(tree[0]);
    while(!s.empty()){
        Node cur = s.top();
        s.pop();
        for(int i=0; i<cur.depth; ++i){
            printf("-");
        }
        printf("%c\n", cur.data);
        if(cur.next != -2){
            s.push(tree[cur.next]);
        }
        if(cur.child != -2){
            s.push(tree[cur.child]);
        }
    }
    
    return 0;
}

void merge(int f[], vector<Node>t){
    for(int i=0; i<t.size(); ++i){
        if(t[i].child != -2){
            f[t[i].child] = f[i];
        }
        if(t[i].next != -2){
            f[t[i].next] = f[i];
        }
    }
    return;
}

vector<Node> get_depth(int root, vector<Node> t){
    stack<Node> s;
    t[root].depth = 0;
    s.push(t[root]);
    while(!s.empty()){
        Node tmp;
        Node cur = s.top();
        s.pop();
        if(cur.child != -2){
            t[cur.child].depth = cur.depth+1;
            tmp = t[cur.child];
            s.push(tmp);
        }
        if(cur.next != -2){
            t[cur.next].depth = cur.depth;
            tmp = t[cur.next];
            s.push(tmp);
        }
    }
    return t;
}