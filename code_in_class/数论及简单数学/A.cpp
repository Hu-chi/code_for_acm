#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
#define maxn 10000
using namespace std;
const ll mod =9901;
bool judge[maxn];
ll check[maxn][2];
int prime[maxn/2];
int tot, num;
ll a,b;

void init(){
    tot=0;
    memset(judge, 0, sizeof judge);
    for(int i = 2; i < maxn; i++){
        if(!judge[i]){
            for(int j = i+i; j < maxn; j+=i){
                judge[j]=1;
            }
            prime[tot++]=i;
        }
    }
}

ll multi(ll a, ll b, ll m){
    ll ans = 0;
    a %= m;
    while(b) {
        if(b&1)ans = (ans+a)%m;
        a = (a+a)%m;
        b >>= 1;
    }
    return ans;
}

ll largequickmod(ll p, ll k, ll m){
    ll ans = 1;
    while(k){
        if(k&1) ans = multi(ans,p,m);
        p = multi(p,p,m);
        k>>=1;
    }
    return ans;
}

ll quickmod(ll p, ll k){
    ll ans=1;
    p%=mod;
    while(k){
        if(k&1)ans = ans*p%mod;
        p = (p*p)%mod;
        k>>=1;
    }
    return ans;
}

ll S(ll p, ll k){
    if(p==0)return 0;
    if(k==0)return 1;
    ll temp = quickmod(p,(k>>1))%mod;
    if(k&1){
        return S(p,k>>1)%mod*(1+temp*p%mod)%mod;
    }else{
        return (S(p,(k>>1)-1)%mod*(1+temp*p%mod)%mod+temp)%mod;
    }
}

void Method_one(){
    ll ans = 1;
    for(int i = 0; i < num; i++){
        ans = (ans * S(check[i][0], b*check[i][1]))%mod;
    }
    if(a==0)ans=0;
    printf("%lld\n",ans);
}

void Method_two(){
    ll ans = 1;
    for(int i = 0; i < num; i++){
        ll M = mod*(check[i][0]-1);
        ans *= (largequickmod(check[i][0], check[i][1]*b+1, M)+M-1)/(check[i][0]-1);
        ans %= mod;
    }
    printf("%lld\n",ans);
}

int main(){
    init();
    while(~scanf("%lld%lld",&a,&b)){
        ll temp = a;
        num=0;
        memset(check, 0, sizeof check);
        for(int i = 0; i < tot; i++){
            if(temp<=1)break;
            if(temp%prime[i]==0){check[num++][0]=prime[i];}
            while(temp%prime[i]==0){
                temp/=prime[i];
                check[num-1][1]++;
            }
        }
        if(temp>1){
            check[num][0]=temp;
            check[num++][1]=1;
        }
        //Method_one();
        Method_two();
    }
    return 0;
}
