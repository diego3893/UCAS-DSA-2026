#include<stdio.h>

typedef struct{
    int r;
    int c;
}Queue;

const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main(){
    int m, n, st_row, st_col, dir, color;
    scanf("%d%d%d%d%d", &m, &n, &st_row, &st_col, &dir);
    int matrix[m+5][n+5], book[m+5][n+5];
    Queue q[m*n+5];
    int head = 0, tail = 0;
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &matrix[i][j]);
            book[i][j] = 0;
        }
    }
    color = matrix[st_row][st_col];
    int nr = st_row, nc = st_col;
    q[tail].r = st_row, q[tail++].c = st_col;
    book[nr][nc] = 1;
    while(head < tail){
        for(int i=0; i<4; ++i){
            nr = q[head].r+dirs[i][0];
            nc = q[head].c+dirs[i][1];
            if((0<=nr && nr<m) && (0<=nc && nc<n)){
                if(matrix[nr][nc]==color && !book[nr][nc]){
                    q[tail].r = nr, q[tail++].c = nc;
                    book[nr][nc] = 1;
                }
            }
        }
        if(color == 1){
            matrix[q[head].r][q[head].c] = 2;
        }
        head++;
    }
    for(int i=0; i<m; ++i){
        for(int j=0; j<n; ++j){
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}