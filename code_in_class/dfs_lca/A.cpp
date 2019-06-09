#include <cstdio>
#include <cstring>
#include <vector>
const int N = 1e5+999;
using namespace std;

int n, u, v, tot, l[N], r[N], q;
vector<vector<int> > e(N);
bool has[N];

int a[N];
inline int lb(int x) { return x & (-x); }

inline void add(int x, int v) {
    for (int i = x; i < N; i += lb(i)) {
        a[i] += v;
    }
}

inline int query(int x) {
    int ans = 0;
    for (int i = x; i; i -= lb(i)) {
        ans += a[i];
    }
    return ans;
}

void dfs(int u, int fa) {
    l[u] = ++tot;
    for (int i = 0; i < e[u].size(); i++) {
        int v = e[u][i];
        if(v == fa) continue;
        dfs(v, u);
    }
    r[u] = tot;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        add(l[i], 1);
    }
    scanf("%d", &q);
    char ch[3];
    while(q--) {
        scanf("%s%d", ch, &u);
        if(ch[0] == 'Q') {
            printf("%d\n", query(r[u]) - query(l[u]-1));
        } else {
            add(l[u], (int)has[u]*2-1);
            has[u] ^= 1;
        }
    }
    return 0;
}
