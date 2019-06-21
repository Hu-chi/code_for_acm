#include <bits/stdc++.h>
const int N = 1e2+9;
using namespace std;
long long mp[N][N], n, m, cnt[N][N];

double ans[N];

int main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j++) {
			mp[i][j] = 1e15;
		}
	}
	long long u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%lld%lld%lld", &u, &v, &w);
		mp[u][v] = min(mp[u][v], w);
		mp[v][u] = mp[u][v];
		cnt[u][v] = cnt[v][u] = 1;
	}
	for (int i = 1; i <= n; i++) {
		mp[i][i] = 0;
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				long long sum_ijk = mp[i][k] + mp[k][j];
				if (sum_ijk < mp[i][j]) {
					mp[i][j] = sum_ijk;
					cnt[i][j] = cnt[i][k] * cnt[k][j];
				} else if (sum_ijk == mp[i][j]) {
					cnt[i][j] += cnt[i][k] * cnt[k][j];
				}
			}
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if(mp[i][j] == mp[i][k] + mp[k][j] && cnt[i][j]) {
					ans[k] += 1. * cnt[i][k] * cnt[k][j] / cnt[i][j];
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%.3f\n", ans[i]);
	}
	return 0;
}