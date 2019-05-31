#include <iostream>
#include <cstdio>
#include <cstring>
#define abs(x) (x>0?x:-x)
const int N = 450 * 100 + 9;
using namespace std;

int dp[101][N], a[N], n;

int main() {
    int sum=0, half_n, half_sum;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    half_n = (n+1) >> 1;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int k = half_n; k; k--)
            for (int j = sum; j >= a[i]; j--)
                if(dp[k-1][j-a[i]]) dp[k][j] = 1;

    int x, y, xy = 1e9;
    for (int i = sum; ~i; i--) {
        if(dp[half_n][i] && xy > abs(i*2-sum)) {
            xy = abs(i*2 - sum);
            x = min(i, sum - i);
            y = max(i, sum - i);
        }
    }
    printf("%d %d\n", x, y);
}
