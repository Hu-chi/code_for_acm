#include <bits/stdc++.h>
const int N = 4e5+9;
using namespace std;
using ll = long long;
int n, m, cnt, Time, in[N], out[N], c[N], val[N<<1], head[N<<1];
struct Edge{ int v, nxt; }e[N<<2];
bool vis[N];

void ad(int u, int v) { e[cnt] = {v, head[u]}; head[u] = cnt++; }
void add(int u, int v) { ad(u, v); ad(v, u); }

void dfs(int u) {
	in[u] = ++Time;
	val[Time] = c[u];
	vis[u] = 1;
	for (int i = head[u]; ~i; i=e[i].nxt) {
		int v = e[i].v;
		if(!vis[v]) dfs(v);
	}
	out[u] = Time;
}

struct Node {
	ll num, fg;
} tree[N<<2];

void pushup(int rt) {
	tree[rt].num = tree[rt<<1].num|tree[rt<<1|1].num;
}

void pushdown(int rt) {
	if(tree[rt].fg) {
		tree[rt<<1].num = tree[rt<<1|1].num = (1ll << tree[rt].fg);
		tree[rt<<1].fg = tree[rt<<1|1].fg = tree[rt].fg;
		tree[rt].fg = 0;
	}
}

void build(int rt, int l, int r) {
	tree[rt].fg = 0;
	if(l == r) {
		tree[rt].num = (1ll << val[l]);
		return ;
	}
	int mid = (l + r) >> 1;
	build(rt<<1, l, mid);
	build(rt<<1|1, mid+1, r);
	pushup(rt);
}

void update(int rt, int L, int R, int l, int r, int v) {
	if(l <= L && R <= r) {
		tree[rt].fg = v;
		tree[rt].num = (1ll << v); return ;
	}
	int mid = (L + R) >> 1;
	pushdown(rt);
	if (l <= mid) update(rt<<1, L, mid, l, r, v);
	if (mid < r)  update(rt<<1|1, mid+1, R, l, r, v);
	pushup(rt);
}

ll query(int rt, int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		return tree[rt].num;
	}
	ll ans=0;
	pushdown(rt);
	int mid = (L + R) >> 1;
	if(l <= mid) ans |= query(rt<<1, L, mid, l, r);
	if(mid < r)  ans |= query(rt<<1|1, mid+1, R, l, r);
	return ans;
}

int main() {
	scanf("%d%d", &n, &m); memset(head, -1, sizeof head);
	for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y); add(x, y);
	}
	dfs(1); build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int op, x; ll v;
		scanf("%d%d", &op, &x);
		if(op == 1) {
			scanf("%lld", &v); update(1, 1, n, in[x], out[x], v);
		} else {
			ll ans = query(1, 1, n, in[x], out[x]);
			printf("%d\n", __builtin_popcountll(ans));
		}
	}
	return 0;
}