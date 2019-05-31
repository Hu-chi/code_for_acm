#include <cstdio>
int n, k;
int main() {
    while(~scanf("%d%d", &n, &k)) {
        printf("%d\n", (n&k)==k);
    }
}
