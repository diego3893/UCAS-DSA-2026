#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int ans = 1;
    while(n > 0){
        ans *= n;
        n /= 2;
    }
    printf("%d", ans);
    return 0;
}