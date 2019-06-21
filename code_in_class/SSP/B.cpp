#include <bits/stdc++.h>
const int N = 1e4+9;
using namespace std;
int n, m, k, s, t, head[N], cnt, d[N][12];
const int inf = 1e9;
struct Edge {
	int v, nxt, w;
} e[N<<4];

inline void ad(int u, int v, int w) {
	e[cnt] = {v, head[u], w};
	head[u] = cnt++;
}

inline void add(int u, int v, int w) {
	ad(u, v, w); ad(v, u, w);
}

struct Node {
	int dis, id, t;
	bool operator<(const Node& a) const {
		return dis > a.dis;
	}
};

int dijkstra(int s, int t) {
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= 11; j++)
			d[i][j] = inf;
	d[s][0] = 0;
	priority_queue<Node> q;
	q.push({d[s][0], s, 0});
	while(!q.empty()) {
		Node tp = q.top(); q.pop();
		int u = tp.id;
		for (int i = head[u]; ~i; i = e[i].nxt) {
			int v = e[i].v;
			if(d[v][tp.t+1] > d[u][tp.t] && tp.t < k) {
				d[v][tp.t+1] = d[u][tp.t];
        q.push({d[v][tp.t+1], v, tp.t+1});
			}
			if(d[v][tp.t] > d[u][tp.t] + e[i].w) {
				d[v][tp.t] = d[u][tp.t] + e[i].w;
				q.push({d[v][tp.t], v, tp.t});
			}
		}
	}
	int mi = inf;
	for (int i = 0; i <= k; i++) {
    mi = min(mi, d[t][i]);
	}
	return mi;
}

int main() {
	memset(head, -1, sizeof head);
	scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
	int u, v, w;
	for (int i = 1; i <= m ; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
	}
	int ans = dijkstra(s, t);
	printf("%d\n", ans);
	return 0;
}
