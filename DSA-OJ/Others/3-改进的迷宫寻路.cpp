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

const int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
struct Coord{
    int x, y;
    int f;
};

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    char maze[n+1][m+1];
    char maze_bak[n+1][m+1];
    Coord st, ed, key;
    for(int i=0; i<=n; ++i){
        for(int j=0; j<=m; ++j){
            if(i == 0){
                maze[i][j] = '1';
                continue;
            }
            if(j == 0){
                maze[i][j] = '1';
                continue;
            }
            scanf("%c", &maze[i][j]);
            if(maze[i][j] == 'R'){
                st.x = i, st.y = j;
                st.f = -1;
            }
            if(maze[i][j] == 'C'){
                ed.x = i, ed.y = j;
                ed.f = -1;
            }
            if(maze[i][j] == 'Y'){
                key.x = i, key.y = j;
                key.f = -1;
            }
        }
        getchar();
    }
    memcpy(maze_bak, maze, sizeof(maze));
    int head = 0, tail = 0;
    Coord q[100*100+10];
    q[tail++] = st;
    int find_key = 0, find_ed = 0;
    while(head<tail && !find_key){
        Coord cur = q[head++];
        maze_bak[cur.x][cur.y] = '2';
        for(int i=0; i<4; ++i){
            int dx, dy;
            dx = cur.x+dir[i][0];
            dy = cur.y+dir[i][1];
            if(1<=dx&&dx<=n && 1<=dy&&dy<=m && maze_bak[dx][dy]=='0'){
                Coord tmp;
                tmp = {dx, dy, head-1};
                q[tail++] = tmp;
            }
            if(1<=dx&&dx<=n && 1<=dy&&dy<=m && maze_bak[dx][dy]=='Y'){
                Coord tmp;
                tmp = {dx, dy, head-1};
                q[tail++] = tmp;
                find_key = 1;
                break;
            }
        }
    }
    stack<Coord> s;
    s.push(q[tail-1]);
    while(s.top().f != -1){
        s.push(q[s.top().f]);
    }
    while(!s.empty()){
        printf("%d %d\n", s.top().x, s.top().y);
        s.pop();
    }

    head = 0, tail = 0;
    q[tail++] = key;
    while(head<tail && !find_ed){
        Coord cur = q[head++];
        maze[cur.x][cur.y] = '2';
        for(int i=0; i<4; ++i){
            int dx, dy;
            dx = cur.x+dir[i][0];
            dy = cur.y+dir[i][1];
            if(1<=dx&&dx<=n && 1<=dy&&dy<=m && maze[dx][dy]=='0'){
                Coord tmp;
                tmp = {dx, dy, head-1};
                q[tail++] = tmp;
            }
            if(1<=dx&&dx<=n && 1<=dy&&dy<=m && maze_bak[dx][dy]=='C'){
                Coord tmp;
                tmp = {dx, dy, head-1};
                q[tail++] = tmp;
                find_ed = 1;
                break;
            }
        }
    }
    s.push(q[tail-1]);
    while(s.top().f != -1){
        s.push(q[s.top().f]);
    }
    s.pop();
    while(!s.empty()){
        printf("%d %d\n", s.top().x, s.top().y);
        s.pop();
    }
    return 0;
}