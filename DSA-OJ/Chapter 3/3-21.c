#include<stdio.h>
#include<stdlib.h>

#define OPSETSIZE 7

typedef struct Node{
    struct Node *next;
    struct Node *prior;
    char data;
}Node;

char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};
const unsigned char Prior[OPSETSIZE][OPSETSIZE] = {
 {'>','>','<','<','<','>','>'},
 {'>','>','<','<','<','>','>'},
 {'>','>','>','>','<','>','>'},
 {'>','>','>','>','<','>','>'},
 {'<','<','<','<','<','=',' '},
 {'>','>','>','>',' ','>','>'},
 {'<','<','<','<','<',' ','='}};

 int checkPrior(char, char);

int main(){
    int c;
    int isOP;
    Node *st_op, *top_op, *p;
    st_op = (Node*)malloc(sizeof(Node));
    // st_num = (Node*)malloc(sizeof(Node));
    st_op->next = NULL;
    st_op->prior = NULL;
    st_op->data = '#';
    top_op = st_op;
    // st_num->next = NULL;
    // st_num->prior = NULL;
    // st_num->data = '#';
    // top_num = st_num;
    while((c=getchar())!='\n' && c!=EOF){
        isOP = 0;
        for(int i=0; i<OPSETSIZE; ++i){
            if(c == OPSET[i]){
                isOP = 1;
                break;
            }
        }
        if(!isOP){
            // p = (Node*)malloc(sizeof(Node));
            // p->next = NULL;
            // p->prior = top_num;
            // p->data = c;
            // top_num->next = p;
            // top_num = p;
            printf("%c", c);
        }
        if(isOP){
            int sym_prior = checkPrior(top_op->data, c);
            if(sym_prior == 0){
                p = top_op;
                top_op = top_op->prior;
                top_op->next = NULL;
                free(p);
            }
            if(sym_prior == -1){
                p = (Node*)malloc(sizeof(Node));
                p->next = NULL;
                p->prior = top_op;
                p->data = c;
                top_op->next = p;
                top_op = p;
            }
            if(sym_prior == 1){
                while(sym_prior == 1){
                    p = top_op;
                    printf("%c", p->data);
                    top_op = top_op->prior;
                    top_op->next = NULL;
                    free(p);
                    if(top_op->data == '#'){
                        break;
                    }
                    sym_prior = checkPrior(top_op->data, c);
                }
                if(sym_prior != 0){
                    p = (Node*)malloc(sizeof(Node));
                    p->next = NULL;
                    p->prior = top_op;
                    p->data = c;
                    top_op->next = p;
                    top_op = p;
                }else{
                    p = top_op;
                    top_op = top_op->prior;
                    top_op->next = NULL;
                    free(p);
                }
            }
        }
    }
    while(top_op->data != '#'){
        printf("%c", top_op->data);
        top_op = top_op->prior;
    }
    return 0;
}
int checkPrior(char a, char b){
    int a_index, b_index;
    for(int i=0; i<OPSETSIZE; ++i){
        if(a == OPSET[i]){
            a_index = i;
        }
        if(b == OPSET[i]){
            b_index = i;
        }
    }
    if(Prior[a_index][b_index] == '>'){
        return 1;
    }
    if(Prior[a_index][b_index] == '='){
        return 0;
    }
    if(Prior[a_index][b_index] == '<'){
        return -1;
    }
}