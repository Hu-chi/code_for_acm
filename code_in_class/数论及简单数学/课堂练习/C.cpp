#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
typedef long long ll;
using namespace std;

int qmod(long long n , long long k){
    ll res = 1;
    while(k>0){
        if(k&1)res=(res*n)%1000;
        n = (n*n)% 1000;
        k >>= 1;
    }
    return res%1000;
}

int qlog(long long n, long long k){
    double a = log10(n+0.0)*k;
    if(a<=3)return pow(10,a);
    a-=(ll) a;
    int ans = pow(10.0,a)*1000;
    while(ans>=1000){ans/=10;}
    return ans;
}

int main(){
    int T,t=0;
    scanf("%d",&T);
    ll n,k;
    while(t++<T){
        scanf("%lld%lld",&n,&k);
        printf("Case %d: %03d %03d\n",t,qlog(n,k),qmod(n,k));
    }
    return 0;
}
