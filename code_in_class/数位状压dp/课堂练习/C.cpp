#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
int digit[20];
ll dp[20][5000];//前缀和不大于presum满足条件的个数
ll a,b;

ll dfs(int pos, int remain, bool e){
    if(pos==-1)return remain>=0;
    if(remain<0)return 0;
    if(!e && dp[pos][remain]!=-1) return dp[pos][remain];
    int ed = e?digit[pos]:9;
    ll ans=0;
    for(int i = 0; i <= ed; i++){
        ans += dfs(pos-1, remain - i*(1<<pos), e&&(i==ed));
    }
    if(!e) dp[pos][remain] = ans;
    return ans;
}

int f(ll n){
    int ans =0,t=-1;
    while(n){
        ans+=(n%10)*(1<<++t);
        n/=10;
    }
    return ans;
}

ll calc(ll n){
    int len = 0;
    while(n){
        digit[len++] = n%10;
        n/=10;
    }
    return dfs(len-1, f(a),1);
}

int main(){
    int T,t=0;scanf("%d",&T);
    memset(dp, -1, sizeof dp);
    while(t++<T){
        scanf("%lld%lld",&a,&b);
        printf("Case #%d: %lld\n",t,calc(b));
    }
}
