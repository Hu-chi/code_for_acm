#include <cstdio>
#include <iostream>
#include <cstring>
const int N = 3e5;
using namespace std;

int n, q, s, cnt;
int head[N];
struct Edge{
    int v, w, nxt, id;
}e[N<<1];

inline void ad(int u, int v, int w, int id) {
    e[cnt].v = v; e[cnt].w = w; e[cnt].id = id;
    e[cnt].nxt = head[u]; head[u] = cnt++;
}

inline void add(int u, int v, int w, int id) {
    ad(u, v, w, id); ad(v, u, w, id);
}

int l[N], r[N], tot;
void dfs_x(int u, int fa) {
    l[u] = ++tot;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dfs_x(v, u);
    }
    r[u] = tot;
}

int dep[N], fa[N][20], be_id[N];
void build(int u, int f) {
    dep[u] = dep[fa[u][0]] + 1;
    for (int i = 0; fa[u][i]; i++) {
        fa[u][i+1] = fa[fa[u][i]][i];
    }
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == f) continue;
        be_id[e[i].id] = v;
        fa[v][0] = u;
        build(v, u);
    }
}

int Lca(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    int deep = dep[y] - dep[x];
    for (int i = 0; i < 20; i++) {
        if((1<<i) & deep) {
            y = fa[y][i];
        }
    }
    if(x == y) return x;
    for (int i = 19; ~i; i--) {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int sum[N];
inline int lb(int x) {
    return x & (-x);
}

void add_v(int x, int v) {
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

int w_p[N];
int main() {
    scanf("%d%d%d", &n, &q, &s);
    memset(head, -1, sizeof head);
    int u, v, w, op;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        w_p[i] = w;
        add(u, v, w, i);
    }
    dfs_x(1, 0);
    build(1, 0);
    for (int i = 1; i < n; i++) {
        add_v(l[be_id[i]], w_p[i]);
        add_v(r[be_id[i]]+1, -w_p[i]);
    }
    while(q--) {
        scanf("%d", &op);
        if(op) {
            scanf("%d%d", &u, &w);
            add_v(l[be_id[u]], w-w_p[u]);
            add_v(r[be_id[u]]+1, w_p[u]-w);
            w_p[u] = w;
        } else {
            scanf("%d", &u);
            int lca = Lca(u, s);
            int ans = query(l[u]) + query(l[s]) - 2 * query(l[lca]);
            printf("%d\n", ans);
            s = u;
        }
    }
    return 0;
}
