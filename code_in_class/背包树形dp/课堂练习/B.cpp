#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5+9;
const int mod = 1e9+7;
int n,cnt;
int head[N], c[N];

struct Node{ int v,nxt; }e[N<<2];
inline void ad(int u, int v){ e[cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt++; }
inline void add(int u, int v){ ad(u, v);ad(v, u); }

ll dp[N][2];
void dfs(int s, int fa){
    dp[s][c[s]] = 1;
    for (int i = head[s]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(v == fa)continue;
        dfs(v, s);
        dp[s][1] = (dp[s][1]*(dp[v][0]+dp[v][1])%mod + dp[s][0]*dp[v][1])%mod;
        dp[s][0] = dp[s][0]*(dp[v][0]+dp[v][1])%mod;
    }
}

int main(){
    scanf("%d",&n);
    memset(head, -1, sizeof head);
    int u, v;
    for (int i = 1; i < n; i++){
        scanf("%d",&u);
        add(i+1, u+1);
    }
    for (int i = 1; i <= n; i++){
        scanf("%d",&c[i]);
    }
    dfs(1, -1);
    printf("%lld\n",dp[1][1]);
}
