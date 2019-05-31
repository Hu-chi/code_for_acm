#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 1e6;
const int maxk = 26;
struct Node{
    int nxt[26];
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
char w[60], str[maxn];

void init(){
    root=num=0;
    trie[root].init();
}

inline void inser(char *s){
    int idx, p = root;
    while(*s) {
        idx = *s - 'a';
        if(trie[p].nxt[idx]==-1) {
            trie[++num].init();
            trie[p].nxt[idx] = num;
        }
        p = trie[p].nxt[idx];
        s ++;
    }
    trie[p].cnt++;
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

int Find(char *s){
    int p = root, cnt = 0, idx, tmp;
    while(*s) {
        idx = *s - 'a';
        p = trie[p].nxt[idx];
        if(p==-1) p = root;
        tmp = p;
        while(tmp != root && trie[tmp].cnt){
            cnt += trie[tmp].cnt;
            trie[tmp].cnt = 0;
            tmp = trie[tmp].fail;
        }
        s ++;
    }
    return cnt;
}

int n;
int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        getchar();
        for(int i = 0; i < n; i++){
            gets(w);
            inser(w);
        }
        AC();
        gets(str);
        printf("%d\n",Find(str));
    }
}
