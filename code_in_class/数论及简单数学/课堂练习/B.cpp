#include<cstdio>
#include<iostream>
#define  ll unsigned long long
const ll inf = ~0;
using namespace std;
ll ans ;
bool judge[1000];
int prime[1000];
int n,cnt=0;

void dfs(int depth, ll tmp, int num){
    if(num > n || depth>=cnt)return;
    if(num == n && ans>tmp){
        ans = tmp;
        return;
    }
    for(int i= 1; i <= 63; i++){
        if(ans/prime[depth]<tmp || num*(i+1)>n)break;
        dfs(depth+1, tmp*=prime[depth], num*(i+1));
    }
}

int main(){
        for(int i = 2; i<100; i++) {
        if(!judge[i]) {
            for(int j = i+i; j<100; j+=i) {
                judge[j] = 1;
            }
            prime[cnt++] = i;
        }
    }
    while(~scanf("%d",&n)){
        ans = inf;
        dfs(0,1,1);
        printf("%llu\n", ans);
    }
}
