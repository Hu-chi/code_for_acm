#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;

void e_gcd(ll a, ll b, ll &d, ll &x, ll &y){
    if(!b){
        d = a; x = 1; y = 0;
    }else{
        e_gcd(b, a%b, d, y, x);
        y -= (a/b)*x;
    }
}

int main(){
    ll x,y,m,n,l;
    while(~scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&l)){
        ll a,b,d,ans,x1,y1;
        e_gcd(m-n, -l, d, x1, y1);
        //printf("%lld:%lld:%lld\n",d,x1,y1);
        if((y-x)%d!=0){
            puts("Impossible");
        }else{
            x1 *= (y-x)/d;
            l /= -d;
            x1 %= l;
            if(x1 < 0)x1+=l;
            printf("%lld\n",x1);
        }
    }
}
