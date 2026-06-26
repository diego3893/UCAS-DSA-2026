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
#include<map>
using namespace std;

struct node{
    int nxt[26];
    int cnt;
    node(){
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
    }
};

void trie_insert(vector<node>&, const string&);
int trie_search(const vector<node>&, const string&);
void trie_delete(vector<node>&, const string&);

int main(){
    int op;
    string s;
    vector<node> trie;
    node root;
    trie.push_back(root);
    while(cin >> op >> s){
        if(op == 1){
            trie_insert(trie, s);
        }
        if(op == 3){
            if(trie_search(trie, s)){
                printf("True\n");
            }else{
                printf("False\n");
            }
        }
        if(op == 2){
            trie_delete(trie, s);
        }
    }

    return 0;
}

void trie_insert(vector<node>& trie, const string& s){
    int p = 0;
    int len = s.length();
    for(int i=0; i<len; ++i){
        int u = s[i]-'a';
        if(trie[p].nxt[u] == -1){
            node tmp;
            trie.push_back(tmp);
            trie[p].nxt[u] = trie.size()-1;
        }
        p = trie[p].nxt[u];
    }
    trie[p].cnt++;
    return;
}

int trie_search(const vector<node>& trie, const string& s){
    int p = 0;
    int len = s.length();
    for(int i=0; i<len; ++i){
        int u = s[i]-'a';
        if(trie[p].nxt[u] == -1){
            return 0;
        }
        p = trie[p].nxt[u];
    }
    if(trie[p].cnt > 0){
        return p;
    }else{
        return 0;
    }
}

void trie_delete(vector<node>& trie, const string& s){
    int p = trie_search(trie, s);
    if(!p){
        return;
    }
    trie[p].cnt--;
    return;
}