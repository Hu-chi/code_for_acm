#include <bits/stdc++.h>

using namespace std;
const int N = 3e5+9;
const int M = 1e6+9;

int dp[M<<3], a[N], bin[25], n;

int main() {
    bin[0] = 1;
    for(int i = 1; i <= 22; i++) {
        bin[i] = bin[i-1] << 1;
    }
	scanf("%d", &n);
	memset(dp, 0x3f, sizeof(dp));
	for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] ^= a[i-1];
        dp[a[i]] = min(dp[a[i]], i);
	}
	for(int i = 2 * M; i >= 0; i--) {
		for(int j = 21; j >= 0; j--) {
            if(i & bin[j]) {
                dp[i^bin[j]] = min(dp[i^bin[j]], dp[i]);
            }
		}
	}
    printf("%d\n", a[1]);
	for(int i = 2; i <= n; i++) {
		int ans = 0, now = 0;
		for(int j = 21; j >= 0; j--) {
			if(a[i] & bin[j]) {
                ans += bin[j];
			} else if(dp[now|bin[j]] <= i) {
                ans += bin[j+1];
                now |= bin[j];
			}
		}
        printf("%d\n", ans);
	}
	return 0;
}