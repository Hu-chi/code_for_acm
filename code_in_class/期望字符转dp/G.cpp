
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=1010;
const int INF=0x3f3f3f3f;

struct Trie{
    int ok;
    Trie *fail;
    Trie *next[4];
    void init(){
        ok=0;
        fail=NULL;
        memset(next,NULL,sizeof(next));
    }
}*root,*q[N],a[N];

char wrd[30];
char str[N];
int n,cnt,dp[N][N];

int find(char ch){
    switch(ch){
        case 'A':return 0;
        case 'C':return 1;
        case 'T':return 2;
        case 'G':return 3;
    }
    return 0;
}

void InsertTrie(char *str){
    Trie *loc=root;
    for(int i=0;str[i]!='\0';i++){
        int id=find(str[i]);
        if(loc->next[id]==NULL){
            a[cnt].init();
            loc->next[id]=&a[cnt++];
        }
        loc=loc->next[id];
    }
    loc->ok=1;
}

void AC_automation(){
    int head=0,tail=0;
    root->fail=NULL;
    q[tail++]=root;
    Trie *cur,*tmp;
    while(head<tail){
        cur=q[head++];
        tmp=NULL;
        for(int i=0;i<4;i++){
            if(cur->next[i]==NULL){
                if(cur==root)       //方便DP
                    cur->next[i]=root;
                else
                    cur->next[i]=cur->fail->next[i];
            }else{
                tmp=cur->fail;
                while(tmp!=NULL){
                    if(tmp->next[i]!=NULL){
                        cur->next[i]->fail=tmp->next[i];
                        cur->next[i]->ok |= tmp->next[i]->ok;
                        break;      //注意退出循环
                    }
                    tmp=tmp->fail;
                }
                if(tmp==NULL)
                    cur->next[i]->fail=root;
                q[tail++]=cur->next[i];
            }
        }
    }
}

int main(){

    //freopen("input.txt","r",stdin);

    int cases=0;
    while(~scanf("%d",&n) && n){
        cnt=0;
        root=&a[cnt++];
        root->init();
        for(int i=0;i<n;i++){
            scanf("%s",wrd);
            InsertTrie(wrd);
        }
        AC_automation();
        scanf("%s",str);
        int len=strlen(str);
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                dp[i][j]=INF;
        dp[0][0]=0;
        for(int i=1;i<=len;i++)
            for(int j=0;j<cnt;j++)
                for(int k=0;k<4;k++){
                    Trie *tmp=a[j].next[k];
                    if(tmp->ok)
                        continue;
                    int dis=tmp-root;
                    dp[i][dis]=min(dp[i][dis],dp[i-1][j]+(k!=find(str[i-1])));
                }
        int ans=INF;
        for(int i=0;i<cnt;i++)
            if(ans>dp[len][i])
                ans=dp[len][i];
        printf("Case %d: ",++cases);
        if(ans==INF)
            printf("-1\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}
