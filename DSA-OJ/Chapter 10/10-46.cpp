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
    int n;
    scanf("%d", &n);
    int arr[n+5], idx[n+5];
    for(int i=0; i<n; ++i){
        scanf("%d", &arr[i]);
        idx[i] = i;
    }
    bool is_swapped = 0;
    for(int i=1; i<n; ++i){
        for(int j=1; j<n-i+1; ++j){
            if(arr[idx[j-1]] > arr[idx[j]]){
                swap(idx[j-1], idx[j]);
                is_swapped = 1;
            }
        }
        if(!is_swapped){
            break;
        }
    }
    for(int i=0; i<n; ++i){
        printf("%d ", arr[idx[i]]);
    }
    return 0;
}