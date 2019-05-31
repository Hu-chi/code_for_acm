#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
const int N = 27;
using namespace std;
char s[N];
ll C[N][N];
int len;

void init() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

bool check(char *s, int len) {
    for (int i = 1; i < len; i++) {
        if(s[i] <= s[i-1]) return 0;
    }
    return 1;
}

ll dfs(char *s, int idx, int pre=0) {
    ll ans = 0;
    if(idx == len) return s[idx]-'a'-pre+1;
    for (int i = pre; i < s[idx]-'a'; i++) {
        ans += C[25 - i][len - idx];
    }    ans += dfs(s, idx+1, s[idx]-'a'+1);
    return ans;
}

int main() {
    init();
    scanf("%s", s+1);
    len = strlen(s+1);
    if(!check(s+1, len)) { return puts("0"), 0; }
    ll ans = dfs(s, 1);
    for (int i = 1; i < len; i++) ans += C[26][i];
    printf("%lld\n", ans);
    return 0;
}
