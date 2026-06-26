#include<stdio.h>

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int arr[n+5][m+5];
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            scanf("%d", &arr[i][j]);
        }
    }
    int first_exp = 0;
    for(int i=n; i>=1; --i){
        for(int j=m; j>=1; --j){
            if(arr[i][j]){
                if(first_exp){
                    printf("+");
                }
                first_exp = 1;
                if(arr[i][j] != 1){
                    if((i-1) && (j-1)){
                        printf("%dxE%dyE%d", arr[i][j], i-1, j-1);
                    }
                    if((i-1) && !(j-1)){
                        printf("%dxE%d", arr[i][j], i-1);
                    }
                    if(!(i-1) && (j-1)){
                        printf("%dyE%d", arr[i][j], j-1);
                    }
                }else{
                    if((i-1) && (j-1)){
                        printf("xE%dyE%d", i-1, j-1);
                    }
                    if((i-1) && !(j-1)){
                        printf("xE%d", i-1);
                    }
                    if(!(i-1) && (j-1)){
                        printf("yE%d", j-1);
                    }
                }
                if(!(i-1) && !(j-1)){
                    printf("%d", arr[i][j]);
                }
            }
        }
    }
    return 0;
}