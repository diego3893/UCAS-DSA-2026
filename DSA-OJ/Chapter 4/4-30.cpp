#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
    string str, t;
    cin >> str;
    int len_str = str.length();
    int next[len_str], st_pos;
    int max_len = -0x7fffffff, cur_max;
    memset(next, 0, sizeof(next));
    for(int i=0; i<len_str; ++i){
        cur_max = -0x7fffffff;
        t = str.substr(i);
        int len_t = t.length();
        next[0] = -1;
        int j = -1;
        for(int k=1; k<len_t; ++k){
            while(j!=-1 && t[j+1]!=t[k]){
                j = next[j];
            }
            if(t[j+1] == t[k]){
                ++j;
            }
            next[k] = j;
        }
        for(int k=0; k<len_t; ++k){
            cur_max = max(cur_max, next[k]);
        }
        if(cur_max > max_len){
            st_pos = i;
        }
        max_len = max(max_len, cur_max+1);
    }
    if(max_len){
        cout << str.substr(st_pos, max_len) << ' ' << st_pos;
    }else{
        cout << -1;
    }
    return 0;
}