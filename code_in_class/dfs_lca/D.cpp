#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
const int N = 5e4+9;
const int inf = 1e9;
const int M = 22;
using namespace std;

int depth[N], fa[N][M], mxp[N][M], mnp[N][M], mxi[N][M];
int head[N], cnt, n;
int w[N];
struct Edge{ int v, nxt; } e[N<<1];
inline void ad(int u, int v) {
    e[cnt].v = v; e[cnt].nxt = head[u];
    head[u] = cnt++;
}

inline void add(int u, int v) {
    ad(u, v); ad(v, u);
}

inline void init() {
    memset(head, -1, sizeof head);
}

struct State{
    int fa, mx, mi, dx, sx;
} s[N][M];


void build(int u, int fa) {
    depth[u] = depth[s[u][0].fa] + 1;
    for (int i = 0; s[u][i].fa; i++) {
        s[u][i+1].fa = s[s[u][i].fa][i].fa;
        s[u][i+1].mx = max(s[u][i].mx, s[s[u][i].fa][i].mx);
        s[u][i+1].mi = min(s[u][i].mi, s[s[u][i].fa][i].mi);
        s[u][i+1].sx = max(max(s[u][i].sx, s[s[u][i].fa][i].sx), s[u][i].mx - s[s[u][i].fa][i].mi);
        s[u][i+1].dx = max(max(s[u][i].dx, s[s[u][i].fa][i].dx),-s[u][i].mi + s[s[u][i].fa][i].mx);
    }
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(fa == v) continue;
        s[v][0].fa = u;
        s[v][0].mx = max(w[v], w[u]);
        s[v][0].mi = min(w[v], w[u]);
        s[v][0].sx = w[v] - w[u];
        s[v][0].dx = w[u] - w[v];
        build(v, u);
    }
}

int Lca(int x, int y) {
    if(depth[x] > depth[y]) swap(x, y);
    int deep = depth[y] - depth[x];
    for (int i = 0; i < M; i++) {
        if((1<<i)&deep)
            y = s[y][i].fa;
    }
    if(x == y) return x;
    for (int i = M-1; ~i; i--) {
        if(s[y][i].fa != s[x][i].fa) {
            y = s[y][i].fa;
            x = s[x][i].fa;
        }
    }
    return s[x][0].fa;
}

int solve(int x, int y) {
    int lca = Lca(x, y);
    if(x == y) {
        return 0;
    }
    int deep = depth[x] - depth[lca];
    int ans = 0, mx = -1, mi = inf;
    if(deep>0) {
        for (int i = 0; i < M; i++) {
            if((1<<i)&deep) {
                ans = max(ans, s[x][i].dx);
                ans = max(ans, s[x][i].mx - mi);
                mi = min(mi, s[x][i].mi);
                x = s[x][i].fa;
            }
        }
    }
    deep = depth[y] - depth[lca];
    if(deep>0) {
        for (int i = 0; i < M; i++) {
            if((1<<i)&deep) {
                ans = max(ans, s[y][i].sx);
                ans = max(ans, mx - s[y][i].mi);
                mx = max(mx, s[y][i].mx);
                y = s[y][i].fa;
            }
        }
    }
    ans = max(ans, mx - mi);
    return ans;
}

int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    int u, v, q;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    s[1][0].mx = s[1][0].mi = w[1];
    build(1, 0);
    scanf("%d", &q);
    while(q--) {
        scanf("%d%d", &u, &v);
        printf("%d\n", solve(u, v));
    } return 0;
}
