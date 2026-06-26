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

map<char, int> sym2idx;
struct Node{
    string exp;
    char sym;
};
stack<Node> s_exp;

// 输入忽略#，即得前缀表达式
// 维护运算符优先级
// 每个运算符，弹两个表达式，优先级低必加括号，同级先弹出的那个加括号，节点的符号为最后一次运算弹出的符号
// 读入整个串，从右向左扫！这是波兰表达式；逆波兰和波兰的处理并不一样QAQ
const int priority[4][4] = {{0, 0, -1, -1},
                            {0, 0, -1, -1},
                            {1, 1, 0, 0},
                            {1, 1, 0, 0}};

int get_priority(char, char);
void generate_exp(char);

int main(){
    sym2idx.insert({'+', 0});
    sym2idx.insert({'-', 1});
    sym2idx.insert({'*', 2});
    sym2idx.insert({'/', 3});
    char c;
    string str;
    while((c=getchar())!='\n' && c!=EOF){
        if(c == '#'){
            continue;
        }else{
            str += c;
        }
    }
    for(int i=str.length()-1; i>=0; --i){
        if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/'){
            generate_exp(str[i]);
        }else{
            Node tmp;
            tmp.exp = str[i];
            tmp.sym = '#';
            s_exp.push(tmp);
        }
    }
    cout << s_exp.top().exp;
    return 0;
}

int get_priority(char sym1, char sym2){
    return priority[sym2idx[sym1]][sym2idx[sym2]];
}

void generate_exp(char sym){
    if(s_exp.size() < 2){
        return;
    }
    Node exp1 = s_exp.top();
    s_exp.pop();
    Node exp2 = s_exp.top();
    s_exp.pop();
    Node ans;
    ans.sym = sym;
    ans.exp.clear();
    int priority;
    if(exp1.sym != '#'){
        priority = get_priority(sym, exp1.sym);
        if(priority == 1){
            ans.exp += '('+exp1.exp+')';
        }else{
            ans.exp += exp1.exp;
        }
    }else{
        ans.exp += exp1.exp;
    }
    ans.exp += sym;
    if(exp2.sym != '#'){
        priority = get_priority(sym, exp2.sym);
        if(priority==-1 || (priority==0&&(sym=='+'||sym=='*'))){
            ans.exp += exp2.exp;
        }else{
            ans.exp += '('+exp2.exp+')';
        }
    }else{
        ans.exp += exp2.exp;
    }
    s_exp.push(ans);
    return;
}