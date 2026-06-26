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
    TreeNode(char c, TreeNode* p): left(NULL), right(NULL), parent(p), data(c) {}
};

TreeNode* build_tree(TreeNode*, string, string);
void print_tree(TreeNode*);

int main(){
    string preorder, inorder;
    getline(cin, preorder);
    getline(cin, inorder);
    TreeNode* root = build_tree(NULL, preorder, inorder);
    print_tree(root);

    return 0;
}

TreeNode* build_tree(TreeNode* parent, string preorder, string inorder){
    if(preorder.empty() || inorder.empty()){
        return NULL;
    }
    char root = preorder[0];
    TreeNode* p = new TreeNode(root, parent);
    int root_idx_inorder = inorder.find(root);
    string left_inorder = inorder.substr(0, root_idx_inorder);
    string right_inorder = inorder.substr(root_idx_inorder+1);
    string left_preorder = preorder.substr(1, left_inorder.length());
    string right_preorder = preorder.substr(left_inorder.length()+1);
    p->left = build_tree(p, left_preorder, left_inorder);
    p->right = build_tree(p, right_preorder, right_inorder);
    return p;
}

void print_tree(TreeNode* root){
    if(root == NULL){
        return;
    }
    print_tree(root->left);
    print_tree(root->right);
    printf("%c", root->data);
    return;
}