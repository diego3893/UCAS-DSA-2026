#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct PolyTerm{
    int power;
    int param;
}PolyTerm;
typedef struct PolyNode{
    PolyTerm data;
    struct PolyNode *next;
}Node;

Node *head, *p, *q;

void data_process(char[], int*, int*, int, int);
void data_save(int*, int, int, char[]);

int main(){
    char c, str[100];
    int Index = 0, sign = 1, st = 0, node_cnt = 0;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    q = head;

    while((c=getchar())!='\n' && c!=EOF){
        if(c == ' '){
            continue;
        }
        if(c == '+'){
            data_save(&node_cnt, sign, Index, str);
            sign = 1;
            Index = 0;
            continue;
        }
        if(c == '-'){
            if(st){
                data_save(&node_cnt, sign, Index, str);
            }
            sign = -1;
            Index = 0;
            continue;
        }
        str[Index++] = c;
        st = 1;
    }
    data_save(&node_cnt, sign, Index, str);
    p = head;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = head;
    // printf("cnt:%d\n", node_cnt);

    for(int i=0; i<node_cnt-1; ++i){
        p = head->next;
        q = head;
        for(int j=0; j<node_cnt-1-i; ++j){
            if(p->data.power < p->next->data.power){
                q->next = p->next;
                p->next = q->next->next;
                q->next->next = p;
            }
            p = q->next->next;
            q = q->next;
        }
    }

    p = head->next;
    q = head;
    while(p != head){
        p->data.param *= p->data.power;
        if(p->data.param == 0){
            q->next = p->next;
            free(p);
            p = q->next;
            continue;
        }
        p->data.power--;
        p = p->next;
        q = q->next;
    }

    st = 0;
    p = head->next;
    while(p != head){
        if(p->data.param < 0){
            if(p->data.power > 1){
                printf("- %dx^%d ", abs(p->data.param), p->data.power);
            }
            if(p->data.power == 1){
                printf("- %dx ", abs(p->data.param));
            }
            if(p->data.power == 0){
                printf("- %d ", abs(p->data.param));
            }
        }else{
            if(st){
                if(p->data.power > 1){
                    printf("+ %dx^%d ", abs(p->data.param), p->data.power);
                }
                if(p->data.power == 1){
                    printf("+ %dx ", abs(p->data.param));
                }
                if(p->data.power == 0){
                    printf("+ %d ", abs(p->data.param));
                }
            }else{
                if(p->data.power > 1){
                    printf("%dx^%d ", abs(p->data.param), p->data.power);
                }
                if(p->data.power == 1){
                    printf("%dx ", abs(p->data.param));
                }
                if(p->data.power == 0){
                    printf("%d ", abs(p->data.param));
                }
            }
        }
        p = p->next;
        st = 1;
    }

    if(!st){
        printf("0");
    }

    return 0;
}

void data_process(char s[], int* power, int* param, int sign, int length){
    int num = 0, Index = 0, pow = 0;
    while(s[Index]!='x' && Index<length){
        num = num*10+s[Index]-'0';
        Index++;
    }
    *param = num*sign;
    if(Index == length){
        *power = 0;
        return;
    }
    if(s[Index]=='x' && Index==length-1){
        *power = 1;
        return;
    }
    Index += 2;
    while(Index < length){
        pow = pow*10+s[Index]-'0';
        Index++;
    }
    *power = pow;
    return;
}

void data_save(int* node_cnt, int sign, int length, char s[]){
    int power, param;
    data_process(s, &power, &param, sign, length);
    q = head;
    p = head->next;
    while(p != NULL){
        if(p->data.power == power){
            break;
        }
        p = p->next;
        q = q->next;
    }
    if(p == NULL){
        p = (Node*)malloc(sizeof(Node));
        p->next = NULL;
        q->next = p;
        p->data.param = param;
        p->data.power = power;
        (*node_cnt)++;
        return;
    }else{
        p->data.param += param;
        return;
    }
}