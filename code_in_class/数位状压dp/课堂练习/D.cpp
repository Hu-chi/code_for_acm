#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
ll digit[20];
ll dp[20][60000];
ll a,b;

int getnew(int x, int s){
    int temp = s;
    for(int i = 0; i < x; i++){
        temp/=3;
    }
    if(temp%3<2)return s+(int)pow(3,x);
    else return s - (int)pow(3,x);
}

bool judge(int s){
    int cont = 0;
    while(s){
        if(s%3==1+(++cont)%2)return false;
        s/=3;
    }
    return true;
}

ll dfs(int pos, int s, bool e, bool z){
    if(pos == -1)return judge(s);
    if(!e && dp[pos][s]!=-1)return dp[pos][s];
    ll ans = 0;
    int ed = e?digit[pos]:9;
    for(int i = 0; i <= ed; i++){
        ans += dfs(pos-1,(z&&i==0)?0:getnew(i,s), e&&i==ed, z&&i==0);
    }
    if(!e) dp[pos][s]=ans;
    return ans;
}

ll calc(ll n){
    int len = 0;
    while(n){
        digit[len++] = n%10;
        n/=10;
    }
    return dfs(len-1, 0, 1, 1);
}

int main(){
    int t;scanf("%d",&t);
    memset(dp,-1,sizeof dp);
    while(t--){
        scanf("%lld%lld",&a,&b);
        printf("%lld\n",calc(b)-calc(a-1));
    }
    return 0;
}
