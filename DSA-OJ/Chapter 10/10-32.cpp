#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
using namespace std;

int main(){
    int arr[5];
    memset(arr, 0, sizeof(arr));
    int n;
    while(scanf("%d", &n) == 1){
        arr[n]++;
    }
    int first_output = 1;
    for(int i=1; i<=3; ++i){
        while(arr[i]){
            if(first_output){
                printf("%d", i);
                first_output = 0;
            }else{
                printf(" %d", i);
            }
            arr[i]--;
        }
    }
    return 0;
}