#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf = 1LL<<60;
const int N = 5e5+9;
struct Edge{
    int v,nxt;
}e[N<<1];

int head[N];
ll a[N], sum[N], dp[N], ans;
int n,u,v,cnt;
void ad(int u, int v){ e[cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt++; }
void add(int u, int v){ ad(u, v); ad(v, u); }

void dfs(int s, int fa){
    sum[s] = a[s];
    for (int i = head[s]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa)continue;
        dfs(v, s);
        sum[s] += sum[v];
        if(dp[s] > -inf)ans = max(ans, dp[s] + dp[v]);
        dp[s] = max(dp[s], dp[v]);
    }
    dp[s] = max(dp[s], sum[s]);
}

int main(){
    scanf("%d",&n);
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; i++) scanf("%lld",&a[i]), dp[i] = -inf;
    for (int i = 1; i < n; i++) {
        scanf("%d%d",&u,&v);
        add(u, v);
    }
    ans = -inf;
    dfs(1, -1);
    if(ans <= -inf)puts("Impossible");
    else printf("%lld\n",ans);
}
