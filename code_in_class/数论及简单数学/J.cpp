#include <cstdio>
#include <algorithm>
#define gcd __gcd
#define ll long long
using namespace std;
const int N = 1e3+9;
int gd[N][N];

void init() {
    for (int i = 1; i < N; i++) {
        gd[i][i] = i;
        for (int j = 0; j < i; j++) {
            gd[i][j] = gd[j][i] = __gcd(i, j);
        }
    }
}

ll n, m;
int main() {
    init();
    scanf("%lld%lld", &n, &m); n++;m++;
    ll nm = n * m;
    ll ans = nm*(nm-1)/2*(nm-2)/3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i||j) {
                if(!i || !j) ans -= (n-i)*(m-j)*(gd[i][j] - 1);
                else     ans -= 2 * (n-i)*(m-j)*(gd[i][j] - 1);
            }
        }
    }
    return printf("%lld\n", ans), 0;
}
