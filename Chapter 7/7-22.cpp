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

bool dfs(int, int, vector<vector<int> >, int[]);

int main(){
    int n;
    scanf("%d", &n);
    vector<vector<int> > g(n+1);
    int vst[n+5];
    memset(vst, 0, sizeof(vst));
    string s;
    cin >> s;
    for(int i=0; i<s.length(); ++i){
        if(s[i]=='-' || s[i]==','){
            s[i] = ' ';
        }
    }
    stringstream ss;
    ss.str(s);
    int u, v;
    while(ss >> u){
        ss >> v;
        g[u].push_back(v);
    }
    int st, ed;
    scanf("%d,%d", &st, &ed);
    if(dfs(st, ed, g, vst)){
        printf("yes");
    }else{
        printf("no");
    }
    return 0;
}

bool dfs(int st, int ed, vector<vector<int> >g, int vst[]){
    if(st == ed){
        return 1;
    }
    for(int i=0; i<g[st].size(); ++i){
        if(!vst[g[st][i]]){
            vst[g[st][i]] = 1;
            if(dfs(g[st][i], ed, g, vst)){
                return 1;
            }
            vst[g[st][i]] = 0;
        }
    }
    return 0;
}