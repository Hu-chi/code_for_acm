#include <cstdio>
#include <iostream>
#include <algorithm>
const int N = 15;
using namespace std;
int n;
int mp[N][N], fa[N];

int main(){
    while(~scanf("%d",&n) &&n){
        for (int i = 0; i <= n; i++){
            for (int j = 0; j <= n; j++){
                scanf("%d",&mp[i][j]);
            }
        }
        for (int k = 0; k <= n; k++){
            for (int i = 0; i <= n; i++){
                for (int j = 0; j <= n; j++){
                    mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
                }
            }
        }
        for (int i = 0; i <= n; i++){
            fa[i] = i;
        }
        fa[n+1] = 0;
        int ans = 0x3f3f3f3f;
        do{
            int tmp = 0;
            for (int i = 1; i <= n+1; i++){
                tmp += mp[fa[i-1]][fa[i]];
            }
            ans = min(ans, tmp);
        } while(next_permutation(fa+1, fa+n+1));
        printf("%d\n", ans);
    }
    return 0;
}
