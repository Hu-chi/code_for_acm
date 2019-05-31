#include<cstdio>
#include<iostream>
#include<cstring>
#include <vector>
#define uint unsigned int
const int N = 5e4;
int prime[N], cnt;
bool judge[21*N], vis[N];
using namespace std;

void init(){
    for(int i = 2; i<N; i++){
        if(!vis[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt; j++){
            if(i*prime[j] >= N) break;
            vis[i*prime[j]] = 1;
            if(i%prime[j]==0) break;
        }
    }
}

int main(){
    init(); uint u,v;
    while(~scanf("%d%d",&u,&v)){
        if(u==1)u=2; // 1��������
        memset(judge,0,sizeof judge);
        for(int i = 0; i < cnt && prime[i] <= v; i++){
            uint j=((u-1)/prime[i]+1)*prime[i]; // ��һ��>=u��prime[i]�ı���
            if(j == prime[i]) j += prime[i]; // jΪ��������
            for(;j <= v; j+=prime[i]){
                judge[j-u]=1;
            }
        } int st,stlen=N,ed,edlen=0;
        int cot=0,len=0;
        for(int i = 0; i <= v-u; i++){
            if(!judge[i]){  // ��u+iΪ����
                if(len && len<stlen){
                    st = i-len; stlen = len; //���������������
                } if(len && len>=edlen){
                    ed = i-len; edlen = len; //������Զ��������
                } cot++; len = 0; // ͳ��������������
            } len ++ ;
        } if(cot>1)printf("%d,%d are closest, %d,%d are most distant.\n",u+st,u+st+stlen,u+ed,u+ed+edlen);
        else puts("There are no adjacent primes.");
    }
    return 0;
}
