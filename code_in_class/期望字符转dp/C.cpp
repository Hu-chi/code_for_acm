#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1e5;
const int maxk = 5;
const int inf = 1e9;
struct Node{
    int nxt[maxk];
    int fail;
    int cnt;
    void init(){
        memset(nxt, -1, sizeof nxt);
        fail = -1;
        cnt = 0;
    }
}trie[maxn];

int root, num;
int que[maxn], head, tail;

void init(){
    root=num=0;
    trie[root].init();
}

inline void inser(char *s){
    int idx, p = root;
    while(*s) {
        idx = *s - 0;
        if(trie[p].nxt[idx]==-1) {
            trie[++num].init();
            trie[p].nxt[idx] = num;
        }
        p = trie[p].nxt[idx];
        s ++;
    }
    trie[p].cnt=1;
}

void AC() {
    int cur,p,son;
    head = tail = 0;
    que[tail++] = root;
    while(head < tail) {
        cur = que[head++];
        for(int i = 0; i < maxk; i++) {
            if(trie[cur].nxt[i]!=-1) {
                son = trie[cur].nxt[i];
                p = trie[cur].fail;
                while(p != -1) {
                    if(trie[p].nxt[i] != -1) {
                        trie[son].fail = trie[p].nxt[i];
                        trie[son].cnt |= trie[trie[p].nxt[i]].cnt;
                        break;
                    }
                    p = trie[p].fail;
                }
                if(cur == root) trie[son].fail = root;
                else trie[son].fail = trie[p].nxt[i];
                que[tail++] = son;
            } else {
                p = trie[cur].fail;
                if(cur == root) {
                    trie[cur].nxt[i] = root;
                } else trie[cur].nxt[i] = trie[p].nxt[i];
            }
        }
    }
}

int n, T;
int dp[1010][1010];
char s[1022];
int main(){
    while(~scanf("%d",&n) && n){
        init();
        for (int i = 0; i <= n; i++) {
            scanf("%s", s);
            for (int j = 0; s[j]; j++) {
                if(s[j] == 'A') s[j] = 1;
                if(s[j] == 'C') s[j] = 2;
                if(s[j] == 'G') s[j] = 3;
                if(s[j] == 'T') s[j] = 4;
            }
            if(i != n) inser(s);
        }
        AC();
        int len = strlen(s);
        memset(dp, 0x3f, sizeof dp);
        dp[0][0] = 0;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j <= num; j++) {
                for (int k = 1; k <= 4; k++) {
                    int nxt_id = trie[j].nxt[k];
            //        cout << i << j << k << " " << nxt_id << " " << trie[nxt_id].cnt << endl;
                    if(nxt_id < 0 || trie[nxt_id].cnt > 0) continue;
                    dp[i+1][nxt_id] = min(dp[i][j] + (s[i] != k), dp[i+1][nxt_id]);
            //        cout << dp[i+1][nxt_id] << endl;
                }
            }
        }
        int ans = inf;
        for (int i = 0; i <= num; i++) {
            ans = min(ans, dp[len][i]);
        }
        printf("Case %d: %d\n", ++T, ans<inf?ans:-1);
    }
}
