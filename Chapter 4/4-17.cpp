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

string s, pattern, rep;

void get_nxtval(int[]);
vector<int> kmp(int[]);

int main(){
    cin >> s >> pattern >> rep;
    int nxtval[pattern.length()+5];
    
    get_nxtval(nxtval);
    // for(int i=0; i<pattern.length(); ++i){
    //     printf("%d ", nxtval[i]);
    // }

    vector<int> idx;
    idx = kmp(nxtval);

    // for(int i=0; i<idx.size(); ++i){
    //     printf("%d ", idx[i]);
    // }
    int pat_l = pattern.length();
    int i = 0, skip_idx = 0;
    while(i < s.length()){
        if((skip_idx<idx.size() && i!=idx[skip_idx]-pat_l+1) || skip_idx>=idx.size()){
            printf("%c", s[i]);
        }else if(skip_idx<idx.size() && i==idx[skip_idx]-pat_l+1){
            i = idx[skip_idx];
            cout << rep;
            skip_idx++;
        }
        i++;
    }
    return 0;
}

void get_nxtval(int nxtval[]){
    nxtval[0] = -1;
    int j = 0, k = -1;
    while(j < pattern.length()){
        if(k==-1 || pattern[j]==pattern[k]){
            ++j, ++k;
            if(pattern[j] == pattern[k]){
                nxtval[j] = nxtval[k];
            }else{
                nxtval[j] = k;
            }
        }else{
            k = nxtval[k];
        }
    }
    return;
}

vector<int> kmp(int nxtval[]){
    vector<int> ans;
    int i = 0, k = 0;
    while(i < s.length()){
        if(k >= (int)pattern.length()){
            k = 0;
            ans.push_back(i-1);
        }
        if(k==-1 || s[i]==pattern[k]){
            ++i, ++k;
        }else{
            k = nxtval[k];
        }
    }
    if(k >= (int)pattern.length()){
        ans.push_back(i-1);
    }
    return ans;
}