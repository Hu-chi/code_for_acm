/*
也就是说在DP时候，要重建每个数，算出平方，然后求和。
使用结构体
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll mod = 1e9+7;
struct status{
    ll cnt, sum, sqsum;
    status(){cnt=-1;sum=sqsum=0;}
    status(ll a, ll b, ll c){
        cnt = a; sum = b; sqsum = c;
    }
}dp[20][10][10];

ll a,b;
ll digit[20],p[25];

status dfs(int pos, int sum, int md, bool e){
    if(pos==-1) return (sum!=0&&md!=0) ? status(1,0,0):status(0,0,0);
    if(!e && dp[pos][sum][md].cnt!=-1) return dp[pos][sum][md];
    status ans = status(0,0,0);
    int ed = e?digit[pos]:9;
    for(int i = 0; i <= ed; i++){
        if(i==7) continue;
        status next = dfs(pos-1, (sum+i)%7, (md*10+i)%7, e&&i==ed);
        ans.cnt += next.cnt;
        ans.cnt %= mod;
        ans.sum += (next.sum + ((p[pos]*i)%mod) * next.cnt % mod )%mod;
        ans.sum %= mod;

        ans.sqsum += (next.sqsum + ((2*p[pos]*i)%mod)*next.sum)%mod;
        ans.sqsum %= mod;
        ans.sqsum += (next.cnt*p[pos])%mod*p[pos]%mod*i*i%mod;
        ans.sqsum %= mod;
    }
    if(!e)dp[pos][sum][md] = ans;
    return ans;
}

ll calc(ll n){
    int len = 0;
    while(n){
        digit[len++] = n%10;
        n/=10;
    }
    return dfs(len-1, 0, 0, 1).sqsum;
}

int main(){
    int t;scanf("%d",&t);
    p[0] = 1;
    for(int i = 1; i <= 20; i++) p[i]=(p[i-1]*10)%mod;
    while(t--){
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",((calc(b)-calc(a-1))%mod+mod)%mod);
    }
}
