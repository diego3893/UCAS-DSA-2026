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

int max_step;

void dfs(int[], vector<vector<int> >, int, int);

int main(){
    int n;
    scanf("%d", &n);
    vector<vector<int> > g(n+1);
    int vst[n+5];
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
    for(int i=1; i<=n; ++i){
        memset(vst, 0, sizeof(vst));
        vst[i] = 1;
        max_step = -0x7fffffff;
        dfs(vst, g, 0, i);
        if(i == 1){
            printf("%d", max_step);
        }else{
            printf(",%d", max_step);
        }
    }
    return 0;
}

void dfs(int vst[], vector<vector<int> > g, int step, int cur){
    if(step > max_step){
        max_step = step;
    }
    for(int i=0; i<g[cur].size(); ++i){
        if(!vst[g[cur][i]]){
            vst[g[cur][i]] = 1;
            dfs(vst, g, step+1, g[cur][i]);
            vst[g[cur][i]] = 0;
        }
    }
    return;
}