#include <bits/stdc++.h>

const int N = 3e5+9;
const int inf = 1e9;
using namespace std;
int n, m, cnt, head[N];

struct Egde {
  int v, nxt, w;
} e[N<<2];

inline void ad(int u, int v, int w) {
  e[cnt] = {v, head[u], w};
  head[u] = cnt++;
}

inline void add(int u, int v, int w) {
  ad(u, v, w); ad(v, u, w);
}

struct Node {
  int x, y, id;
} p[N];

bool cmpx(Node a, Node b) {
  return a.x < b.x;
}

bool cmpy(Node a, Node b) {
  return a.y < b.y;
}

int d[N];
int dijkstra(int s, int t) {
  for (int i = 0; i <= n; i++) {
    d[i] = inf;
  }
  d[s] = 0;
  priority_queue<pair<int, int> > q;
  q.push({-d[s], s});
  while(!q.empty()) {
    pair<int, int> tp = q.top(); q.pop();
    int u = tp.second;
    for (int i = head[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(d[v] > d[u] + e[i].w) {
        d[v] = d[u] + e[i].w;
        q.push({-d[v], v});
      }
    }
  }
  return d[t];
}

int main() {
  scanf("%d", &n);
  memset(head, -1, sizeof head);
  int a, b;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a, &b);
    p[i].x = a; p[i].y = b;
    p[i].id = i;
  }
  sort(p, p+n, cmpx);
  for (int i = 1; i < n; i++) {
    add(p[i-1].id, p[i].id, abs(p[i-1].x - p[i].x));
  }
  sort(p, p+n, cmpy);
  for (int i = 1; i < n; i++) {
    add(p[i-1].id, p[i].id, abs(p[i-1].y - p[i].y));
  }
  int ans = dijkstra(0, n-1);
  printf("%d\n", ans);
  return 0;
}
