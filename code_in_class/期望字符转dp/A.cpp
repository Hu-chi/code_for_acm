/**
 * Created by huchi on 2017/8/20.
 * ��Ŀ��˼��n��bug,s��ϵͳ,Ҫ���ҳ�n��bug,��������ϵͳ���ҵ�bug������
 * ������,dp[i][j]��i��bug,j��ϵͳ... ʱ����Ҫ���ٴ�
 * dp[i][j] �Ĺ�����Դ�� dp[i][j], dp[i+1][j], dp[i][j+1], dp[i+1][j+1]
 * ���ǵĹ����� p1 = (i*j)/n/s; p2 = (n-i)*j/n/s ; p3 = i*(s-j); p4 = (n-i)*(s-j)/n/s;
 * ��Ϊ���������,����dp[i,j] = p1*dp[i,j] + p2*dp[i+1,j] + p3*dp[i,j+1] + p4*dp[i+1,j+1] + 1;
**/

#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
double dp[1005][1005];
int main(){
    int n,s;
    while(~scanf("%d%d",&n,&s)){
        memset(dp, 0, sizeof dp);
        dp[n][s] = 0;
        double p1,p2,p3,p4;
        for(int i = n; i >= 0; i--){
            for(int j = s; j >= 0; j--){
                if((i==n)&&(j==s))continue;
                p1 = i*j*1.0/n/s;
                p2 = (n-i)*j*1.0/n/s;
                p3 = i*(s-j)*1.0/n/s;
                p4 = (n-i)*(s-j)*1.0/n/s;
                dp[i][j] = (p2*dp[i+1][j] + p3*dp[i][j+1] + p4*dp[i+1][j+1] + 1)/(1-p1);
            }
        }
        printf("%.20f\n",dp[0][0]);
    }
    return 0;
}