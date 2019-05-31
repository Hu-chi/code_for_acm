#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#define ll long long
using namespace std;
const int N = 11;
int state[1<<N], a[102], num[1<<N];
ll dp[102][100][100];
int n,m,cnt;

void init(){
    cnt = 0;
    for (int i = 0; i < (1<<m); i++){
        if((i&(i<<1)) == 0 && (i&(i<<2)) == 0){
            state[cnt++] = i;
            int tmp = i;
            num[i] = __builtin_popcount(i);
        }
    }
}

void slove() {
    for (int i = 2; i <= n+1; i++) {
        for (int j = 0; j < cnt; j++) {
            if((a[i]& state[j]) != state[j]) continue;
            for (int k = 0; k < cnt; k++) {
                if((state[j]&state[k])!=0) continue;
                if((a[i-1]& state[k]) != state[k]) continue;
                for (int t = 0; t < cnt; t++) {
                    if((state[t]&(state[k]|state[j]))!=0 ) continue;
                    if((a[i-2]& state[t]) != state[t]) continue;
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][k][t] + num[state[j]]);
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < cnt; i++)
        ans = max(ans, *max_element(dp[n+1][i], dp[n+1][i]+cnt));
    printf("%lld\n",ans);
}
char s[N];
int main(){
    while(~scanf("%d%d",&n,&m)){
        memset(dp, 0, sizeof dp);
        init();
        for (int i = 2; i <= n+1; i++){
            a[i] = 0;
            scanf("%s",&s);
            for (int j = 0; j < m; j++){
                a[i] <<= 1; a[i] |= (s[j] == 'P');
            }
        }
        slove();
    }
    return 0;
}
