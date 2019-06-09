#include<cstdio>
#include<iostream>
#include<cstring>
const int N = 2e4;
using namespace std;
int n;

int head[N],fa[N], depth[N], pre[N], tot;
bool vis[N];
struct Edge{ int to, next; } edge[N*2];

void addEdge(int u, int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int s){
    vis[s] = 1;
    for(int i = head[s]; i != -1; i = edge[i].next){
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
    while(x!=y){
        x = fa[x];
        y = fa[y];
    }
    return x;
}

void init(){
    memset(vis, 0, sizeof vis);
    memset(head, -1, sizeof head);
    for(int i = 0; i <= n; i++){ pre[i] = i; }
}

int Find(int x){
    return x==pre[x]?x:Find(pre[x]);
}

int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        int u, v;
        for(int i = 1; i < n; i++){
            scanf("%d%d",&u, &v);
            addEdge(u, v);
            pre[v] = Find(u);
        }
        for(int i = 1; i <= n; i++){
            if(pre[i] == i) dfs(i);
        }
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u, v));
    }
}
