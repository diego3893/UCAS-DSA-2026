#include<stdio.h>
#include<stdlib.h>

int main(){
    int k, m, ans = 0;
    scanf("%d%d", &k, &m);
    if(m < k-1){
        printf("0");
        return 0;
    }
    if(m == k-1){
        printf("1");
        return 0;
    }
    int *arr = (int*)malloc(k*sizeof(int));
    for(int i=0; i<k; ++i){
        arr[i] = 0;
    }
    arr[k-1] = 1;
    for(int j=0; j<m-k+1; ++j){
        ans = 0;
        for(int i=0; i<k; ++i){
            ans += arr[i];
            if(i<k-1){
                arr[i] = arr[i+1];
            }
            if(i == k-1){
                arr[i] = ans;
            }
        }
    }
    printf("%d", ans);
    free(arr);
    arr = NULL;
    return 0;
}
