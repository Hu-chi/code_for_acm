#include<cstdio>
#include<cstring>
const int mod=1<<15;
struct Edge{int v,nxt,w;}e[mod];
int head[mod], sq[101];
int cnt;

inline int gethash(int x){
    return (x+ mod) & (mod-1);
}

inline void insert(int x) {
    int id=gethash(x);
    for(int i=head[id]; i != -1;i=e[i].nxt) {
        if(e[i].v==x) {
            e[i].w++; return;
        }
    } e[cnt] = {x, head[id], 1}; head[id]=cnt++;
}

inline int search(int x) {
    int id=gethash(x);
    for(int i=head[id] ; i!=-1;i=e[i].nxt) {
        if(e[i].v==x) return e[i].w;
    } return 0;
}

int main() {
    int a,b,c,d ;
    for(int i=1;i<=100;i++) sq[i]=i*i;
    while(~scanf("%d%d%d%d",&a,&b,&c,&d)) {
        if(a>0 && b>0 && c>0 && d>0||a<0 && b<0 && c<0 && d<0) {
            printf("0\n"); continue;
        } memset(head,-1,sizeof(head)); cnt=0;
        for(int i=1;i<=100;i++) {
            for(int j=1;j<=100;j++) {
                insert(sq[i]*a+sq[j]*b);
            }
        } int ans=0;
        for(int i=1;i<=100;i++) {
            for(int j=1;j<=100;j++) {
                ans+=search(-sq[i]*c-sq[j]*d);
            }
        } printf("%d\n",ans<<4);
    } return 0;
}
