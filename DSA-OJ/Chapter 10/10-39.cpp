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

int main() {
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    vector<int> arr;
    int x;
    stringstream ss;
    ss.str(line1);
    while(ss >> x){
        arr.push_back(x);
    }
    int m = arr.size();
    ss.clear();
    ss.str(line2);
    while(ss >> x){
        arr.push_back(x);
    }
    int n = arr.size();
    int k = min(m, n - m); 

    int pA = m-1;
    int pB = n-1;
    int k1 = 0;
    int k2 = 0;
    
    for(int i=0; i<k; ++i){
        if(pA>=0 && (pB<m || arr[pA]>arr[pB])){
            k1++;
            pA--;
        }else{
            k2++;
            pB--;
        }
    }

    rotate(arr.begin(), arr.begin()+m-k1, arr.begin()+m);
    rotate(arr.begin()+k1, arr.begin()+n-k2, arr.begin()+n);

    int p1 = k;
    int p2 = k+m-k1;
    int p_out = 0;
    int end_p1 = k+m-k1;
    int end_p2 = n;

    while(p1<end_p1 || p2<end_p2){
        if(p2==end_p2 || (p1<end_p1 && arr[p1]<=arr[p2])){
            swap(arr[p_out], arr[p1]);
            p1++;
        }else{
            swap(arr[p_out], arr[p2]);
            p2++;
        }
        p_out++;
    }

    sort(arr.begin()+n-k, arr.end());

    for(int i=0; i<n; ++i){
        printf("%d ", arr[i]);
    }

    return 0;
}