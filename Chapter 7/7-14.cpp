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

vector<vector<int> > g;
void init(int);

int main(){
    int n, m;
    string s;
    stringstream ss;
    scanf("%d,%d", &n, &m);
    init(n);
    cin >> s;
    for(int i=0; i<s.length(); ++i){
        if(s[i]==',' || s[i]=='-'){
            s[i] = ' ';
        }
    }
    // cout << s;
    ss.str(s);
    int u, v;
    while(ss >> u){
        ss >> v;
        g[u].push_back(v);
    }
    for(auto& it: g){
        sort(it.begin(), it.end(), greater<int>());
    }

    int skip_zero = 0;
    for(int i=0; i<=n; ++i){
        if(i==0 && g[i].size()==0){
            skip_zero = 1;
            continue;
        }
        if(i==n && skip_zero==0){
            continue;
        }else if(i==n && skip_zero==1){
            printf("\n");
        }
        printf("%d", i);
        for(int j=0; j<g[i].size(); ++j){
            if(!j){
                printf(" %d", g[i][j]);
            }else{
                printf(",%d", g[i][j]);
            }
        }
        if(i!=n-1 && i!=n){
            printf("\n");
        }
    }

    return 0;
}

void init(int n){
    for(int i=0; i<=n; ++i){
        vector<int> tmp;
        g.push_back(tmp);
    }
    return;
}