#include <bits/stdc++.h>
const int N = 1e4+8;
using namespace std;
int n, m, k, a, b, c;
int dp[2][N];

vector<pair<int,int> > p[12];

int main() {
    while(~scanf("%d%d%d", &n, &m, &k)) {
        memset(dp[0], 0, sizeof dp[0]);
        for (int i = 1; i <= k; i++) p[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &a, &b, &c);
            p[a].emplace_back(b, c);
        }
        for (int i = 1; i <= k; i++) {
            memset(dp[i&1], -1, sizeof dp[0]);
            for (auto q:p[i]) {
                for (int j = m; j >= q.first; j--){
                    if(~dp[i&1][j-q.first])
                        dp[i&1][j] = max(dp[i&1][j], dp[i&1][j-q.first] + q.second);
                    if(~dp[(i-1)&1][j-q.first])
                        dp[i&1][j] = max(dp[i&1][j], dp[(i-1)&1][j-q.first] + q.second);
                }
            }
        }
        if(~dp[k&1][m]) printf("%d\n", dp[k&1][m]);
        else puts("Impossible");
    } return 0;
}
