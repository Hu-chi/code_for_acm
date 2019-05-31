#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#define maxn 6005
/**
则dp[i][0]=dp[i][0]+max(dp[son][0],dp[son][1]) ,原因是上司不出席，下属可出席也可不出席，取个大的。

dp[i][1]=dp[i][1]+dp[son][0]，原因是上司一旦出席，下属绝对不能出席。
**/

using namespace std;
int hap[maxn],f[maxn],dp[maxn][2],head[maxn],tol;
struct edge{
    int to,nxt;
}e[maxn*2];

void addedge(int u, int v){
    e[tol].to = v;
    e[tol].nxt = head[u];
    head[u] = tol++;
}

void dfs(int root){
    dp[root][1] = hap[root];
    for(int i = head[root]; i != -1; i = e[i].nxt){
        dfs(e[i].to);
    }
    for(int i = head[root]; i != -1; i = e[i].nxt){
        dp[root][0] += max(dp[e[i].to][1], dp[e[i].to][0]);
        dp[root][1] += dp[e[i].to][0];
    }
}

int main(){
    int n,u,v;
    while(~scanf("%d",&n) && n){
        memset(f,0,sizeof f);
        memset(dp,0,sizeof dp);
        memset(head, -1, sizeof head);
        for(int i = 1; i <= n; i++)
            scanf("%d",&hap[i]);
        for(int i = 1; i <= n; i++){
            scanf("%d%d",&v,&u);
            if(u==0&&v==0)break;
            f[v] = u;
            addedge(u,v);
        }
        int root=1;tol=0;
        while(f[root])root = f[root];
        dfs(root);
        int ans = max(dp[root][0],dp[root][1]);
        printf("%d\n",ans);
    }
    return 0;
}
