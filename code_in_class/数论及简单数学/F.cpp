#include <cstdio>
#include <iostream>
const int N = 10;
using namespace std;

int mp[N][N], ans[N][N], pre[N][N];
int dir[5][2] = {0, 1, 0, -1, 1, 0, -1, 0, 0, 0};

void deal(int row) {
    for (int j = 0; j < 6; j++) {
        if(ans[row][j])
        for(int i = 0; i < 5; i++) {
            int _x = row + dir[i][0];
            int _y = j + dir[i][1];
            if(_x < 0 || _y < 0 || _x >= 5 || _y >= 6) continue;
            pre[_x][_y] ^= 1;
        }
    }
}

void solve() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &mp[i][j]);
        }
    }
    for (int state = 0; state < (1<<6); state++) {
        int tmp_s = state;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) pre[i][j] = mp[i][j];
        }
        for (int j = 5; ~j; j--) {
            ans[0][j] = tmp_s & 1;
            tmp_s >>= 1;
        }
        for (int i = 1; i < 5; i++) {
            deal(i - 1);
            for (int j = 0; j < 6; j++) {
                ans[i][j] = pre[i-1][j];
            }
        }
        deal(4);
        int flag = 0;
        for (int j = 0; j < 6; j++) {
            if(pre[4][j]) flag = 1;
        }
        if(!flag) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    printf("%d ", ans[i][j]);
                } printf("%d\n", ans[i][5]);
            }
            return ;
        }
    }
}

int main() {
    int t, T = 0;
    scanf("%d", &t);
    while(t--) {
        printf("PUZZLE #%d\n", ++T);
        solve();
    }
    return 0;
}
