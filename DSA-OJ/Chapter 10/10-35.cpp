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

void down(int, vector<int>&, int);

int main(){
    int x;
    vector<int> heap;
    heap.push_back(0);
    while(cin >> x){
        heap.push_back(x);
    }
    int sz = heap.size()-1;
    for(int i=(sz+1)/3; i>=1; --i){
        down(i, heap, sz);
    }
    for(int i=1; i<sz; ++i){
        swap(heap[1], heap[sz-i+1]);
        down(1, heap, sz-i);
    }
    for(int i=1; i<=sz; ++i){
        printf("%d ", heap[i]);
    }

    return 0;
}

void down(int p, vector<int>& heap, int sz){
    int max_idx;
    int s1 = p*3-1, s2 = p*3, s3 = p*3+1;
    while(s1 <= sz){
        if(s3 <= sz){
            int max_s = max(heap[s1], max(heap[s2], heap[s3]));
            max_idx = (max_s==heap[s1])?s1:((max_s==heap[s2])?s2:s3);
        }else if(s2 <= sz){
            max_idx = (heap[s1]>heap[s2])?s1:s2;
        }else{
            max_idx = s1;
        }
        if(heap[max_idx] > heap[p]){
            swap(heap[max_idx], heap[p]);
            p = max_idx;
        }else{
            break;
        }
        s1 = p*3-1, s2 = p*3, s3 = p*3+1;
    }
    return;
}