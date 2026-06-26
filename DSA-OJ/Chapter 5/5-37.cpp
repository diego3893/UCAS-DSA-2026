#include<cstdio>
#include<string>
#include<iostream>
#include<cctype>
using namespace std;

enum NodeType{
    Atom,
    List
};

struct GLNode{
    NodeType type;
    union{
        char data;
        GLNode *hp;
    };
    GLNode *tp;
};

GLNode* createGList(string, int&);
GLNode* removeX(GLNode*, char);
void printGList(GLNode*);

int main(){
    string line;
    getline(cin, line);
    int spacePos = line.find_last_of(' ');
    string glStr = line.substr(0, spacePos);
    char target = line[spacePos+1];
    int pos = 0;
    GLNode *root = new GLNode();
    root->type = List;
    root->hp = createGList(glStr, pos);
    root->tp = NULL;
    root->hp = removeX(root->hp, target);
    if(root->hp == NULL){
        printf("-1\n");
    }else{
        printGList(root->hp);
        printf("\n");
    }
    return 0;
}

GLNode* createGList(string s, int &pos){
    GLNode *node = NULL;
    char c = s[pos];
    pos++;

    if(c == '('){
        node = new GLNode();
        node->type = List;
        node->hp = createGList(s, pos);
        if(s[pos] == ')'){
            pos++;
        }
        if(s[pos] == ','){
            pos++;
            node->tp = createGList(s, pos);
        }else{
            node->tp = NULL;
        }
    }else if(isalpha(c)){
        node = new GLNode();
        node->type = Atom;
        node->data = c;
        if(s[pos] == ','){
            pos++;
            node->tp = createGList(s, pos);
        }else{
            node->tp = NULL;
        }
    }else if(c == ')'){
        pos--;
        return NULL;
    }
    return node;
}

GLNode* removeX(GLNode *L, char x){
    if(L == NULL){
        return NULL;
    }
    L->tp = removeX(L->tp, x);
    if(L->type == Atom){
        if(L->data == x){
            GLNode *nextNode = L->tp;
            delete(L);
            return nextNode;
        }
        return L;
    }else{
        L->hp = removeX(L->hp, x);
        if(L->hp == NULL){
            GLNode *nextNode = L->tp;
            delete(L);
            return nextNode;
        }
        return L;
    }
}

void printGList(GLNode* L){
    if(L == NULL){
        return;
    }
    if(L->type == Atom){
        printf("%c", L->data);
    }else{
        printf("(");
        printGList(L->hp);
        printf(")");
    }
    if(L->tp != NULL){
        printf(",");
        printGList(L->tp);
    }
}