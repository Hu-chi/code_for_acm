#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<utility>
#include<queue>
#define CLR(a,v) memset(a, v, sizeof a)

using namespace std;
int n,m,s,K;

double mp[110][110];
void floyd(){
    for(int i = 0; i < n; i++){
        mp[i][i] = 1.0;
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                mp[i][j] = max(mp[i][j], mp[i][k]*mp[k][j]);
            }
        }
    }
}

int main(){
    int t=0,k;
    scanf("%d",&k);
    while(t++<k){
        scanf("%d%d%d%d",&n,&m,&s,&K);
        CLR(mp,0);
        int u,v;
        double w;
        while(m--){
            scanf("%d%d%lf",&u,&v,&w);
            mp[u][v] = mp[v][u] = w/100.0;
        }
        floyd();
        double ans = 1.0/mp[0][n-1]*2*K*s;
        printf("Case %d: %.7lf\n",t,ans);
    }
    return 0;
}
