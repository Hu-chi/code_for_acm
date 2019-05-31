#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5;
const int MAX_K = 26;
int n;

struct Node{
    int nxt[MAX_K];
    int fail, cnt, id;
    void init(){
        memset(nxt, -1, sizeof nxt);
        fail = -1; cnt = 0; id = 0;
    }
}trie[MAX_N];

int root, num;
int que[MAX_N], head, tail;
char str[MAX_N*20];
char in[1001][52];

void init(){ root=num=0; trie[root].init(); }

inline void inser(char *s, int id){
    int idx, p = root;
    while(*s){
        idx = *s - 'A';
        if(trie[p].nxt[idx]==-1){
            trie[++num].init();
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

int cal_cnt[1001];

void Find(char *s){
    int p = root, cnt = 0, idx, tmp;
    while(*s){
        idx = *s - 'A';
        if(idx >= 0 && idx < MAX_K) {
            p = trie[p].nxt[idx];
            if(p==-1) p = root;
        } else p = root;
        tmp = p;
        while(tmp != root && trie[tmp].cnt){
            cal_cnt[trie[tmp].id]++;
            tmp = trie[tmp].fail;
        }
        s ++;
    }
}

int main(){
    while(~scanf("%d",&n)){
        init();
        for(int i = 0; i < n; i++){
            scanf("%s", in[i]);
            inser(in[i], i);
        }
        AC();
        scanf("%s", str);
        Find(str);
        for (int i = 0; i < n; i++) {
            if(cal_cnt[i]) {
                printf("%s: %d\n", in[i], cal_cnt[i]);
            }
        }
        memset(cal_cnt, 0, sizeof cal_cnt);
    }
}
