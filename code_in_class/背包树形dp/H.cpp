#include <bits/stdc++.h>
const int N = 233;
using namespace std;

int dp[N][N], b[N], n, m, id;
vector<int> e[N];

void dfs(int u) {
    for (int i = 0; i < e[u].size(); i++) {
        int v = e[u][i];
        dfs(v);
        for (int j = m+1; j > 1; j--) {
            for (int k = 1; k < j; k++) {
                dp[u][j] = max(dp[u][j], dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

int main() {
    while(~scanf("%d%d", &n, &m) && n) {
        for (int i = 0; i <= n; i++) e[i].clear();
        for (int i = 0; i <= m+1; i++) dp[0][i] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &id, &b[i]);
            e[id].push_back(i);
            for (int j = 1; j <= m+1; j++) {
                dp[i][j] = b[i];
            }
        }
        dfs(0);
        printf("%d\n", dp[0][m+1]);
    }
    return 0;
}
