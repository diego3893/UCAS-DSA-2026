#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;

vector<string> split(string);
struct Node{
    int r, c;
    int data;
    Node *right, *down;
};

// 复杂度O(n*m)，输出至少需要n*m
int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    Node *rhead[m+5], *chead[n+5], *p;
    for(int i=1; i<=m; ++i){
        p = new Node;
        p->right = NULL;
        p->down = NULL;
        rhead[i] = p;
    }
    for(int i=1; i<=n; ++i){
        p = new Node;
        p->right = NULL;
        p->down = NULL;
        chead[i] = p;
    }
    string str;
    char c;
    getchar();
    while((c=getchar())!='\n' && c!=EOF){
        str += c;
    }
    vector<string> split_str = split(str);
    vector<int> v;
    // printf("%d\n", split_str.size());
    for(string s: split_str){
        v.push_back(stoi(s));
    }
    int flag;
    int idx = 0;
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            scanf("%d", &flag);
            if(flag){
                p = new Node;
                p->r = i;
                p->c = j;
                p->data = v[idx++];
                p->down = NULL;
                p->right = NULL;
                Node *q;
                q = rhead[i];
                while(q->right){
                    q = q->right;
                }
                q->right = p;
                q = chead[j];
                while(q->down){
                    q = q->down;
                }
                q->down = p;
            }
        }
    }
    
    getchar();
    str.clear();
    while((c=getchar())!='\n' && c!=EOF){
        str += c;
    }
    split_str.clear();
    v.clear();
    split_str = split(str);
    for(string s: split_str){
        v.push_back(stoi(s));
    }
    idx = 0;
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            scanf("%d", &flag);
            if(flag){
                Node *q;
                q = rhead[i];
                p = rhead[i]->right;
                while(p && p->c<j){
                    p = p->right;
                    q = q->right;
                }
                if(p){
                    if(p->c == j){
                        p->data += v[idx++];
                        if(!p->data){
                            q->right = p->right;
                            q = chead[j];
                            while(q->down != p){
                                q = q->down;
                            }
                            q->down = p->down;
                            free(p);
                            continue;
                        }
                    }
                    if(p->c > j){
                        p = new Node;
                        p->r = i;
                        p->c = j;
                        p->data = v[idx++];
                        p->right = q->right;
                        q->right = p;
                        Node *tmp;
                        tmp = chead[j];
                        q = chead[j]->down;
                        while(q && q->r<i){
                            tmp = tmp->down;
                            q = q->down;
                        }
                        if(q){
                            p->down = tmp->down;
                            tmp->down = p;
                        }else{
                            tmp->down = p;
                            p->down = NULL;
                        }
                    }
                }else{
                    p = new Node;
                    p->r = i;
                    p->c = j;
                    p->data = v[idx++];
                    p->right = NULL;
                    q->right = p;
                    Node *tmp;
                    tmp = chead[j];
                    q = chead[j]->down;
                    while(q && q->r<i){
                        tmp = tmp->down;
                        q = q->down;
                    }
                    if(q){
                        p->down = tmp->down;
                        tmp->down = p;
                    }else{
                        tmp->down = p;
                        p->down = NULL;
                    }
                }
            }
        }
    }
    int first_output = 1;
    for(int i=1; i<=m; ++i){
        Node *q;
        q = rhead[i]->right;
        while(q){
            //printf("%d,%d:%d\n", q->r, q->c, q->data);
            if(first_output){
                printf("%d", q->data);
                first_output = 0;
            }else{
                printf(" %d", q->data);
            }
            q = q->right;
        }
    }
    printf("\n");
    for(int i=1; i<=m; ++i){
        int cidx = 1;
        Node *q;
        q = rhead[i]->right;
        first_output = 1;
        while(q){
            for(int j=1; j<=q->c-cidx; ++j){
                if(first_output){
                    printf("0");
                    first_output = 0;
                }else{
                    printf(" 0");
                }
            }
            cidx = q->c+1;
            if(first_output){
                printf("1");
                first_output = 0;
            }else{
                printf(" 1");
            }
            q = q->right;
        }
        for(int j=1; j<=n-cidx+1; ++j){
            if(first_output){
                printf("0");
                first_output = 0;
            }else{
                printf(" 0");
            }
        }
        printf("\n");
    }
    
    return 0;
}

vector<string> split(string s){
    vector<string> res;
    string temp;
    for(char c: s){
        if(c == ' '){
            res.push_back(temp);
            temp.clear();
        }else{
            temp += c;
        }
    }
    res.push_back(temp);
    return res;
}