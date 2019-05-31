#include <cstdio>
#include <iostream>
const int N = 1e5+9;
const int INF = 1e9+9;
using namespace std;
int dp[N<<1];
int n, s, f;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < (N<<1); i++)
        dp[i] = -INF;
    dp[N] = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &s, &f);
        if(s < 0 && f < 0) continue;
        if(s > 0) {
            for (int j = (N<<1)-1; j >= s; j--) {
                if(dp[j-s] > -INF)
                    dp[j] = max(dp[j], dp[j-s]+f);
            }
        } else {
            for (int j = s; j < (N<<1)+s; j++) {
                if(dp[j-s] > -INF)
                    dp[j] = max(dp[j], dp[j-s]+f);
            }
        }
    }
    int ans = 0;
    for (int i = N; i < (N<<1); i++) {
        if(dp[i]>=0)
            ans = max(ans, dp[i]+i-N);
    }
    printf("%d\n", ans);
}
