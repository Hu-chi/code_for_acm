#include <bits/stdc++.h>
const int inf = 1e9+9;
using namespace std;

int t1,t2,tmp,ans;
int a[5],b[5];
struct data{ int a[5]; };
data cal(int *a, int k) {
    data ans;
    int t1 = a[2] - a[1], t2 = a[3] - a[2];
    for(int i = 1; i <= 3; i++)
        ans.a[i] = a[i];
    if(t1 == t2)
        return ans;
    if(t1 < t2) {
        int t = min(k, (t2 - 1)/t1);
        k -= t; tmp += t;//顺便记录深度
        ans.a[2] += t * t1;
        ans.a[1] += t * t1;
    } else {
        int t = min(k, (t1 - 1)/t2);
        k -= t; tmp += t;
        ans.a[2] -= t * t2;
        ans.a[3] -= t * t2;
    }
    if(k) return cal(ans.a, k);//辗转相除
    else return ans;
}

bool operator!=(data a, data b) {
    for(int i = 1; i <= 3; i++) {
        if(a.a[i] != b.a[i])
            return 1;
    }
    return 0;
}
int main() {
    for (int i = 1; i <= 3; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= 3; i++) {
        scanf("%d", &b[i]);
    }
    sort(a+1,a+4); sort(b+1,b+4);
    data t1 = cal(a, inf); int d1 = tmp; tmp = 0;
    data t2 = cal(b, inf); int d2 = tmp; tmp = 0;
    //t1,t2分别为a,b的根，d1,d2为深度
    if(t1 != t2) { return puts("NO"), 0; }
    if(d1 > d2) {
        swap(d1,d2);
        for(int i=1;i<=3;i++)
            swap(a[i],b[i]);
    }
    ans = d2 - d1;
    t1=cal(b, ans);
    for(int i=1;i<=3;i++) {
        b[i]=t1.a[i];
    }
    int l = 0, r = d1;
    while(l <= r) {
        int mid= l + r >> 1;
        if(cal(a,mid) != cal(b,mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("YES\n%d", ans + 2 * l);
    return 0;
}
