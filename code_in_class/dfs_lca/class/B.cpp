#include <bits/stdc++.h>
using namespace std;

#define met(a, b) memset(a, b, sizeof(a))
#define N 100053
#define INF 0x3f3f3f3f

typedef long long LL;

struct node {
    int Index, val;
    node(){}
    node(int Index, int val) : Index(Index), val(val){}
};

int v[N], n, ans[N], Time, Node[N];
vector<vector<int> >G;
vector<vector<node> >Q;

int Find(int val) {
    int L = 1, R = Time, ans = Time;
    while(L<=R) {
        int Mid = (L+R)>>1;
        if(v[Node[Mid]] >= val) {
            R = Mid-1;
            ans = Mid;
        }
        else L = Mid+1;
    } return Node[ans];
}

void dfs(int u) {
    Node[++Time] = u;
    int len = Q[u].size();
    for(int i=0; i<len; i++) {
        node p = Q[u][i];
        ans[p.Index] = Find(p.val);
    }
    for(int i=0, L=G[u].size(); i<L; i++)
        dfs(G[u][i]);
    Time--;
}

int main() {
    int T, q, t = 1;
    scanf("%d", &T);
    while(T--) {
        met(v, 0);
        v[0] = 1;
        scanf("%d %d", &n, &q);
        G.clear();
        G.resize(n+5);
        Q.clear();
        Q.resize(n+5);
        int f, u, num;
        for(int i=1; i<n; i++) {
            scanf("%d %d", &f, &v[i]);
            G[f].push_back(i);
        }
        for(int i=1; i<=q; i++) {
            scanf("%d %d", &u, &num);
            Q[u].push_back(node(i, num));
        }
        Time = 0;
        dfs(0);
        printf("Case %d:\n", t++);
        for(int i=1; i<=q; i++)
            printf("%d\n", ans[i]);
    } return 0;
}
