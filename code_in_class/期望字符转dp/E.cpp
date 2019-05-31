#include <bits/stdc++.h>
const int M = 1<<16;
const int N = 133;
using namespace std;
int v[N], s[N], p[N], n, k, t;
double dp[N][M];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= 16; i++) p[i] = 1 << (i - 1);
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &v[i], &t);
        while(t) {
            s[i] += p[t];
            scanf("%d", &t);
        }
    }
    for (int i = n; i; i--) {
        for (int j = 0; j < p[k+1]; j++) {
            for (int q = 0; q < k; q++) {
                if((s[q]&j) == s[q])
                    dp[i][j] += max(dp[i+1][j], dp[i+1][j|p[q+1]]+v[q]);
                else dp[i][j] += dp[i+1][j];
            }
            dp[i][j] /= k;
        }
    }
    printf("%.6f\n", dp[1][0]);
    return 0;
}
