#include<cstdio>
#include<cstring>
#include<iostream>
const int N = 1e3+10;
using namespace std;

struct Edge{ int to, next; }edge[N];
inline int read(){
   int s=0;
   char ch=getchar();
   while(ch<'0'||ch>'9'){ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s;
}

int head[N], pre[N], fa[N], depth[N], cnt[N], tot, n;
bool vis[N];

inline void addEdge(int u, int v){
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}

void dfs(int s){
	vis[s] = 1;
	for(int i = head[s]; i!=-1; i = edge[i].next){
		int to = edge[i].to;
		if(!vis[to]){
			fa[to] = s;
			depth[to] = depth[s] + 1;
			dfs(to);
		}
	}
}

int lca(int x, int y){
	if(depth[x] > depth[y]) swap(x, y);
	while(depth[x] != depth[y]){ y = fa[y]; }
	while(x != y){
		x = fa[x];
		y = fa[y];
	}
	return x;
}
void init(){
    tot=0;
	memset(vis, 0 ,sizeof vis);
	memset(head, -1, sizeof head);
	memset(cnt, 0, sizeof cnt);
	memset(depth, 0 ,sizeof depth);
	for(int i = 0; i <= n; i++){
		pre[i] = i;
	}
}

int Find(int x){
	return x==pre[x]?x:Find(pre[x]);
}

int main(){
	while(~scanf("%d",&n)){
		init();
		int root, num;
		for(int i = 0; i < n; i++){
			root = read();
			num = read();
			int v;
			for(int j = 0; j < num; j++){
				v = read();
				addEdge(root, v);
				pre[v] = pre[root];
			}
		}
		for(int i = 1; i <= n; i++)
			if(pre[i] == i){ dfs(i); break; }
		int u, v, q;
		q = read();
		for(int i = 0; i < q; i++){
		    u = read();
		    v = read();
			cnt[lca(u, v)]++;
		}
		for(int i = 1; i <= n; i++){
			if(cnt[i]){
				printf("%d:%d\n",i,cnt[i]);
			}
		}
	}
	return 0;
}
