#include <bits/stdc++.h>
const int N = 2e3+9;
using namespace std;
int n, dp[N][N];
pair<int, int> a[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }
    sort(a+1, a+1+n, greater<pair<int,int> >());
    int ans = 0;
    memset(dp, -0x3f, sizeof dp);
    dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][max(0, j-a[i].first)+1] + a[i].second);
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
}
