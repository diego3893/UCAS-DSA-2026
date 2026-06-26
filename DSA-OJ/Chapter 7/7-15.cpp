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

int main() {
    int n;
    scanf("%d", &n);

    vector<vector<int> > matrix(n, vector<int>(n));
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &matrix[i][j]);
        }
    }

    string op;
    while(cin >> op){
        if(op == "IV"){
            int v;
            scanf("%d", &v);
            matrix.insert(matrix.begin()+v, vector<int>(n, 0));
            n++;
            for(int i=0; i<n; ++i){
                matrix[i].insert(matrix[i].begin()+v, 0);
            }
        }else if(op == "IA"){
            int v, w;
            scanf("%d%d", &v, &w);
            matrix[v][w] = 1;
            matrix[w][v] = 1;
        }else if(op == "DV"){ 
            int v;
            scanf("%d", &v);
            matrix.erase(matrix.begin()+v);
            n--;
            for(int i=0; i<n; ++i){
                matrix[i].erase(matrix[i].begin()+v);
            }
        }else if(op == "DA"){
            int v, w;
            scanf("%d%d", &v, &w);
            matrix[v][w] = 0;
            matrix[w][v] = 0;
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(!j){
                printf("%d", matrix[i][j]);
            }else{
                printf(" %d", matrix[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}