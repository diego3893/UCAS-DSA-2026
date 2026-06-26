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

struct Node{
    char data;
    int lc, rc;
};

int main(){
    int n;
    scanf("%d", &n);
    Node tree[n+5];
    for(int i=0; i<n; ++i){
        cin >> tree[i].data;
        if(tree[i].data=='+' || tree[i].data=='-' || tree[i].data=='*' || tree[i].data=='/'){
            scanf("%d%d", &tree[i].rc, &tree[i].lc);
        }else{
            tree[i].lc = -1;
            tree[i].rc = -1;
        }
    }
    stack<Node> s;
    string ans;
    s.push(tree[0]);
    while(!s.empty()){
        Node tmp;
        tmp = s.top();
        s.pop();
        ans += tmp.data;
        if(tmp.lc != -1){
            s.push(tree[tmp.lc]);
        }
        if(tmp.rc != -1){
            s.push(tree[tmp.rc]);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}