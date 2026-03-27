#include<stdio.h>
#include<stdlib.h>
#define STR_INIT_SIZE 50
#define STR_EXP_SIZE 10

int main(){
    char c;
    int Index = 0, size = STR_INIT_SIZE, flag = 1;
    char *str = (char*)malloc(STR_INIT_SIZE*sizeof(char));
    while((c=getchar()) != EOF){
        if(c == '\n'){
            continue;
        }
        if(c == '@'){
            flag = 1;
            for(int i=0; i<(Index/2); ++i){
                if(str[i] == str[Index-i-1]){
                    continue;
                }else{
                    flag = 0;
                    break;
                }
            }
            printf("%d\n", flag);
            Index = 0;
            continue;
        }
        str[Index++] = c;
        if(Index >= size){
            size += STR_EXP_SIZE;
            char *new_str = (char*)realloc(str, STR_EXP_SIZE*sizeof(char));
            if(new_str != NULL){
                str = new_str;
            }
        }
    }
}