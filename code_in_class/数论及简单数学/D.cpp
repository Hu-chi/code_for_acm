#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;

const int N = 1e3;
ll C[N][N];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

ll CC(ll n, ll m) {
    if(m*2 > n) m = n - m;
    ll ans = 1, b = 1;
    for (int i = 1; i <= m; i++) {
        ans *= n - i + 1;
        b *= i;
        if(ans % b == 0) {
            ans /= b;
            b = 1;
        }
    }
    return ans;
}

int main() {
    init();ll n, m;
    while(~scanf("%lld%lld", &n, &m) && !(n==0&&m==0)) {
        n = n + m;
        if(n < N) printf("%lld\n", C[n][m]);
        else printf("%lld\n", CC(n, m));
    }
}
