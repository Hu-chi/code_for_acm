#include <iostream>
#include <cstdio>
#define ll long long

ll qp(ll a, ll k, ll mod) {
    ll ans = 1;
    while(k) {
        if(k&1) ans = ans * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return ans;
}

int main() {
    int t, m, h, a, b; scanf("%d", &t);
    while(t--) {
        ll ans = 0;
        scanf("%d%d", &m, &h);
        for (int i = 0; i < h; i++) {
            scanf("%d%d", &a, &b);
            ans += qp(a, b, m);
            ans %= m;
        }
        printf("%lld\n", ans);
    }
}
