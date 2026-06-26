#include<stdio.h>

int main(){
    int x0, n, a, ans = 0, p;
    scanf("%d%d", &x0, &n);
    p = x0;
    for(int i=0; i<=n; ++i){
        scanf("%d", &a);
        if(i == 0){
            ans += a;
        }else{
            ans += a*p;
            p *= x0;
        }
    }
    printf("%d", ans);
    return 0;
}