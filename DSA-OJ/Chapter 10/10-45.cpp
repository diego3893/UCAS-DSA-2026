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

struct node{
    int a;
    int c;
    node(int _a): a(_a), c(0) {}
};

int main(){
    vector<node> arr;
    int n;
    while(scanf("%d", &n) == 1){
        arr.push_back(node(n));
    }
    int len = arr.size();
    for(int i=0; i<len; ++i){
        int cnt = 0;
        for(int j=0; j<len; ++j){
            if(arr[j].a < arr[i].a){
                cnt++;
            }
        }
        arr[i].c = cnt;
    }
    for(int i=0; i<len; ++i){
        if(i != arr[i].c){
            swap(arr[i], arr[arr[i].c]);
        }
    }
    int first_output = 1;
    for(int i=0; i<len; ++i){
        if(first_output){
            first_output = 0;
            printf("%d", arr[i].a);
        }else{
            printf(" %d", arr[i].a);
        }
    }
    return 0;
}