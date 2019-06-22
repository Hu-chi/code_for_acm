#include <bits/stdc++.h>
const int N = 1e5+9;
using namespace std;
deque<pair<int, long long> > q;
int k;
bool vis[N];

int main() {
  scanf("%d", &k);
  q.push_back({1, 1});
  while(!q.empty()) {
    pair<int, long long> tp = q.front(); q.pop_front();
    if(!tp.first) {
      printf("%d\n", tp.second);
      break;
    }
    if(vis[tp.first]) continue;
    vis[tp.first] = 1;
    q.push_front({tp.first*10%k, tp.second});
    q.push_back({(tp.first+1)%k, tp.second+1});
  }
  return 0;
}
