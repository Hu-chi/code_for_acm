#include <bits/stdc++.h>
const int N = 3e5+9;
const long long inf = 1e16+9;
using namespace std;
int n, m, k, cnt, head[N];

struct Edge{
  int v, nxt;long long w;
} e[N<<2];

inline void ad(int u, int v, long long w) {
  e[cnt] = {v, head[u], w};
  head[u] = cnt++;
}

inline void add(int u, int v, long long w) {
  ad(u, v, w); ad(v, u, w);
}

bool vis[N];
vector<int> ans;
long long d[N];int pre[N];
void dijkstra(int s) {
  priority_queue<pair<long long, int> > q;
  int cntt = 0;
  for (int i = 0; i <= n; i++) d[i] = inf;
  d[s] = 0; q.push({-d[s], s}); pre[s] = -1;
  while(!q.empty() && cntt < k) {
    pair<long long, int> tp = q.top(); q.pop();
    int u = tp.second;
    if(vis[u]) continue;
    if(u != s) { ans.push_back(pre[u]); cntt ++; }
    vis[u] = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(d[v] > d[u] + e[i].w) {
        d[v] = d[u] + e[i].w;
        pre[v] = i/2+1;
        q.push({-d[v], v});
      }
    }
  }
}

int main() {
  memset(head, -1, sizeof head);
  scanf("%d%d%d", &n, &m, &k);
  int x, y, w;
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &x, &y, &w);
    add(x, y, w);
  }
  dijkstra(1);
  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  } puts("");
  return 0;
}
