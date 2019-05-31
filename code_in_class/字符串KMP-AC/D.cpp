#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_LEN = 233;
const int MAX_N = 3e4+9;

int N, L, S;

char s[MAX_N][MAX_LEN];
ull base[MAX_LEN], v[MAX_N], c_v[MAX_N];

int main() {
    scanf("%d%d%d", &N, &L, &S);
    base[0] = 1; int ans = 0;
    for (int i = 1; i < MAX_LEN; i++) base[i] = base[i-1] * 131;
    for (int i = 0; i < N; i++) {
        scanf("%s", s[i]);
        v[i] = 0;
        for (int j = 0; j < L; j++) {
            v[i] = v[i] * base[1] + s[i][j];
        }
    }
    for (int j = 0; j < L; j++) {
        for (int i = 0; i < N; i++) {
            c_v[i] = v[i] - s[i][j] * base[L-1 - j];
        }
        sort(c_v, c_v + N);
        int tmp = 1;
        for (int i = 1; i < N; i++) {
            if(c_v[i] == c_v[i-1]) {
                ans += tmp ++;
            } else tmp = 1;
        }
    } return printf("%d\n", ans), 0;
}
