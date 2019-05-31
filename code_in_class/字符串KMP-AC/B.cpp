#include <cstdio>
#include <cstring>
#include <iostream>
const int N = 1e6+9;
using namespace std;
char s[N], p[N];
int nxt[N], n, m;

void getNxt(){
    int j = 0, k = -1;
    nxt[0] = -1;
    while(j < m){
        if(k==-1 || p[j] == p[k]){
            nxt[j++] = k++;
        }else k = nxt[k];
    }
}

int kmp(){
    int i=0,j=0;
    int ans = 0;
    getNxt();
    while(i<n){
        if(j==-1||s[i]==p[j]){
            i++; j++;
        } else j = nxt[j];
        if(j==m){
            j = nxt[j];
            ans ++;
        }
    }
    return ans;
}

int t;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%s%s",p,s);
        n = strlen(s);
        m = strlen(p);
        printf("%d\n",kmp());
    }
    return 0;
}
