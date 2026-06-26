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
#include<map>
using namespace std;

enum TagType{
    Link,
    Tread
};

struct Node{
    int val;
    int lc, rc;
    TagType ltag, rtag;
    Node(int v, int l, int r): val(v), lc(l), rc(r), ltag(Link), rtag(Link) {}
};
map<int, int> val2idx;
map<int, int> idx2val;
vector<Node> tree_input(vector<Node>, int*);
vector<Node> inorder_treading(vector<Node>, int);
void print_inorder(vector<Node>);

int main(){
    // freopen("data.in", "r", stdin);
    vector<Node> tree;
    tree.push_back({-1, -1, -1});
    int root;
    tree = tree_input(tree, &root);
    int subtree_root, link_node;
    scanf("%d", &link_node);
    getchar();
    tree = tree_input(tree, &subtree_root);
    if(!tree[val2idx[link_node]].lc){
        tree[val2idx[link_node]].lc = subtree_root;
    }else{
        tree[val2idx[subtree_root]].rc = tree[val2idx[link_node]].lc;
        tree[val2idx[link_node]].lc = subtree_root;
    }

    tree = inorder_treading(tree, root);

    // printf("%d\n", root);
    // for(int i=1; i<tree.size(); ++i){
    //     printf("val:%d, lc:%d, rc:%d\n", tree[i].val, tree[i].lc, tree[i].rc);
    // }
    print_inorder(tree);

    return 0;
}
vector<Node> tree_input(vector<Node> tree, int* root){
    vector<Node> res = tree;
    stringstream ss1, ss2;
    string str1, str2;

    getline(cin, str1);
    ss1.str(str1);
    getline(cin, str2);
    ss2.str(str2);
    int lc, rc;
    ss1 >> lc;
    ss2 >> rc;
    *root = lc;
    int node_cnt = 0;
    while(ss1>>lc && ss2>>rc){
        Node tmp(*root+node_cnt, lc, rc);
        node_cnt++;
        res.push_back(tmp);
        val2idx.insert({tmp.val, res.size()-1});
        idx2val.insert({res.size()-1, tmp.val});
    }
    return res;
}

vector<Node> inorder_treading(vector<Node> tree, int root){
    vector<Node> res = tree;
    stack<Node> s;
    Node pre(-1, -1, -1);
    int cur_val = root;
    while(cur_val!=0 || !s.empty()){
        while(cur_val != 0){
            s.push(tree[val2idx[cur_val]]);
            if(s.top().lc!=0 && s.top().ltag==Link){
                cur_val = s.top().lc;
            }else{
                cur_val = 0;
            }
        }
        Node cur = s.top();
        s.pop();
        int cur_idx = val2idx[cur.val];
        if(pre.val != -1){
            int pre_idx = val2idx[pre.val];
            if(pre.rc==0 && pre.rtag==Link){
                res[pre_idx].rtag = Tread;
                res[pre_idx].rc = cur.val;
            }
            if(cur.ltag==Link && cur.lc==0){
                res[cur_idx].ltag = Tread;
                res[cur_idx].lc = pre.val;
                cur = res[cur_idx];
            }
        }
        pre = cur;
        if(cur.rc!=0 && cur.rtag==Link){
            cur_val = cur.rc;
        }else{
            cur_val = 0;
        }
    }
    return res;
}

void print_inorder(vector<Node> tree){
    Node cur(-1, -1, -1);
    for(int i=1; i<tree.size(); ++i){
        if(tree[i].lc == 0){
            cur = tree[i];
            break;
        }
    }
    while(cur.rc){
        printf("%d ", cur.val);
        if(cur.rtag == Tread){ // 线索化才能直接跳
            cur = tree[val2idx[cur.rc]];
        }else{
            cur = tree[val2idx[cur.rc]];
            while(cur.ltag==Link && cur.lc!=0){
                cur = tree[val2idx[cur.lc]];
            }
        }
    }
    printf("%d", cur.val);
    return;
}