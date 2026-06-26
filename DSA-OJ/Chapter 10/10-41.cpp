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

int main(){
    int cnt[10005];
    memset(cnt, 0, sizeof(cnt));
    for(int i=0; i<1000; ++i){
        int x;
        scanf("%d", &x);
        cnt[x]++;
    }
    for(int i=1; i<=10000; ++i){
        while(cnt[i]){
            printf("%d ", i);
            cnt[i]--;
        }
    }
    return 0;
}