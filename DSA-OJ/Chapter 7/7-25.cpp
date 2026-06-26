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

int topo(vector<vector<int> >, int[], int);

int main(){
    int n;
    scanf("%d", &n);
    getchar();
    vector<vector<int> > g(n+1);
    int indeg[n+5];
    memset(indeg, 0, sizeof(indeg));
    string s;
    getline(cin, s);
    stringstream ss;
    ss.str(s);
    int tmp;
    vector<int> edge_info;
    while(ss >> tmp){
        edge_info.push_back(tmp);
    }
    int fst[n+5], lst[n+5];
    for(int i=0; i<=n; ++i){
        scanf("%d", &fst[i]);
    }
    for(int i=0; i<=n; ++i){
        scanf("%d", &lst[i]);
    }
    for(int i=1; i<=n; ++i){
        if(fst[i] > lst[i]){
            continue;
        }
        for(int j=fst[i]; j<lst[i]; ++j){
            g[i].push_back(edge_info[j]);
            indeg[edge_info[j]]++;
        }
    }
    if(topo(g, indeg, n) == n){
        printf("no");
    }else{
        printf("yes");
    }
    return 0;
}

int topo(vector<vector<int> > g, int indeg[], int n){
    int ans = 0;
    int u;
    int is_indeg_zero;
    do{
        u = -1;
        is_indeg_zero = 0;
        for(int i=1; i<=n; ++i){
            if(indeg[i] == 0){
                indeg[i] = -1;
                u = i;
                is_indeg_zero = 1;
                ans++;
                break;
            }
        }
        if(u != -1){
            for(int i=0; i<g[u].size(); ++i){
                indeg[g[u][i]]--;
            }
        }
    }while(is_indeg_zero);
    return ans;
}