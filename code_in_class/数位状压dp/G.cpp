#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;

ll dp[30][13][3];
int digit[20];

ll dfs(int pos, int pre, int md, int flag, bool e){
    if(pos==-1) return flag&&md==0;
    if(!e && flag &&  dp[pos][md][2]!=-1) return dp[pos][md][2];
    if(!e && !flag && dp[pos][md][1]!=-1 && pre==1) return dp[pos][md][1];
    if(!e && !flag && dp[pos][md][0]!=-1 && pre!=1) return dp[pos][md][0];
    ll ans = 0;
    int ed = e ? digit[pos] : 9;
    for(int i = 0; i <= ed; i++) {
        ans += dfs(pos-1, i, (md*10+i)%13, flag||(pre==1&&i==3), e&&(i==ed));
    }
    if(!e)dp[pos][md][flag?2:pre==1?1:0] = ans;
    return ans;
}

ll calc(ll n){
    int len=0;
    memset(dp, -1, sizeof dp);
    while(n){
        digit[len++]=n%10;
        n/=10;
    }
    return dfs(len-1, 0, 0, 0, 1);
}

int main(){
    ll n; while(~scanf("%lld",&n)){
        printf("%lld\n",calc(n));
    }
    return 0;
}
