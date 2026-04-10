#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cmath>
#include<map>
using namespace std;
enum TagType{
    Link,
    Tread
};
struct Node{
    int id;
    int lc, rc;
    TagType ltag, rtag;
    Node(int x, int u, int v): id(x), lc(u), rc(v), ltag(Link), rtag(Link) {}
};
map<int, int> val2idx;
map<int, int> idx2val;
void print_tree(vector<Node>);
vector<Node> preorder_treading(vector<Node>);
vector<Node> postorder_treading(vector<Node>);
vector<Node> inorder_treading(vector<Node>);
// 维护一个并查集，查询有几棵独立的树，合并之后做线索化（复制一份操作）
// 建映射，维护节点值和下标的对应关系

int main(){
    int x, u, v, n;
    vector<Node> t;
    t.push_back({-1, -1, -1}); // 占位
    scanf("%d", &n);
    int f[n+5];
    for(int i=1; i<=n; ++i){
        f[i] = i;
    }
    for(int i=1; i<=n; ++i){
        scanf("%d%d%d", &x, &u, &v);
        Node tmp(x, u, v);
        t.push_back(tmp);
        val2idx.insert({x, i}); // 值为x的节点在t中的下标是i
        idx2val.insert({i, x});
    }
    for(int i=1; i<=n; ++i){
        if(t[i].lc){
            int lidx = val2idx[t[i].lc];
            f[lidx] = f[i];
        }
        if(t[i].rc){
            int ridx = val2idx[t[i].rc];
            f[ridx] = f[i];
        }
    }
    int pre_root = -1;
    for(int i=1; i<=n; ++i){
        if(f[i] == i){
            if(pre_root == -1){
                pre_root = i;
                t[0].id = idx2val[i]; // t[0]存合并二叉树的根
            }else{
                int root_val = idx2val[i];
                t[pre_root].rc = root_val; // 把这棵树接在上一棵树的右子树
                pre_root = i;
            }
        }
    }
    // 森林合并完成
    // for(int i=0; i<=n; ++i){
    //     printf("%d %d %d\n", t[i].id, t[i].lc, t[i].rc);
    // }
    vector<Node> preorder_t = preorder_treading(t);
    vector<Node> inorder_t = inorder_treading(t);
    vector<Node> postorder_t = postorder_treading(t);

    print_tree(preorder_t);
    print_tree(inorder_t);
    print_tree(postorder_t);

    return 0;
}

void print_tree(vector<Node> t){
    printf("%d", t[0].id);
    for(int i=1; i<t.size(); ++i){
        printf(" %d", t[i].lc);
    }
    printf("\n");
    printf("%d", t[0].id);
    for(int i=1; i<t.size(); ++i){
        printf(" %d", t[i].rc);
    }
    printf("\n");
    return;
}

vector<Node> preorder_treading(vector<Node> t){ // 先序前驱线索化
    vector<Node> preorder_t = t;
    stack<Node> s;
    s.push(preorder_t[val2idx[preorder_t[0].id]]);
    Node pre = s.top();
    while(1){
        pre = s.top();
        s.pop();
        if(pre.rc!=0 && pre.rtag==Link){
            s.push(preorder_t[val2idx[pre.rc]]);
        }
        if(pre.lc!=0 && pre.ltag==Link){
            s.push(preorder_t[val2idx[pre.lc]]);
        }
        if(s.empty()){
            break;
        }
        Node cur = s.top();
        if(cur.lc==0 && cur.ltag==Link){
            cur.ltag = Tread;
            cur.lc = pre.id;
            int cur_idx = val2idx[cur.id];
            preorder_t[cur_idx] = cur;
        }
    }
    return preorder_t;
}

vector<Node> postorder_treading(vector<Node> t){ // 后序后继线索化，使用反转变形先序（root-rc-lc反转）
    vector<Node> postorder_t = t;
    stack<Node> s;
    s.push(postorder_t[val2idx[postorder_t[0].id]]);
    Node pre = s.top();
    while(1){
        pre = s.top();
        s.pop();
        if(pre.lc!=0 && pre.ltag==Link){
            s.push(postorder_t[val2idx[pre.lc]]);
        }
        if(pre.rc!=0 && pre.rtag==Link){
            s.push(postorder_t[val2idx[pre.rc]]);
        }
        if(s.empty()){
            break;
        }
        Node cur = s.top();
        if(cur.rc==0 && cur.rtag==Link){ // 变形先序中的前驱就是后序中的后继
            cur.rtag = Tread;
            cur.rc = pre.id;
            int cur_idx = val2idx[cur.id];
            postorder_t[cur_idx] = cur;
        }
    }
    return postorder_t;
}

vector<Node> inorder_treading(vector<Node> t){ // 中序全线索化
    vector<Node> inorder_t = t;
    stack<Node> s;
    int cur_id = inorder_t[0].id;
    Node pre(-1, -1, -1);
    while(!s.empty() || cur_id!=0){
        while(cur_id != 0){
            s.push(inorder_t[val2idx[cur_id]]);
            if(inorder_t[val2idx[cur_id]].ltag == Link){
                cur_id = inorder_t[val2idx[cur_id]].lc;
            }else{
                cur_id = 0;
            }
        }
        Node cur = s.top();
        s.pop();
        if(pre.id != -1){
            if(pre.rc==0 && pre.rtag==Link){
                int pre_idx = val2idx[pre.id];
                inorder_t[pre_idx].rtag = Tread;
                inorder_t[pre_idx].rc = cur.id;
            }
            if(cur.lc==0 && cur.ltag==Link){
                int cur_idx = val2idx[cur.id];
                inorder_t[cur_idx].ltag = Tread;
                inorder_t[cur_idx].lc = pre.id;
                cur.ltag = Tread;
                cur.lc = pre.id;
            }
        }
        pre = cur;
        if(cur.rc!=0 && cur.rtag==Link){
            cur_id = cur.rc;
        }else{
            cur_id = 0;
        }
    }
    return inorder_t;
}