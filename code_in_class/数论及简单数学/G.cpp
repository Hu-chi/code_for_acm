#include <cstdio>
#include <iostream>
#define ll long long
using namespace std;
int p, q, r, s;
int main() {
    while(~scanf("%d%d%d%d", &p, &q, &r, &s)) {
        double ans = 1;
        q = min(q, p - q);
        s = min(s, r - s);
        for (int i = 0; i < max(q, s); i++) {
            if(i < q) {
                ans *= (p - i);
                ans /= i+1;
            }
            if(i < s) {
                ans /= (r - i);
                ans *= i+1;
            }
        }
        printf("%.5f\n", ans);
    } return 0;
}
