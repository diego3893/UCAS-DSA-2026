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

struct Node{
    int kval;
    int addr;
    int mark_no_buddy;
    Node(int kval_, int addr_): kval(kval_), addr(addr_), mark_no_buddy(0) {}
    bool operator<(Node& other) const{
        if(kval == other.kval){
            return addr<other.addr;
        }
        return kval<other.kval;
    }
};
int buddy(int, int);

int main(){
    stringstream ss;
    string str;
    vector<Node> mem;
    getline(cin, str);
    while(str.length()){
        int kval, addr;
        ss.clear();
        ss.str(str);
        ss >> kval;
        while(ss >> addr){
            Node tmp(kval, addr);
            mem.push_back(tmp);
        }
        getline(cin, str);
    }
    while(getline(cin, str)){
        int kval, addr;
        ss.clear();
        ss.str(str);
        ss >> kval >> addr;
        Node tmp(kval, addr);
        mem.push_back(tmp);
    }
    sort(mem.begin(), mem.end());
    // for(int i=0; i<mem.size(); ++i){
    //     printf("%d %d\n", mem[i].kval, mem[i].addr);
    // }
    while(1){
        int merge = 0;
        for(int i=0; i<mem.size(); ++i){
            if(mem[i].mark_no_buddy){
                continue;
            }
            int buddy_addr = buddy(mem[i].addr, mem[i].kval);
            // printf("k:%d addr:%d buddy:%d\n", mem[i].kval, mem[i].addr, buddy_addr);
            int buddy_idx = -1;
            for(int j=0; j<mem.size(); ++j){
                if(mem[j].addr==buddy_addr && mem[j].kval==mem[i].kval){
                    buddy_idx = j;
                    break;
                }
                if(mem[j].kval > mem[i].kval){
                    break;
                }
            }
            if(buddy_idx == -1){
                mem[i].mark_no_buddy = 1;
                continue;
            }
            // printf("buddy_idx:%d\n", buddy_idx);
            Node tmp(mem[i].kval+1, min(mem[i].addr, mem[buddy_idx].addr));
            mem.push_back(tmp);
            int min_idx = min(i, buddy_idx);
            int max_idx = max(i, buddy_idx);
            mem.erase(mem.begin()+max_idx);
            mem.erase(mem.begin()+min_idx);
            merge = 1;

            // for(int i=0; i<mem.size(); ++i){
            //     printf("%d %d\n", mem[i].kval, mem[i].addr);
            // }

            break;
        }
        if(!merge){
            break;
        }
        sort(mem.begin(), mem.end());
    }
    int cur_k = mem[0].kval;
    printf("%d", cur_k);
    for(int i=0; i<mem.size(); ++i){
        if(mem[i].kval != cur_k){
            printf("\n%d", mem[i].kval);
            cur_k = mem[i].kval;
        }
        printf(" %d", mem[i].addr);
    }
    return 0;
}

int buddy(int p, int k){
    if(p%(int)(pow(2, k+1)) == 0){
        return pow(2, k)+p;
    }
    return p-pow(2, k);
}