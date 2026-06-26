#include<stdio.h>
typedef struct{
    int M;
    int F;
    int total;
}Score;

int main(){
    Score score[5];
    int pts;
    for(int i=0; i<5; ++i){
        score[i].M = 0;
        score[i].F = 0;
        score[i].total = 0;
    }
    char c, str[10];
    int Index = 0;
    while((c = getchar()) != EOF){
        if(c!='\n' && Index<5){
            str[Index++] = c;
            // printf("%d\n", Index);
        }else if(Index == 5){
            scanf("%d", &pts);
            // printf("%d\n", pts);
            Index++;
        }else{
            Index = 0;
            if(str[2] == 'M'){
                score[str[4]-'A'].M += pts;
            }
            if(str[2] == 'F'){
                score[str[4]-'A'].F += pts;
            }
        }
    }
    for(int i=0; i<5; ++i){
        score[i].total = score[i].F+score[i].M;
        if(score[i].M != 0){
            printf("%c %c %d\n", i+'A', 'M', score[i].M);
        }
        if(score[i].F != 0){
            printf("%c %c %d\n", i+'A', 'F', score[i].F);
        }
        if(score[i].total != 0){
            printf("%c %d\n", i+'A', score[i].total);
        }
    }
    return 0;
}