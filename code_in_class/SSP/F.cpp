#include <bits/stdc++.h>
#define ll long long
const int N = 2e5+9;
using namespace std;

struct Edge {
  int v, nxt, w;
} e[N<<2];
int n, k, cnt, head[N];

inline void ad(int u, int v, int w) {
  e[cnt] = {v, head[u], w};
  head[u] = cnt++;
}

inline void add(int u, int v, int w) {
  ad(u, v, w); ad(v, u, w);
}

bool inq[N];
int vis[N], d[N];
bool spfa(int s) {
  queue<int> q;
  vis[s] = inq[s] = 1; q.push(s);
  while(!q.empty()) {
    int u = q.front(); q.pop(); inq[u] = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(d[v] < d[u] + e[i].w) {
        d[v] = d[u] + e[i].w;
        if(++vis[v] > n) return 0;
        if(!inq[v]) {
          inq[v] = 1;
          q.push(v);
        }
      }
    }
  }
  return 1;
}

int main() {
  memset(head, -1, sizeof head);
  scanf("%d%d", &n, &k);
  int x, a, b;
  int flag = 0;
  for (int i = 0; i < k; i++) {
    scanf("%d%d%d", &x, &a, &b);
    if(a == b) {
      if((x&1)==0) flag = 1;
      continue;
    }
    if(x == 1) add(a, b, 0);
    else if(x == 2) ad(a, b, 1);
    else if(x == 3) ad(b, a, 0);
    else if(x == 4) ad(b, a, 1);
    else ad(a, b, 0);
  }
  if(flag) {
      puts("-1");
      return 0;
  }
  for (int i = n; i; i--) {
    ad(0, i, 1);
  }
  if(!spfa(0)) return puts("-1"), 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += d[i];
  }
  printf("%lld\n", ans);
  return 0;
}
