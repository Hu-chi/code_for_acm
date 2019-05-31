#include <bits/stdc++.h>

using namespace std;
const int N = 1e4+9;
int dp[N];

int main() {
    int T, n, m, p, w; scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &p, &m, &n);
        memset(dp, -1, sizeof dp); dp[p] = 0;
        for (int i = 0; i < n; i++){
            scanf("%d%d", &w, &p);
            for (int j = p; j <= m; j++) {
                if(dp[j-p]!=-1) {
                    if(dp[j]==-1) dp[j] = dp[j-p] + w;
                    else dp[j] = min(dp[j], dp[j-p]+w);
                }
            }
        }
        if(dp[m]==-1) puts("This is impossible.");
        else printf("The minimum amount of money in the piggy-bank is %d.\n", dp[m]);
    } return 0;
}
