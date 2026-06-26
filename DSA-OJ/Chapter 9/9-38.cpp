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
    node(int x): data(x), lc(NULL), rc(NULL) {}
};

int first_output = 1;
node* build_tree(const vector<int>&, int&);
node* preorder2tree();
void inorder(node*);
void insertBST(node*&, int);
void mergeBST(node*&, node*);

int main(){
    node *tree1, *tree2;
    tree1 = preorder2tree();
    tree2 = preorder2tree();
    mergeBST(tree1, tree2);
    inorder(tree1);

    return 0;
}

node* preorder2tree(){
    string s;
    stringstream ss;
    getline(cin, s);
    ss.str(s);
    int x;
    vector<int> arr;
    while(ss >> x){
        arr.push_back(x);
    }
    node* root;
    int idx = 0;
    root = build_tree(arr, idx);
    return root;
}

node* build_tree(const vector<int>& arr, int& idx){
    if(arr[idx] == -1){
        idx++;
        return NULL;
    }
    node* root = new node(arr[idx]);
    idx++;
    root->lc = build_tree(arr, idx);
    root->rc = build_tree(arr, idx);
    return root;
}

void inorder(node* root){
    if(!root){
        return;
    }
    inorder(root->lc);
    if(first_output){
        printf("%d", root->data);
        first_output = 0;
    }else{
        printf(" %d", root->data);
    }
    inorder(root->rc);
    return;
}

void insertBST(node*& root, int val){
    if(!root){
        root = new node(val);
        return;
    }
    if(root->data > val){
        insertBST(root->lc, val);
    }else{
        insertBST(root->rc, val);
    }
    return;
}

void mergeBST(node*& dst, node* src){
    if(!src){
        return;
    }
    insertBST(dst, src->data);
    mergeBST(dst, src->lc);
    mergeBST(dst, src->rc);
    return;
}