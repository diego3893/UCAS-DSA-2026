#include<stdio.h>

typedef struct Node{
    int Index;
    int flag;
}Node;

int main(){
    Node arr[300];
    for(int i=0; i<256; ++i){
        arr[i].flag = 0;
    }
    char c;
    int Index = 0;
    int is_empty = 1;
    while((c=getchar()) != ' '){
        if(!arr[c].flag){
            arr[c].Index = Index;
        }
        arr[c].flag = 1;
        Index++;
    }
    while((c=getchar())!='\n' && c!=EOF){
        arr[c].flag = 0;
    }
    for(int i=0; i<256; ++i){
        if(arr[i].flag == 1){
            printf("%c", i);
            is_empty = 0;
        }
    }
    if(!is_empty){
        printf(" ");
        for(int i=0; i<256; ++i){
            if(arr[i].flag == 1){
                printf("%d", arr[i].Index);
            }
        }
    }else{
        printf("-1");
    }
    return 0;
}