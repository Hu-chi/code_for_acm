#include <cstdio>
#include <cstring>
const int N = 1.6e7+9;
using namespace std;
char s[N];
bool has[N], vis[256];
int n, nc, a[256], m, cnt;

int main(){
    scanf("%d%*d%s",&m,s); n = strlen(s);
    for (int i = 0; i < n; i++) {
        if(!vis[s[i]]) {
            vis[s[i]] = 1; a[s[i]]=nc++;
        }
    } int ans = 0, x = 0, y = 1;
    for (int i = 0; i < m; i ++) {
        x = x*nc + a[s[i]];
        y *= nc;
    } y/= nc; has[x] = 1; ans ++;
    for (int i = 1; i <= n-m; i++) {
        x = (x - a[s[i-1]]*y)*nc + a[s[i+m-1]];
        if(!has[x]) has[x] = 1, ans++;
    } return printf("%d\n", ans), 0;
}
