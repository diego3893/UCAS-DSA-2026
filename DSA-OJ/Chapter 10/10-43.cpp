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
    vector<int> arr;
    int n;
    while(scanf("%d", &n) == 1){
        arr.push_back(n);
    }
    vector<int> c;
    int len = arr.size();
    for(int i=0; i<len; ++i){
        int cnt = 0;
        for(int j=0; j<len; ++j){
            if(arr[j] < arr[i]){
                cnt++;
            }
        }
        c.push_back(cnt);
    }
    int first_output = 1;
    for(int i=0; i<len; ++i){
        if(first_output){
            first_output = 0;
            printf("%d", c[i]);
        }else{
            printf(" %d", c[i]);
        }
    }
    return 0;
}