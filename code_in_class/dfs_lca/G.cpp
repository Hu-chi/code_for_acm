#include <cstdio>
#include <cstring>
#include <iostream>
#define pa pair<int,int>
#define ll long long
const int inf = 1e9+9;
using namespace std;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int bin[15];
int T, n, cnt, P;
int last[10005];
int bl[10005], pos[10005], to[10005];
int fa[10005][14], siz[10005], deep[10005];
struct edge{ int to,next,v; }e[20005];
struct seg{ int l,r,mn,mx,tag; }t[40005];
void solve(int &x,int &y) {
	int t = x; x = -y; y = -t;
}

void add(int u,int v,int w) {
	e[++cnt].to = v; e[cnt].next = last[u];
	last[u] = cnt; e[cnt].v = w;
	e[++cnt].to = u; e[cnt].next = last[v];
	last[v] = cnt; e[cnt].v = w;
}

void update(int k) {
	t[k].mn = min(t[k<<1].mn, t[k<<1|1].mn);
	t[k].mx = max(t[k<<1].mx, t[k<<1|1].mx);
}

void pushdown(int k) {
	int l = t[k].l, r = t[k].r;
	if(l == r || !t[k].tag) return;
	t[k].tag=0;
	t[k<<1].tag ^= 1; t[k<<1|1].tag ^= 1;
    solve(t[k<<1].mn, t[k<<1].mx);
	solve(t[k<<1|1].mn, t[k<<1|1].mx);
}

void build(int k,int l,int r) {
	t[k].l = l; t[k].r = r; t[k].tag = 0;
	t[k].mn = inf; t[k].mx = -inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(k<<1, l, mid);
	build(k<<1|1, mid+1, r);
}

void change(int k,int x,int val) {
	pushdown(k);
	int l = t[k].l, r = t[k].r, mid = l + r >> 1;
	if(l == r) {
		t[k].mn = t[k].mx = val;
		return;
	}
	if(x <= mid) change(k<<1, x, val);
	else change(k<<1|1, x, val);
	update(k);
}

void rever(int k,int x,int y) {
	pushdown(k);
	int l = t[k].l, r = t[k].r, mid = l + r >> 1;
	if(l == x && r == y) {
	    solve(t[k].mn, t[k].mx);
		t[k].tag=1; return;
	}
	if(y <= mid) rever(k<<1, x, y);
	else if(x > mid) rever(k<<1|1, x, y);
	else rever(k<<1, x, mid), rever(k<<1|1, mid+1, y);
	update(k);
}

int query(int k,int x,int y) {
	pushdown(k);
	int l = t[k].l, r = t[k].r, mid = l + r >> 1;
	if(x == l && y == r) return t[k].mx;
	if(y <= mid) return query(k<<1, x, y);
	else if(x>mid)return query(k<<1|1, x, y);
	else return max(query(k<<1, x, mid), query(k<<1|1, mid+1, y));
}
void dfs1(int x) {
	siz[x]=1;
	for(int i=1;i<=13;i++)
		if(bin[i]<=deep[x])
			fa[x][i]=fa[fa[x][i-1]][i-1];
		else break;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0]) {
			deep[e[i].to]=deep[x]+1;
			fa[e[i].to][0]=x;
			dfs1(e[i].to);
			siz[x]+=siz[e[i].to];
		}
}

void dfs2(int x,int chain) {
	bl[x]=chain;pos[x]=++P;
	int k=0;
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0]) {
			if(siz[e[i].to]>siz[k])k=e[i].to;
		} else {
			to[i>>1]=pos[x];change(1,pos[x],e[i].v);
		}
	if(!k)return;
	dfs2(k,chain);
	for(int i=last[x];i;i=e[i].next)
		if(e[i].to!=fa[x][0]&&e[i].to!=k)
			dfs2(e[i].to,e[i].to);
}

int lca(int x,int y) {
	if(deep[x]<deep[y])swap(x,y);
	int t=deep[x]-deep[y];
	for(int i=0;i<=13;i++)
		if(t&bin[i])x=fa[x][i];
	for(int i=13;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	if(x==y)return x;
	return fa[x][0];
}

int solvequery(int x,int f) {
	int mx = -inf;
	while(bl[x] != bl[f]) {
		mx = max(mx,query(1,pos[bl[x]],pos[x]));
		x=fa[bl[x]][0];
	}
	if(pos[f]+1<=pos[x])
		mx = max(mx,query(1,pos[f]+1,pos[x]));
	return mx;
}

void solverever(int x, int f) {
	while(bl[x] != bl[f]) {
		rever(1, pos[bl[x]], pos[x]);
		x = fa[bl[x]][0];
	}
	if(pos[f] + 1 <= pos[x])
		rever(1, pos[f] + 1, pos[x]);
}

int main() {
	bin[0]=1;for(int i=1;i<15;i++)bin[i]=bin[i-1]<<1;
	T=read();
	while(T--) {
		P=0;cnt=1;
		memset(last, 0, sizeof(last));
		memset(deep, 0, sizeof(deep));
		memset(fa, 0, sizeof(fa));
		n = read();
		for (int i = 1; i < n; i++) {
			int u = read(), v = read(), w = read();
			add(u, v, w);
		}
		build(1,1,n);
		dfs1(1);
		dfs2(1,1);
		char ch[10];
		while(scanf("%s",ch+1)) {
			if(ch[1] == 'D') break;
			int x = read(), y = read();
			if(ch[1] == 'Q') {
				int f = lca(x, y);
				printf("%d\n", max(solvequery(x, f), solvequery(y, f)));
			} else if (ch[1] == 'C') {
				change(1, to[x], y);
			} else if (ch[1] == 'N') {
				int f = lca(x, y);
				solverever(x, f);
				solverever(y, f);
			}
		}
	}
	return 0;
}
