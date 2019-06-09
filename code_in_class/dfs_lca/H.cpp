#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <bits/stdc++.h>
#define ll long long
const int N = 1e5+9;
const ll inf = 0x3f3f3f3f3f3f3f3f;
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

ll val[N], dis[N];
int l[N], r[N], id[N], tot;
void dfs_x(int u, int fa) {
    l[u] = ++tot;
    id[tot] = u;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa) continue;
        dis[v] = dis[u] + val[v];
        dfs_x(v, u);
    }
    r[u] = tot;
}

void init() {
    cnt = tot = 0;
    memset(head, -1, sizeof head);
    memset(l, 0, sizeof l);
    memset(r, 0, sizeof r);
    memset(dis, 0, sizeof dis);
    memset(id, 0, sizeof id);
}

namespace sgt {
    struct ST{
        ll mx, ad;
    }tr[N<<2];
    void push_up(int rt) {
        tr[rt].mx = max(tr[rt<<1].mx, tr[rt<<1|1].mx);
    }
    void push_down(int rt) {
        if(tr[rt].ad) {
            tr[rt<<1].ad += tr[rt].ad;
            tr[rt<<1].mx += tr[rt].ad;
            tr[rt<<1|1].ad += tr[rt].ad;
            tr[rt<<1|1].mx += tr[rt].ad;
            tr[rt].ad = 0;
        }
    }
    void build(int l, int r, int rt) {
        tr[rt].ad = 0;
        if(l == r) {
            tr[rt].mx = dis[id[l]];
            return ;
        }
        int mid = l + r >> 1;
        build(l, mid, rt<<1);
        build(mid+1, r, rt<<1|1);
        push_up(rt);
    }
    void update(int L, int R, int l, int r, int rt, ll val) {
        if(L <= l && r <= R) {
            tr[rt].ad += val;
            tr[rt].mx += val;
            return ;
        }
        int mid = l + r >> 1;
        push_down(rt);
        if(L <= mid) update(L, R, l, mid, rt<<1, val);
        if(mid < R) update(L, R, mid+1, r, rt<<1|1, val);
        push_up(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if(L <= l && r <= R) {
            return tr[rt].mx;
        }
        int mid = l + r >> 1;
        push_down(rt);
        ll ans = -inf;
        if(L <= mid) ans = max(ans, query(L, R, l, mid, rt<<1));
        if(mid < R) ans = max(ans, query(L, R, mid+1, r, rt<<1|1));
        return ans;
    }
}
int n, m;

int main() {
    int t,T=0; scanf("%d", &t);
    while(t--) {
        printf("Case #%d:\n", ++T);
        scanf("%d%d", &n, &m);
        init();
        int u, v, op;
        for (int i = 1; i < n; i ++) {
            scanf("%d%d", &u, &v); u++; v++;
            add(u, v);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &val[i]);
            dis[i] = val[i];
        }
        dfs_x(1, 0);
        sgt::build(1, n, 1);
        ll w;
        for (int i = 0; i < m; i ++) {
            scanf("%d%d", &op, &u); u++;
            if(op) {
                printf("%lld\n", sgt::query(l[u], r[u], 1, tot, 1));
            } else {
                scanf("%lld", &w);
                sgt::update(l[u], r[u], 1, tot, 1, w - val[u]);
                val[u] = w;
            }
        }
    } return 0;
}
