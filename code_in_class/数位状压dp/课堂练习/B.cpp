#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
int n, m, u, w;
int v[13], dp[1<<13][13][13];
bool mp[13][13];
ll num[1<<13][13][13];

void slove(){
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if(!mp[i][j]) continue;
            dp[(1<<i)|(1<<j)][i][j] = dp[(1<<i)|(1<<j)][j][i] = v[i]+v[j]+v[i]*v[j];
            num[(1<<i)|(1<<j)][i][j] = num[(1<<i)|(1<<j)][j][i] = 1;
        }
    }
    for (int s = 0; s < (1<<n); s++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(dp[s][i][j] == -1) continue;
                for (int k = 0; k < n; k++) {
                    if(s&(1<<k)) continue;
                    if(!mp[j][k]) continue;
                    int tmp = dp[s][i][j] + v[k] + v[j]*v[k] + mp[i][k]*v[i]*v[j]*v[k];
                    if(dp[s|(1<<k)][j][k] < tmp){
                        dp[s|(1<<k)][j][k] = tmp;
                        num[s|(1<<k)][j][k] = num[s][i][j];
                    } else if(dp[s|(1<<k)][j][k] == tmp) {
                        num[s|(1<<k)][j][k] += num[s][i][j];
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans = max(ans, dp[(1<<n)-1][i][j]);
        }
    }
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(ans == dp[(1<<n)-1][i][j]) cnt+=num[(1<<n)-1][i][j];
        }
    }
    printf("%d %lld\n", ans, cnt/2);
}

int main(){
    int t;scanf("%d", &t);
    while(t -- ){
        memset(mp, 0, sizeof mp);
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", &v[i]);
        for (int i = 0; i < m; i++){
            scanf("%d%d", &u, &w);u--;w--;
            mp[u][w] = mp[w][u] = 1;
        } if(n==1) {
            printf("%d 1\n", v[0]);
            continue;
        }
        memset(dp, -1, sizeof dp);
        memset(num, 0, sizeof num);
        slove();
    }
}
