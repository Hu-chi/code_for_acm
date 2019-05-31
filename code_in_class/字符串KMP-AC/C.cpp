#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
const int N = 4e5+9;
using namespace std;
int n;
char s[N];
int nxt[N];
void getNxt(){
    int i=0,j=-1;
    nxt[i]=j;
    while(i<n){
        if(j==-1|| s[i]==s[j]){
            i++;
            j++;
            nxt[i] = j;
        }else j = nxt[j];
    }
}

vector<int>ans;
int main(){
    while(~scanf("%s",s)){
        ans.clear();
        n = strlen(s);
        getNxt();
        int tmp = n;
        while(tmp){
            ans.push_back(tmp);
            tmp = nxt[tmp];
        }
        sort(ans.begin(),ans.end());
        for(int i = 0; i < ans.size(); i++){
            printf("%d%c",ans[i]," \n"[i==ans.size()-1]);
        }
    }
    return 0;
}
