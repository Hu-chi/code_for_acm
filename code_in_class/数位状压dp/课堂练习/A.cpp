#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define ll long long
const int N = 1e5+9;
using namespace std;
vector<int> a[20];
int row, n;
ll dp[20][2048];
int mark[N];
const int mod = 1000000001;

void init(int x){
    int base = x;
    row = 0;
    while(base <= n){
        a[row].clear();
        a[row++].push_back(base);
        base *= 2;
    }
    for (int i = 0; i < row; i++){
        int base = a[i][0];
        base *= 3;
        while(base <= n){
            a[i].push_back(base);
            base *= 3;
        }
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < a[i].size(); j++){
            mark[a[i][j]] = 1;
        }
    }
}

ll solve(){
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1<<(a[0].size())); i++){
        if((i&(i<<1)) == 0){
            dp[0][i] = 1;
        }
    }
    for (int i = 1; i <= row; i++){
        for (int j = 0; j < (1<<a[i].size()); j++){
            if(((j&(j<<1)) == 0)){
                for (int k = 0; k < (1<<(a[i-1].size())); k++){
                    if(((k&(k<<1)) == 0)){
                        if(((j<<(a[i-1].size() - a[i].size()))&k)==0){
                            dp[i][j] += dp[i-1][k];
                            dp[i][j] %= mod;
                        }
                    }
                }
            }
        }
    }
    return dp[row][0];
}

int main(){
    scanf("%d",&n);
    ll ans = 1;
    for (int i = 1; i <= n; i++){
        if(mark[i])continue;
        init(i);
        ans = solve()*ans % mod;
    }
    printf("%lld\n",ans);
    return 0;
}
