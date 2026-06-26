#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;

vector<string> split(string);

// 复杂度O(n*m)
int main(){
    int m, n;
    scanf("%d%d", &m, &n);
    string str;
    char c;
    getchar();
    while((c=getchar())!='\n' && c!=EOF){
        str += c;
    }
    int size1 = 0, B1[m+5][n+5];
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            scanf("%d", &B1[i][j]);
            if(B1[i][j] == 1){
                size1++;
            }
        }
    }
    int V1[size1+5];
    int Index = 0;
    vector<string> split_str = split(str);
    // printf("%d\n", split_str.size());
    for(string s: split_str){
        V1[Index++] = stoi(s);
    }
    Index = 0;
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            if(B1[i][j] == 1){
                B1[i][j] = V1[Index++];
            }
        }
    }

    getchar();
    str.clear();
    while((c=getchar())!='\n' && c!=EOF){
        str += c;
    }
    int size2 = 0, B2[m+5][n+5];
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            scanf("%d", &B2[i][j]);
            if(B2[i][j] == 1){
                size2++;
            }
        }
    }
    int V2[size2+5];
    Index = 0;
    split_str.clear();
    split_str = split(str);
    // printf("%d\n", split_str.size());
    for(string s: split_str){
        V2[Index++] = stoi(s);
    }
    Index = 0;
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            if(B2[i][j] == 1){
                B2[i][j] = V2[Index++];
            }
        }
    }
    // for(int i=1; i<=m; ++i){
    //     for(int j=1; j<=n; ++j){
    //         printf("%d ", B2[i][j]);
    //     }
    //     printf("\n");
    // }
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            B1[i][j] += B2[i][j];
        }
    }
    int first_output = 1;
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            if(B1[i][j]){
                if(first_output){
                    printf("%d", B1[i][j]);
                    first_output = 0;
                }else{
                    printf(" %d", B1[i][j]);
                }
            }
        }
    }
    printf("\n");
    for(int i=1; i<=m; ++i){
        first_output = 1;
        for(int j=1; j<=n; ++j){
            if(first_output){
                printf("%d", (B1[i][j])?1:0);
                first_output = 0;
            }else{
                printf(" %d", (B1[i][j])?1:0);
            }
        }
        printf("\n");
    }
    return 0;
}

vector<string> split(string s) {
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