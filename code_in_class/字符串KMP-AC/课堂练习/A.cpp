#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5;
const int MAX_K = 26;
int n;

struct Node{
    int nxt[MAX_K];
    int fail, cnt, id, dep;
    void init(){
        memset(nxt, -1, sizeof nxt);
        fail = -1; cnt = 0; id = 0;
    }
}trie[MAX_N];

int root, num, vis[MAX_N];
int que[MAX_N], head, tail;

void init(){ root=num=0; trie[root].init(); }

inline void inser(const char *s, int id){
    int idx, p = root;
    while(*s){
        idx = *s - 'a';
        if(trie[p].nxt[idx]==-1) {
            trie[++num].init();
            trie[num].dep = trie[p].dep + 1;
            trie[p].nxt[idx] = num;
        }
        p = trie[p].nxt[idx];
        s ++;
    }
    trie[p].cnt++; trie[p].id = id;
}

void AC(){
    int cur,p,son;
    head = tail = 0;
    que[tail++] = root;
    while(head < tail){
        cur = que[head++];
        for(int i = 0; i < MAX_K; i++){
            if(trie[cur].nxt[i]!=-1){
                son = trie[cur].nxt[i];
                p = trie[cur].fail;
                if(cur == root) trie[son].fail = root;
                else trie[son].fail = trie[p].nxt[i];
                que[tail++] = son;
            } else {
                p = trie[cur].fail;
                if(cur == root){
                    trie[cur].nxt[i] = root;
                }
                else trie[cur].nxt[i] = trie[p].nxt[i];
            }
        }
    }
}

void Find(const char *s, int now){
    int p = root, idx, tmp;
    while(*s){
        idx = *s - 'a';
        p = trie[p].nxt[idx];
        if(p==-1) p = root;
        tmp = p;
        while(tmp != root){
            vis[tmp] = now;
            tmp = trie[tmp].fail;
        }
        s ++;
    }
}

int Query(const char *s, int now) {
    int p = root, idx, tmp, ans = 0;
    while(*s) {
        idx = *s - 'a';
        p = trie[p].nxt[idx];
        if(p == -1) p = root;
        tmp = p;
        while(tmp != root) {
            if(vis[tmp] == now) ans = max(ans, trie[tmp].dep);
            tmp = trie[tmp].fail;
        }
        s++;
    }
    return ans;
}

string str[MAX_N];

int main() {
    int t, n, m, x, y; scanf("%d", &t);
    while(t--) {
        memset(vis, 0, sizeof vis);
        scanf("%d", &n); init();
        for (int i = 0; i < n; i++) {
            cin >> str[i];
            inser(str[i].c_str(), i);
        } AC(); scanf("%d", &m);
        int now = 0;
        while(m--) {
            scanf("%d%d", &x, &y); x --; y --; now ++;
            Find(str[x].c_str(), now);
            int ans = Query(str[y].c_str(), now);
            printf("%d\n", ans);
        }
    }
}
