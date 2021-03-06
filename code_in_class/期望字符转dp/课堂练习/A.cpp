#include <bits/stdc++.h>
const int N = 1e3+9;
const int M = 26;
using namespace std;

void getNxt(char *s, int len, int *nxt, int p[][M]) {
  int j = 1, k = 0;
  nxt[j++] = k;
  while(j <= len) {
    if(k==0 || s[k+1] == s[j]) {
        if(s[k+1] == s[j]) k++;
        nxt[j++] = k;
    } else k = nxt[k];
  }
  for (int i = 0; i <= len; i++) {
    for (int c = 0; c < M; c++) {
      int j = i;
      while(j && s[j+1] != c + 'a') j = nxt[j];
      if(s[j+1] == c + 'a') j++;
      p[i][c] = j;
    }
  }
}

char ch[N], s[N], t[N];
int nxt_s[N], nxt_t[N];
int p_s[N][M], p_t[N][M], dp[N][55][55];

int main() {
  scanf("%s%s%s", ch+1, s+1, t+1);
  int len_c = strlen(ch+1);
  int len_s = strlen(s +1);
  int len_t = strlen(t +1);
  getNxt(s, len_s, nxt_s, p_s);
  getNxt(t, len_t, nxt_t, p_t);

  memset(dp, 0xcf, sizeof dp);
  dp[0][0][0] = 0;
  for (int i = 0; i < len_c; i++) {
    for (int j = 0; j <= len_s; j++) {
      for (int k = 0; k <= len_t; k++) {
        if(dp[i][j][k] == 0xcfcfcfcf) continue;
        for (int c = 0; c < M; c++) {
          if(ch[i+1] != '*' && ch[i+1] != c + 'a') continue;
          int a = p_s[j][c], b = p_t[k][c];
          dp[i+1][a][b] = max(dp[i+1][a][b], dp[i][j][k] + (a == len_s) - (b == len_t));
        }
      }
    }
  }
  int ans = 0xcfcfcfcf;
  for (int i = 0; i <= len_s; i++) {
    // ans = max(ans, *max_element(dp[len_c][i], dp[len_c][i]+len_t+1));

    for (int j = 0; j <= len_t; j++) {
      ans = max(ans, dp[len_c][i][j]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
