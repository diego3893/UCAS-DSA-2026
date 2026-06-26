#include<stdio.h>

int main(){
    int arr[105];
    int x, flag = 0;
    char num[50], c = ' ';
    int Index = 0, Index_num = 0;
    while(1){
        Index = 0;
        x = 0;
        while((c=getchar())!=' ' && c!='\n'){
            num[Index++] = c;
        }
        for(int i=0; i<Index; ++i){
            x = x*10+(num[i]-'0');
        }
        arr[Index_num++] = x;
        if(c == '\n'){
            break;
        }
    }
    scanf("%d", &x);
    for(int i=0; i<Index_num; ++i){
        if(arr[i]>x && !flag){
            printf("%d ", x);
            flag = 1;
        }
        printf("%d ", arr[i]);
    }
    if(!flag){
        printf("%d ", x);
        flag = 1;
    }
    return 0;
}