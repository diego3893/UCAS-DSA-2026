#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

int main(){
    int lowerbound, upperbound, size;
    scanf("%d %d %d", &lowerbound, &upperbound, &size);
    int n = (upperbound-lowerbound)/size;
    int tag[n+5];
    for(int i=0; i<n; ++i){
        scanf("%d", &tag[i]);
    }
    int addr = -1;
    int ava_size = 0;
    int first_output = 1;
    for(int i=0; i<n; ++i){
        if(!tag[i]){
            ava_size += size;
            if(addr == -1){
                addr = lowerbound+i*size;
            }
        }
        if(tag[i]){
            if(ava_size){
                if(first_output){
                    printf("0 %d %d", addr, ava_size);
                    first_output = 0;
                }else{
                    printf("\n0 %d %d", addr, ava_size);
                }
                ava_size = 0;
                addr = -1;
            }
        }
    }
    if(ava_size){
        if(first_output){
            printf("0 %d %d", addr, ava_size);
            first_output = 0;
        }else{
            printf("\n0 %d %d", addr, ava_size);
        }
    }
    if(first_output){
        printf("0 0 0");
    }
    return 0;
}