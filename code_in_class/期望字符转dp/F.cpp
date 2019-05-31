#include <bits/stdc++.h>
#define ll long long
const int N = 2e5+9;
const int mod = 1e9+7;
using namespace std;
int v[N], in[N], n, m, k;
ll qp(ll a, int k) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        in[a]++; in[b]++;
    }
    ll inv = qp(2*m, mod-2);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + k * v[i] % mod * in[i] % mod) % mod;
    }
    printf("%lld\n", ans * inv % mod);
    return 0;
}
