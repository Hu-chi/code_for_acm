#include <cstring>
#include <cstdio>
#include <iostream>
const int N = 2e5+9;
using namespace std;
int n, m, cnt;
int head[N];
struct Edge{
    int v, nxt;
} e[N<<1];

inline void ad(int u, int v) {
    e[cnt].v = v; e[cnt].nxt = head[u];
    head[u] = cnt ++;
}

inline void add(int u, int v) {
    ad(u, v); ad(v, u);
}

int dep[N], fa[N][20];
void build(int u) {
    dep[u] = dep[fa[u][0]] + 1;
    for (int i = 0; fa[u][i]; i++) {
        fa[u][i+1] = fa[fa[u][i]][i];
    }
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(!dep[v]) {
            fa[v][0] = u;
            build(v);
        }
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
    for (int i = 20-1; ~i; i--) {
        if(fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

int s[N];
void dfs(int u, int fa) {
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dfs(v, u);
        s[u] += s[v];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof head);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    build(1);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        s[u]++; s[v]++;
        s[Lca(u, v)] -= 2;
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if(s[i] == 0) {
            ans += m;
        } else if(s[i] == 1) {
            ans ++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
