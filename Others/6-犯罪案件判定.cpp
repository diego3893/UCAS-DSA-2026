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

int parent_node[2*100000+5];

int find(int);
void merge(int, int);

const string unknown = "不确定";
const string yes = "是同一个团伙所为";
const string no = "不是同一个团伙所为";

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        string ans;
        int N, M;
        scanf("%d%d", &N, &M);
        for(int i=1; i<=2*N; ++i){
            parent_node[i] = i;
        }
        for(int i=0; i<M; ++i){
            //printf("%d %d %d\n", i, T, M);
            char op;
            int a, b;
            cin >> op >> a >> b;
            if(op == 'D'){
                merge(a, b+N);
                merge(b, a+N);
            }else if(op == 'A'){
                if(!ans.empty()){
                    ans += '\n';
                }
                if(find(a) == find(b)){
                    ans += yes;
                }else if(find(a) == find(b + N)){
                    ans += no;
                }else{
                    ans += unknown;
                }
            }
        }
        cout << ans;
    }
    return 0;
}

int find(int x){
    if(parent_node[x] == x){
        return x;
    }
    return parent_node[x] = find(parent_node[x]);
}

void merge(int x, int y){
    int rootX = find(x);
    int rootY = find(y);
    if(rootX != rootY){
        parent_node[rootX] = rootY;
    }
    return;
}