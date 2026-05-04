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

enum State{
    NORMAL,
    IN_STRING,
    IN_CHAR,
    IN_COMMENT
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    State state = NORMAL;
    char c, next_c;

    while(cin.get(c)){
        if(state == NORMAL){
            if(c == '/'){
                if(cin.get(next_c)){
                    if(next_c == '*'){
                        state = IN_COMMENT;
                    }else{
                        cout.put(c);
                        cin.putback(next_c);
                    }
                }else{
                    cout.put(c);
                }
            }else if(c == '"'){
                state = IN_STRING;
                cout.put(c);
            }else if(c == '\''){
                state = IN_CHAR;
                cout.put(c);
            }else{
                cout.put(c);
            }
        } 
        else if(state == IN_STRING){
            cout.put(c);
            if(c == '\\'){
                if(cin.get(next_c)){
                    cout.put(next_c);
                }
            }else if(c == '"'){
                state = NORMAL;
            }
        } 
        else if(state == IN_CHAR){
            cout.put(c);
            if(c == '\\'){
                if(cin.get(next_c)){
                    cout.put(next_c);
                }
            }else if(c == '\''){
                state = NORMAL;
            }
        } 
        else if(state == IN_COMMENT){
            if(c == '*'){
                if(cin.get(next_c)){
                    if(next_c == '/'){
                        state = NORMAL;
                    }else{
                        cin.putback(next_c);
                    }
                }
            }
        }
    }
    return 0;
}