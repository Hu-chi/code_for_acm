#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1e5;
const int maxk = 131;
struct Node{
    int nxt[maxk];
    int fail, cnt, id;
    void init(){
        memset(nxt, -1, sizeof nxt);
        fail = -1;
        cnt = 0;
        id = 0;
    }
}trie[maxn];

int root, num;
int que[maxn], head, tail;
char w[60], str[maxn];

void init(){
    root=num=0;
    trie[root].init();
}

inline void inser(char *s, int id){
    int idx, p = root;
    while(*s){
        idx = *s - '\0';
        if(trie[p].nxt[idx]==-1){
            trie[++num].init();
            trie[p].nxt[idx] = num;
        }
        p = trie[p].nxt[idx];
        s ++;
    }
    trie[p].cnt++;
    trie[p].id = id;
}

void AC(){
    int cur,p,son;
    head = tail = 0;
    que[tail++] = root;
    while(head < tail){
        cur = que[head++];
        for(int i = 0; i < maxk; i++){
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

vector<int> ans;
int Find(char *s){
    ans.clear();
    int p = root, cnt = 0, idx, tmp;
    while(*s){
        idx = *s - '\0';
        p = trie[p].nxt[idx];
        if(p==-1) p = root;
        tmp = p;
        while(tmp != root){
            if(trie[tmp].cnt>0) {
                ans.push_back(trie[tmp].id);
                cnt++;
                if(cnt == 3) return 3;
            }
            tmp = trie[tmp].fail;
        }
        s ++;
    }
    return cnt;
}

char s[maxn];
int n;
int main(){
    scanf("%d",&n);
    init();
    for(int i = 0; i < n; i++){
        scanf("%s",s);
        inser(s, i+1);
    }
    AC();
    scanf("%d",&n);
    int total = 0;
    for(int i = 0; i < n; i++){
        scanf("%s", s);
        Find(s);
        if(ans.size() == 0) continue;
        total ++;
        printf("web %d:",i+1);
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++)
            printf(" %d",ans[i]);
        puts("");
    }
    printf("total: %d\n",total);
    return 0;
}
