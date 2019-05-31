#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll dp[21][11], a, b;
int digit[21];

ll dfs(int pos, int v, bool edge, bool zero) {
    if(pos==-1) return 1;
    if(!edge && ~dp[pos][v]) return dp[pos][v];
    int ed = edge ? digit[pos] : 9;
    ll ans = 0;
    for (int i = 0; i <= ed; i++) {
        if(abs(i-v)>=2 || zero) {
            ans += dfs(pos-1, i, edge && i == ed, zero&&i==0);
        }
    }
    if(!edge && !zero) dp[pos][v] = ans;
    return ans;
}

ll cal(ll x){
    memset(dp, -1, sizeof dp);
    int pos = 0;
    while(x) {
        digit[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1, 0, 1, 1);
}

int main(){
    scanf("%lld%lld",&a,&b);
    printf("%lld\n",cal(b) - cal(a-1));
    return 0;
}
