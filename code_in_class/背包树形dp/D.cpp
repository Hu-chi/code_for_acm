#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
const int N = 1666;
using namespace std;
int n;
vector<int> e[N];
int dp[N][2];

int dfs(int u, int fa) {
    dp[u][1] = 1;
    for(int i = 0; i < e[u].size(); i++) {
        if(e[u][i] == fa) continue;
        int v = e[u][i];
        dfs(v, u);
        dp[u][0] += max(dp[v][1], dp[v][0]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    while(~scanf("%d", &n)) {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            e[i].clear();
            int cnt = 0, v;
            scanf("%*d:(%d)", &cnt);
            for (int j = 0; j < cnt; j++) {
                scanf("%d", &v);
                e[i].push_back(v);
            }
        }
        dfs(0, -1);
        printf("%d\n", n - max(dp[0][0], dp[0][1]));
    } return 0;
}
