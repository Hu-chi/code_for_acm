#include <bits/stdc++.h>
const int N = 25;
using namespace std;
double t[N], p;

int main() {
    while(~scanf("%lf", &p)) {
        t[1] = 1 / p;
        t[2] = 1 / p + 1 / p / p;
        for (int k = 3; k <= 20; k++) {
          t[k] = 1 / p + t[k-1] / p - (1 - p) / p * t[k-3];
        }
        printf("%.6f\n", t[19] + t[20]);
    }
    return 0;
}
