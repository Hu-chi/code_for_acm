#include <bits/stdc++.h>
const int N = 2e4+9;
const int inf = 1e7;
using namespace std;

int k, n;
char s[N];
int nxt[N], num[N];

int getAns(char *p, int len) {
    int i = 0, j = -1;
    nxt[i] = j;
    int ans = 0;
    while(i < len) {
        if(j == -1 || p[i] == p[j]) {
            nxt[++i] = ++j;
            if(j < k) num[i] = inf;
            else num[i] = min(j, num[j]);
            if(num[i]*2 < i) ans++;
        } else j = nxt[j];
    }
    return ans;
}

int main() {
    scanf("%s%d", s, &k);
    if(k == 0) return printf("%d\n", n*(n+1)/2), 0;
    int n = strlen(s);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += getAns(s+i, n-i);
    }
    printf("%d\n", ans);
}
