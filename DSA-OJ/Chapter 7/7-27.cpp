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



bool dfs(int[], vector<vector<int> >, int, int, int, int);

int main(){
    int n, k, st, ed;
    scanf("%d,%d", &n, &k);
    scanf("%d,%d", &st, &ed);
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
        g[v].push_back(u);
    }
    vst[st] = 1;
    if(dfs(vst, g, 0, st, k, ed)){
        printf("yes");
    }else{
        printf("no");
    }
    return 0;
}

bool dfs(int vst[], vector<vector<int> > g, int step, int cur, int k, int ed){
    if(cur==ed && step==k){
        return 1;
    }
    for(int i=0; i<g[cur].size(); ++i){
        if(!vst[g[cur][i]]){
            vst[g[cur][i]] = 1;
            if(dfs(vst, g, step+1, g[cur][i], k, ed)){
                return 1;
            }
            vst[g[cur][i]] = 0;
        }
    }
    return 0;
}