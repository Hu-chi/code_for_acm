/**
 * Created by huchi on 2017/8/22.
 * ���Ƕ���ÿ���ڵ㶼����д����E(i)��dp״̬ת�Ʒ���.
 * ���ڷ�Ҷ�ӽڵ�,��E(i)�����丸�׽ڵ�Ͷ��ӽڵ㻹��E(1)�йص�
 * ��ԣҶ�ӽڵ��ֻ������ڵ��E(1)�й�,����Ĺؼ����Ǵ�E(1)����,Ŀ���ǵ��Ƶ�Ҷ�ӽڵ�Ȼ���ֶ���һ������
 * �����ƵĹ�ϵ�г���������һ���йص����,���ǲ��ż���E(i) = A(i)*E(1) + B(i)*E(fa(i)) + c(i)
 * �������ƾ�����.
 * ������Ҫ�Լ����A(i),B(i),c(i)�ĵ��ƹ�ϵ;
 * Ȼ����
**/

//    Ҷ�ӽ�㣺
//    E[i] = ki*E[1] + ei*0 + (1-ki-ei)*(E[father[i]] + 1);
//         = ki*E[1] + (1-ki-ei)*E[father[i]] + (1-ki-ei);
//
//    ��Ҷ�ӽ�㣺��mΪ���������ı�����
//    E[i] = ki*E[1] + ei*0 + (1-ki-ei)/m*( E[father[i]]+1 + ��( E[child[i]]+1 ) );
//         = ki*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei)/m*��(E[child[i]]) + (1-ki-ei);


//    ���������ʽ�ӵ�
//    (1 - (1-ki-ei)/m*��Bj)*E[i] = (ki+(1-ki-ei)/m*��Aj)*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei) + (1-ki-ei)/m*��Cj;
//    �ɴ˿ɵ�
//    Ai =        (ki+(1-ki-ei)/m*��Aj)   / (1 - (1-ki-ei)/m*��Bj);
//    Bi =        (1-ki-ei)/m            / (1 - (1-ki-ei)/m*��Bj);
//    Ci = ( (1-ki-ei)+(1-ki-ei)/m*��Cj ) / (1 - (1-ki-ei)/m*��Bj);

//    ����Ҷ�ӽ��
//    Ai = ki;
//    Bi = 1 - ki - ei;
//    Ci = 1 - ki - ei;

#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
const double eps = 1e-10;
const int maxn = 1e4+5;
using namespace std;

double e[maxn],k[maxn],A[maxn],B[maxn],C[maxn];
vector<int> mp[maxn];
int n,st,ed,kk,ee;
bool dfs(int i, int fa){
    //Ҷ�ӽڵ�
    if(mp[i].size() == 1 && fa!=-1){
        A[i] = k[i];
        B[i] = 1 - k[i] - e[i];
        C[i] = 1 - k[i] - e[i];
        return true;
    }
    int siz = mp[i].size();
    A[i] = k[i];
    B[i] = (1 - k[i] - e[i])/siz;
    C[i] = 1 - k[i] - e[i];
    double temp = 0;

    for(int j = 0; j < siz; j ++){
        if(mp[i][j] == fa){
            continue;
        }
        if(! dfs(mp[i][j], i)){
            return false;
        }
        A[i] += A[mp[i][j]] * B[i];
        C[i] += C[mp[i][j]] * B[i];
        temp += B[mp[i][j]] * B[i];
    }
    if(fabs(temp - 1) < eps)return false;

    A[i] /= 1 - temp;
    B[i] /= 1 - temp;
    C[i] /= 1 - temp;

    return true;
}

int main(){
    int t=0,T;scanf("%d",&T);
    while(t++<T){
        for(int i = 1; i <= n; i++){
            mp[i].clear();
        }
        scanf("%d",&n);
        for(int i = 1; i < n; i++){
            scanf("%d%d",&st,&ed);
            mp[st].push_back(ed);
            mp[ed].push_back(st);
        }
        for(int i = 1; i <= n; i++){
            scanf("%d%d",&kk,&ee);
            k[i] = kk/100.0;
            e[i] = ee/100.0;
        }
        printf("Case %d: ",t);
        if(dfs(1, -1) && fabs(1 - A[1]) > eps){
            printf("%.5lf\n",C[1]/(1-A[1]));
        }else {
            puts("impossible");
        }
    }
    return 0;
}
