#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int main(){
    int k,t=0;
    scanf("%d",&k);
    while(k>t++){
        int a,b;
        double ans = 0;
        scanf("%d %d",&a,&b);
        if(a%2==0){
            ans = 1.0/(a+1);
        }
        printf("Case %d: %.12lf\n",t,ans);
    }
    return 0;
}
