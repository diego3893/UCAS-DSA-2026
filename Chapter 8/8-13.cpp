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

struct Node{
    int tag;
    int addr;
    int size;
    Node(int tag_, int addr_, int size_): tag(tag_), addr(addr_), size(size_) {}
    bool operator<(const Node& other) const{
        return addr < other.addr;
    }
};

int main(){
    vector<Node> ava_Node;
    string str;
    stringstream ss;
    getline(cin, str);
    while(str.length()){
        ss.clear();
        ss.str(str);
        int tag, addr, size;
        ss >> tag >> addr >> size;
        Node tmp(tag, addr, size);
        ava_Node.push_back(tmp);
        getline(cin, str);
    }
    // for(auto node: ava_Node){
    //     printf("%d %d %d\n", node.tag, node.addr, node.size);
    // }
    while(getline(cin, str)){
        ss.clear();
        ss.str(str);
        int tag, addr, size;
        ss >> tag >> addr >> size;
        Node tmp(0, addr, size);
        ava_Node.push_back(tmp);
    }
    // printf("%d\n", release_Node.size());
    sort(ava_Node.begin(), ava_Node.end());
    while(1){
        int merge = 0;
        for(int i=0; i<ava_Node.size()-1; ++i){
            if(ava_Node[i].size+ava_Node[i].addr == ava_Node[i+1].addr){
                ava_Node[i].size += ava_Node[i+1].size;
                ava_Node.erase(ava_Node.begin()+i+1);
                merge = 1;
            }
        }
        // printf("%d %d %d:%d\n", r_node.tag, r_node.addr, r_node.size, merge);
        if(!merge){
            break;
        }
    }
    int first_output = 1;
    for(auto node: ava_Node){
        if(first_output){
            printf("%d %d %d", node.tag, node.addr, node.size);
            first_output = 0;
        }else{
            printf("\n%d %d %d", node.tag, node.addr, node.size);
        }
    }
    return 0;
}