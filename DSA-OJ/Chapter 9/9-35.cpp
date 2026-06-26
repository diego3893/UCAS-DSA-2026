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
    string s;
    vector<int> arr;
    stringstream ss;
    int first_output = 1;
    int a, b;
    int x;
    getline(cin, s);
    ss.str(s);
    while(ss >> x){
        arr.push_back(x);
    }
    scanf("%d%d", &a, &b);
    for(int i=0; i<arr.size(); ++i){
        if(arr[i] <= a){
            continue;
        }
        if(arr[i] >= b){
            break;
        }
        if(first_output){
            printf("%d", arr[i]);
            first_output = 0;
        }else{
            printf(" %d", arr[i]);
        }
    }

    return 0;
}