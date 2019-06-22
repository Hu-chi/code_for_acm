#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf = 1e16;
const int N = 15;
const int M = 5e5;
int n, a[N], cnt, head[M];
ll b_min, b_max;

struct Edge {
  int v, nxt, w;
} e[M*N];

void ad(int u, int v, int w) {
  e[cnt] = {v, head[u], w};
  head[u] = cnt++;
}

ll d[M];
bool vis[M];
void dijkstra(int s) {
  priority_queue<pair<ll, int> >q;
  for (int i = 0; i < M; i++) d[i] = inf; d[s] = 0;
  q.push({-d[s], s});
  while(!q.empty()) {
    pair<ll, int> tp = q.top(); q.pop();
    int u = tp.second;
    if(vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(d[v] > d[u] + e[i].w) {
        d[v] = d[u] + e[i].w;
        q.push({-d[v], v});
      }
    }
  }
}

int main() {
  memset(head, -1, sizeof head);
  scanf("%d%lld%lld", &n, &b_min, &b_max);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a, a+n);
  for (int i = 0; i < a[0]; i++) {
    for (int j = 1; j < n; j++) {
      ad(i, (a[j] + i) % a[0], a[j]);
    }
  }
  dijkstra(0);
  ll ans = 0;
  for (int i = 0; i < a[0]; i++) {
    if(d[i] <= b_max) {
      ll l = max(0LL, (b_min - d[i]) / a[0]);
      if(l * a[0] + d[i] < b_min) l ++;
      ll r = (b_max - d[i]) / a[0];
      if(r * a[0] + d[i] > b_max) r --;
      ans += r - l + 1;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
