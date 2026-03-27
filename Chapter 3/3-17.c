#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 50
#define STACK_EXP_SIZE 10

int main(){
    char *str = (char*)malloc(STACK_INIT_SIZE*sizeof(char)), c;
    int top = 0, size = STACK_INIT_SIZE;
    while((c=getchar()) != '&'){
        str[top++] = c;
        if(top >= size){
            size += STACK_EXP_SIZE;
            char *new_str = (char*)realloc(str, STACK_EXP_SIZE*sizeof(char));
            if(new_str != NULL){
                str = new_str;
            }
        }
    }
    while((c=getchar()) != '@'){
        if(top == 0){
            printf("0");
            return 0;
        }
        if(c == str[top-1]){
            top--;
        }else{
            printf("0");
            return 0;
        }
    }
    printf("1");
    return 0;
}