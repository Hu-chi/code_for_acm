#include <bits/stdc++.h>
const int N = 1111;
const int INF = 1e6+9;
using namespace std;
int n, m, head[N], cnt, dp[N];
int F;

struct Edge{ int v, w, nxt; }e[N<<2];
inline void ad(int u, int v, int w) { e[cnt] = {v, w, head[u]}; head[u]=cnt++; }
inline void add(int u, int v, int w) { ad(u, v, w); ad(v, u, w); }

bool dfs(int u, int fa) {
    dp[u] = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if(e[i].v == fa) continue;
        dfs(e[i].v, u);
        if(dp[e[i].v] == 0) {
            if(e[i].w <= F)dp[u] += e[i].w;
            else dp[u] += INF;
        } else if(e[i].w > F) {
            dp[u] += dp[e[i].v];
        } else {
            dp[u] += min(dp[e[i].v], e[i].w);
        }
    }
    return 1;
}

bool check(int mid) {
    F = mid;
    if(!dfs(1, 0)) return 0;
    return dp[1] <= m;
}

int main() {
    while(~scanf("%d%d", &n, &m) && n) {
        memset(head, -1, sizeof(int) * (n+1));
        cnt = 0;
        for (int i = 1; i < n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }
        int l = 0, r = m+1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(check(mid)) r = mid - 1;
            else l = mid + 1;
        }
        if(r+1<=m)printf("%d\n", r+1);
        else puts("-1");
    }
    return 0;
}
