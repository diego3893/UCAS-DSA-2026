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
    string line;
    int num;
    vector<int> L;
    vector<int> R;
    stringstream ss;

    getline(cin, line);
    ss.clear();
    ss.str(line);
    while(ss >> num){
        L.push_back(num);
    }

    line.clear();
    getline(cin, line);
    ss.clear();
    ss.str(line);
    while(ss >> num){
        R.push_back(num);
    }

    bool first_output = 1;
    for(int i=0; i<R.size(); ++i){
        if(first_output){
            first_output = 0;
            printf("%d", R[i]);
        }else{
            printf(" %d", R[i]);
        }
    }
    printf("\n");
    first_output = 1;
    for(int i=0; i<L.size(); ++i){
        if(first_output){
            first_output = 0;
            printf("%d", L[i]);
        }else{
            printf(" %d", L[i]);
        }
    }

    return 0;
}