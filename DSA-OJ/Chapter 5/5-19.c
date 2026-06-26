#include<stdio.h>

int min(int, int);
int max(int, int);

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int arr[n+5][m+5];
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            scanf("%d", &arr[i][j]);
        }
    }
    int minn, maxn;
    // Opt method：save minn for each row while reading the inputs
    // 复杂度为O(n*n*m)，n为行数，m为列数
    for(int i=1; i<=n; ++i){
        minn = 0x7fffffff;
        for(int j=1; j<=m; ++j){
            minn = min(minn, arr[i][j]);
        }
        for(int j=1; j<=m; ++j){
            if(arr[i][j] == minn){
                maxn = -0x7fffffff;
                for(int k=1; k<=n; ++k){
                    maxn = max(maxn, arr[k][j]);
                }
                if(maxn == arr[i][j]){
                    printf("%d ", arr[i][j]);
                }
            }
        }
    }
    return 0;
}

int min(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}