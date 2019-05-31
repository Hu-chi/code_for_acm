#include <iostream>
#include <cstdio>
#include <cstring>
const int N = 111;
const int M = 1e5+9;
using namespace std;
int n, m, a[N], c[N];

bool dp[M], deq[M];

int main() {
    while(~scanf("%d%d", &n, &m) && n && m) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
        }
        memset(dp, 0, sizeof(bool) * (m+1));
        dp[0] = 1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if(c[i] == 1) {
                for (int v = m; v >= a[i]; v--) {
                    if(!dp[v] && dp[v-a[i]]) {
                        dp[v] = 1; ans++;
                    }
                }
            } else if(a[i]*c[i] >= m) {
                for (int v = a[i]; v <= m; v++) {
                    if(!dp[v] && dp[v-a[i]]) {
                        dp[v] = 1; ans++;
                    }
                }
            } else for (int j = 0; j < a[i]; j++) {
                int s = 0, e = -1, sum = 0;
                for (int v = j; v <= m; v+=a[i]) {
                    if(s + c[i] == e) sum -= deq[s++];
                    deq[++e] = dp[v];
                    sum += dp[v];
                    if(!dp[v] && sum) {
                        dp[v]++; ans++;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
