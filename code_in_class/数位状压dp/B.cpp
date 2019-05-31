#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;

ll bin[35];
ll c[33][33]={0};
void init(){
    for (int i = 0; i < 33; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
        }
    }
}

void T_to_bin(ll n){
    bin[0] = 0;
    while(n){
        bin[++bin[0]] = n&1;
        n>>=1;
    }
}

ll calc(ll v){
    ll sum = 0;
    T_to_bin(v);
    for(int i = 1; i < bin[0]-1; i++){
        for(int j = i/2+1; j <= i; j++){
            sum+=c[i][j];
        }
    }
    int zero = 0;//从高位向低位搜索过程中的0
    for(int i = bin[0]-1; i>=1; i--){
        if(bin[i])for(int j = (bin[0]+1)/2-(zero+1); j < i; j++)
            sum += c[i-1][j];
        else zero++;
    }
    return sum;
}

int main(){
    init();
    ll st,ed;
    scanf("%lld%lld",&st,&ed);
    printf("%lld\n",calc(ed+1)-calc(st));
    return 0;
}
