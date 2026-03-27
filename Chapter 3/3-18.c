#include<stdio.h>

int main(){
    int bracket_cnt = 0;
    char c;
    while((c=getchar())!='\n' && c!=EOF){
        if(c == '('){
            bracket_cnt++;
        }
        if(c == ')'){
            if(bracket_cnt == 0){
                printf("0");
                return 0;
            }
            bracket_cnt--;
        }
    }
    if(bracket_cnt == 0){
        printf("1");
    }else{
        printf("0");
    }
    return 0;
}