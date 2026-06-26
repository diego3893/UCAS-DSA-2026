#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

struct Edge{
    int v, w;
};

int main(){
    int n, src;
    scanf("%d%d", &n, &src);
    vector<vector<Edge> > g(n+1);
    int dis[n+1];
    int vst[n+1];
    for(int i=1; i<=n; ++i){
        dis[i] = 0x7fffffff;
        vst[i] = 0;
    }
    dis[src] = 0;
    string s;
    int w;
    while(cin >> s >> w){
        int u = s[0]-'0', v = s[2]-'0';
        Edge e = {v, w};
        g[u].push_back(e);
    }
    for(int i=1; i<=n; ++i){
        int u=-1, min_dis = 0x7fffffff;
        for(int j=1; j<=n; ++j){
            if(!vst[j] && dis[j]<min_dis){
                u = j;
                min_dis = dis[j];
            }
        }
        if(u == -1){
            break;
        }
        vst[u] = 1;
        for(int j=0; j<g[u].size(); ++j){
            int v = g[u][j].v;
            int w = g[u][j].w;
            if(!vst[v] && dis[u]+w<dis[v]){
                dis[v] = dis[u]+w;
            }
        }
    }
    for(int i=1; i<=n; ++i){
        if(i == src){
            continue;
        }
        if((i==1 && src!=1) || (src==1 && i==2)){
            printf("%d", dis[i]);
        }else{
            printf(",%d", dis[i]);
        }
    }
    return 0;
}