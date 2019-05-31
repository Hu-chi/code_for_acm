#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using ull = unsigned long long;
const ull base = 1e9+9;
const int N = 4e4+9;
using namespace __gnu_pbds;
using namespace std;
int n, m, ans2, pos;
ull bit[N], h[N];
char s[N];
inline void init() { bit[0] = 1; for(int i = 1; i < N; i++) bit[i]=bit[i-1]*base; }
gp_hash_table<ull, int> cnt;
inline bool check(int x){
    cnt.clear(); pos = 0;
    for (int i = x; i <= n; i++) {
        ull tmp = h[i] - h[i-x]*bit[x];
        if(++cnt[tmp]>=m) pos=i-x+1;
    } return pos;
}
int main(){
    init();
    while(~scanf("%d", &m) && m) {
        scanf("%s", s+1); n = strlen(s+1);
        for (int i = 1; i <= n; i++) {
            h[i]=h[i-1]*base+s[i];
        } int l=1,r=n,ans1=0;
        while(l<=r) {
            int mid = (l+r)>>1;
            if(check(mid)) {
                l = mid + 1; ans1 = mid; ans2 = pos;
            } else r = mid - 1;
        } if(ans1) printf("%d %d\n", ans1, ans2-1);
        else puts("none");
    } return 0;
}
