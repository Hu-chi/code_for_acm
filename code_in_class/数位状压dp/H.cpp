#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
#define CL(a,v) memset(a,v,sizeof a)
using namespace std;

const int Mod = 2520;
ll dp[21][Mod][50];
int digit[21];
int indx[Mod+5];

void init() {
    int num = 0;
    for(int i = 1; i <= Mod; i++){
        if(Mod%i == 0)indx[i] = num++;
    }
    CL(dp,-1);
}

ll gcd(ll a, ll b){
    return b==0? a : gcd(b, a%b);
}

ll lcm(ll a, ll b){
    return a/gcd(a,b)*b;
}

ll dfs(int pos, int presum, int prelcm, bool edge){
    if(pos==-1) return presum%prelcm == 0;
    if(!edge && dp[pos][presum][indx[prelcm]] != -1){
        return dp[pos][presum][indx[prelcm]];
    }
    int ed = edge ? digit[pos] : 9;
    ll ans = 0;
    for(int i = 0; i <= ed; i++){
        int nowlcm = prelcm;
        int nowsum = (presum*10 + i)%Mod;
        if(i) nowlcm = lcm(prelcm, i);
        ans += dfs(pos-1, nowsum, nowlcm, edge && i == ed);
    }
    if(!edge) dp[pos][presum][indx[prelcm]] = ans;
    return ans;
}

ll cal(ll x){
    CL(digit, 0);
    int pos = 0;
    while(x){
        digit[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1, 0, 1 ,1);
}

int main(){
    init();
    ll a,b;
    int t;scanf("%d",&t);
    while(t--){
        scanf("%I64d%I64d",&a,&b);
        printf("%I64d\n",cal(b) - cal(a-1));
    }
    return 0;
}
