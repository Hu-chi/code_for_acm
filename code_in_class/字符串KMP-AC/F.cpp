#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6+9;
const int mod = 1e9+7;
int nxt[N], dep[N];
void getAns(char *p){
    int m = strlen(p);
    int i = 0, j = -1;
    nxt[i] = -1; dep[i] = 0;
    ll ans = 1;
    while(i < m) {
        if (j==-1||p[i]==p[j]) {
            i++; j++;
            dep[i] = dep[j]+1;
            nxt[i] = j;
        } else j = nxt[j];
    }
    i = 0, j = -1;
    while(i < m) {
        if(j == -1 || p[i] == p[j]) {
            i++; j++;
            while(j != -1 && (j << 1) > i) j = nxt[j];
            if(j != -1) ans = ans * (dep[j] + 1) % mod;
        } else j = nxt[j];
    }
    printf("%lld\n", ans);
}

int n;
char s[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        memset(dep, 0, sizeof dep);
        scanf("%s", s);
        getAns(s);
    }
}
