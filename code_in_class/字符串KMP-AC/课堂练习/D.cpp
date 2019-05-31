#include <cstdio>
#include <iostream>
#include <cstring>
const int maxn = 1e3+9;
using namespace std;
char p[maxn], s[maxn];
int nxt[maxn];
int n,m;

void getNxt(){
    int i = 0, j = -1;
    nxt[i] = -1;
    while(i<m){
        if(j==-1||p[i]==p[j]){
            i++;
            j++;
            nxt[i] = j;
        }else j = nxt[j];
    }
}

int kmp(){
    int i=0,j=0;
    int ans = 0;
    getNxt();
    while(i<n){
        if(j==-1 || s[i] == p[j]){
            i++;
            j++;
        }else j = nxt[j];
        if(j == m){
            j = 0;
            ans ++;
        }
    }
    return ans;
}

int main(){
    while(~scanf("%s",s)){
        n = strlen(s);
        if(s[0]=='#') break;
        scanf("%s",p);
        m = strlen(p);
        printf("%d\n",kmp());
    }
    return 0;
}
