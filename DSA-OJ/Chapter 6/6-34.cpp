#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string line;
    vector<int> T, L, R;
    int u, v;
    int x;
    stringstream ss;
    
    getline(cin, line);
    ss.clear();
    ss.str(line);
    while(ss >> x){
        T.push_back(x);
    }
    
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