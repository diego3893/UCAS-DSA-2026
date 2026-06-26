#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char chdata;
    struct Node *succ;
    struct Node *next;
}Node;

int main(){
    int n, m;
    int find = 0;
    char c;
    scanf("%d%d", &n, &m);
    Node *head_str, *head_pat, *p, *q;
    head_str = (Node*)malloc(sizeof(Node));
    head_str->next = NULL;
    head_str->succ = NULL;
    getchar();
    q = head_str;
    for(int i=0; i<n; ++i){
        c = getchar();
        p = (Node*)malloc(sizeof(Node));
        q->succ = p;
        p->succ = NULL;
        p->next = q;
        q = p;
        p->chdata = c;
    }
    getchar();
    head_pat = (Node*)malloc(sizeof(Node));
    head_pat->next = NULL;
    head_pat->succ = NULL;
    q = head_pat;
    for(int i=0; i<m; ++i){
        c = getchar();
        p = (Node*)malloc(sizeof(Node));
        q->succ = p;
        p->succ = NULL;
        p->next = NULL;
        q = p;
        p->chdata = c;
    }
    head_pat->succ->next = head_pat;
    q = head_pat->succ->succ; // i = 1
    p = head_pat; // k = -1 tips:我们判定的是p->succ的字符，是k+1=1；这里为什么用k？因为链表没有前驱域，我们不知道是否回退到头节点
    while(q){ // while(i<pat.length())
        while(p!=head_pat && p->succ->chdata!=q->chdata){ // while(k!=-1 && pat[k+1]!=pat[i]) 失配
            p = p->next; // k = next[k]; 回退指针
        }
        if(p->succ->chdata == q->chdata){ // if(pat[k+1]==pat[i]) 匹配
            p = p->succ; // k++ 自匹配指针加1
        }
        q->next = p; // next[i] = k;
        q = q->succ; // i++;
    }
    p = head_pat; // k=-1
    q = head_str->succ; // j=0
    for(int i=1; i<=n; ++i){ // 这是和q同步的一个值，表示当前的下标，用于输出计算（q无法显示当前的串下标）
        while(p!=head_pat && q->chdata!=p->succ->chdata){ // 同上
            p = p->next;
        }
        if(p->succ->chdata == q->chdata){ // 匹配
            p = p->succ; // k++
        }
        if(p->succ == NULL){ // k == pat.length() 匹配成功
            printf("%d", i-m);
            find = 1;
            break;
        }
        q = q->succ; // j++
    }
    if(!find){
        printf("-1");
    }
    return 0;
}