//#include <bits/stdc++.h>
#include <stdio.h>
#include <cstring>
#define ll long long
//using ll = long long;
int n,m;
const int N = 15;
using namespace std;
int a[N], k;
ll dp[N][1<<N];
int state[1<<N], cnt;
const int mod = 1e8;

void slove(){
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < cnt; j++) {
            if((a[i]& state[j]) != state[j]) continue;
            for (int k = 0; k < cnt; k++){
                if((state[j]&state[k])!=0) continue;
                dp[i][state[j]] = (dp[i-1][state[k]] + dp[i][state[j]]) % mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < cnt; i++){
        ans += dp[n][state[i]];
        ans %= mod;
    }
    printf("%lld\n",ans);
}

void init(){
    cnt = 0;
    for (int i = 0; i < (1<<m); i++){
        if((i&(i<<1)) == 0){
            state[cnt++] = i;
        }
    }
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        memset(dp, 0, sizeof dp);
        init();
        for (int i = 1; i <= n; i++){
            a[i] = 0;
            for (int j = 0; j < m; j++){
                scanf("%d",&k);
                a[i] <<= 1; a[i] += k;
            }
        }
        slove();
    }
    return 0;
}