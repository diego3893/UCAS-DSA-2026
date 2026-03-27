#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, arrsize;
    scanf("%d%d", &n, &arrsize);
    if(n>arrsize || n>11){
        printf("-1");
        return 0;
    }
    unsigned int *arr = (unsigned int*)malloc(arrsize*sizeof(unsigned int));
    unsigned int factorial = 1, power = 1;
    for(int i=0; i<n; ++i){
        if(i == 0){
            printf("%d ", factorial*power);
            continue;
        }
        factorial *= i;
        power *= 2;
        printf("%d ", factorial*power);
    }
    free(arr);
    arr = NULL;
    return 0;
}