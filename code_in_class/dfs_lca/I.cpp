#include <bits/stdc++.h>
const int N = 1e5+9;
using namespace std;

int head[N], cnt;
struct Edge{ int v, nxt; } e[N<<2];

inline void ad(int u, int v) {
    e[cnt].v = v; e[cnt].nxt = head[u];
    head[u] = cnt++;
}

inline void add(int u, int v) {
    ad(u, v); ad(v, u);
}

int l[N], r[N], id[N], tot;
void dfs_x(int u, int fa) {
    l[u] = ++tot;
    id[tot] = u;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dfs_x(v, u);
    }
    r[u] = tot;
}

int sum[N];
inline int lb(int x) {
    return x & (-x);
}

void update(int x, int v) {
    for (int i = x; i < N; i += lb(i)) {
        sum[i] += v;
    }
}

int query(int x) {
    int ans = 0;
    for (int i = x; i; i -= lb(i)) {
        ans += sum[i];
    }
    return ans;
}

void init() {
    memset(head, -1, sizeof head);
    memset(sum, 0, sizeof sum);
    cnt = tot = 0;
}

int n, p;
int main() {
    while(~scanf("%d%d", &n, &p) && n) {
        init();
        int u, v;
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            add(u, v);
        }
        dfs_x(p, 0);
        int ans;
        for (int i = 1; i <= n; i++) {
            ans = query(r[i]) - query(l[i] - 1);
            printf("%d%c", ans, " \n"[i==n]);
            update(l[i], 1);
        }
    }
    return 0;
}
