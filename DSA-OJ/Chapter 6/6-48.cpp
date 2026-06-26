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

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    char data;
    int depth;
    TreeNode(char c, TreeNode* p, int d): left(NULL), right(NULL), parent(p), data(c), depth(d) {}
};

int idx = 0;
TreeNode* build_tree(string, TreeNode*);
TreeNode* find_node(char, TreeNode*);
TreeNode* get_LCA(TreeNode*, TreeNode*);

int main(){
    string str;
    getline(cin, str);
    char u, v;
    cin >> u >> v;
    TreeNode* root = build_tree(str, NULL);
    TreeNode *p = find_node(u, root), *q = find_node(v, root);
    TreeNode *ans = get_LCA(p, q);
    printf("%c", ans->data);

    return 0;
}

TreeNode* build_tree(string s, TreeNode* parent){
    if(idx >= s.length()){
        return NULL;
    }
    if(s[idx] == '^'){
        idx++;
        return NULL;
    }
    TreeNode* p = new TreeNode(s[idx++], parent, (parent?parent->data:0)+1);
    p->left = build_tree(s, p);
    p->right = build_tree(s, p);
    return p;
}

TreeNode* find_node(char c, TreeNode* root){
    if(root == NULL){
        return NULL;
    }
    if(root->data == c){
        return root;
    }
    TreeNode* left_find_res = find_node(c, root->left);
    if(left_find_res != NULL){
        return left_find_res;
    }
    return find_node(c, root->right);
}

TreeNode* get_LCA(TreeNode* p, TreeNode* q){
    TreeNode *p1 = p, *q1 = q;
    while(p1 != q1){
        if(p1->depth <= q1->depth){
            q1 = q1->parent;
            continue;
        }
        if(p1->depth >= q1->depth){
            p1 = p1->parent;
            continue;
        }
    }
    if(p1!=p && q1!=q){
        return p1;
    }
    if(p1 == p){
        if(p1->parent != NULL){
            return p1->parent;
        }
        return p1;
    }
    if(p1 == q){
        if(p1->parent != NULL){
            return p1->parent;
        }
        return p1;
    }
}