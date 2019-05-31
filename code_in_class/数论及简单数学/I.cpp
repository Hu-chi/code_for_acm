#include <cstdio>
#include <iostream>
const int N = 4e5+9;
using namespace std;

int s[N], x, y, len;

void mul(int num) {
    int c = 0, t;
    for(int i = 0; i < len; ++i) {
        t = s[i] * num + c;
        s[i] = t % 10;
        c = t / 10;
    }
    while(c != 0) {
        s[len++] = c % 10;
        c /= 10;
    }
}

int cnt[N];

void add(int x, int v) {
    for (int i = 2; i*i <= x; i++) {
        while(x % i == 0) {
            cnt[i] += v;
            x /= i;
        }
    }
    if(x>1) cnt[x] += v;
}

int main() {
    scanf("%d%d", &x, &y);
    x = x + y;
    for (int i = y+1; i <= x; i++) {
        add(i, 1);
    }
    for (int i = 2; i <= x - y + 1; i++) {
        add(i, -1);
    }
    add(x-2*y+1, 1);
    s[0] = 1; len = 1;
    for (int i = 2; i <= x; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            mul(i);
        }
    }
    for (int i = len-1; ~i; i--) {
        printf("%d", s[i]);
    }
    puts("");
}
