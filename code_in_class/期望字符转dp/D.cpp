/**
 * Created by huchi on 2017/8/22.
 * 我们对于每个节点都可以写出以E(i)的dp状态转移方程.
 * 对于非叶子节点,其E(i)是与其父亲节点和儿子节点还有E(1)有关的
 * 富裕叶子节点就只跟父情节点和E(1)有关,问题的关键我们从E(1)出发,目的是地推到叶子节点然后手动接一个方程
 * 但递推的关系中出现了与上一层有关的情况,我们不放假设E(i) = A(i)*E(1) + B(i)*E(fa(i)) + c(i)
 * 这样递推就行了.
 * 首先是要自己解出A(i),B(i),c(i)的递推关系;
 * 然后是
**/

//    叶子结点：
//    E[i] = ki*E[1] + ei*0 + (1-ki-ei)*(E[father[i]] + 1);
//         = ki*E[1] + (1-ki-ei)*E[father[i]] + (1-ki-ei);
//
//    非叶子结点：（m为与结点相连的边数）
//    E[i] = ki*E[1] + ei*0 + (1-ki-ei)/m*( E[father[i]]+1 + ∑( E[child[i]]+1 ) );
//         = ki*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei)/m*∑(E[child[i]]) + (1-ki-ei);


//    带入上面的式子得
//    (1 - (1-ki-ei)/m*∑Bj)*E[i] = (ki+(1-ki-ei)/m*∑Aj)*E[1] + (1-ki-ei)/m*E[father[i]] + (1-ki-ei) + (1-ki-ei)/m*∑Cj;
//    由此可得
//    Ai =        (ki+(1-ki-ei)/m*∑Aj)   / (1 - (1-ki-ei)/m*∑Bj);
//    Bi =        (1-ki-ei)/m            / (1 - (1-ki-ei)/m*∑Bj);
//    Ci = ( (1-ki-ei)+(1-ki-ei)/m*∑Cj ) / (1 - (1-ki-ei)/m*∑Bj);

//    对于叶子结点
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
    //叶子节点
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
