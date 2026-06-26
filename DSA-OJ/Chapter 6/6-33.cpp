#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string line;
    vector<int> L, R;
    int u, v;
    int x;
    stringstream ss;
    
    getline(cin, line);
    ss.clear();
    ss.str(line);
    while(ss >> x){
        L.push_back(x);
    }

    getline(cin, line);
    ss.clear();
    ss.str(line);
    while(ss >> x){
        R.push_back(x);
    }

    vector<int> T(L.size()+5, 0);
    for(int i=1; i<L.size(); ++i){
        if(L[i]){
            T[L[i]] = i;
        }
        if(R[i]){
            T[R[i]] = i;
        }
    }

    scanf("%d%d", &u, &v);
    while(u){
        if(T[u] == v){
            printf("1");
            return 0;
        }
        u = T[u];
    }
    printf("0");
    return 0;
}