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

struct node{
    int data;
    node *lc, *rc;
    node(int d): data(d), lc(NULL), rc(NULL) {}
};

void insert(int, node*&);
vector<int> post_order(node*);

int main(){
    string s;
    stringstream ss;
    getline(cin, s);
    ss.str(s);
    int x;
    vector<int> post_order_arr;
    node *head = NULL;
    while(ss >> x){
        insert(x, head);
    }
    post_order_arr = post_order(head);
    int lower_bound, first_output = 1;
    scanf("%d", &lower_bound);
    for(int i=0; i<post_order_arr.size(); ++i){
        if(post_order_arr[i] >= lower_bound){
            if(first_output){
                printf("%d", post_order_arr[i]);
                first_output = 0;
            }else{
                printf(" %d", post_order_arr[i]);
            }
        }else{
            break;
        }
    }
    return 0;
}

void insert(int x, node* &root){
    if(!root){
        root = new node(x);
        return;
    }
    if(root->data < x){
        insert(x, root->rc);
    }else{
        insert(x, root->lc);
    }
}

vector<int> post_order(node* root){
    stack<node> s;
    vector<int> ans;
    s.push(*root);
    while(!s.empty()){
        node cur = s.top();
        s.pop();
        ans.push_back(cur.data);
        if(cur.lc != NULL){
            s.push(*cur.lc);
        }
        if(cur.rc != NULL){
            s.push(*cur.rc);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}