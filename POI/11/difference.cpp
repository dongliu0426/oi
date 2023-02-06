#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6;

int main() {
  int n;
  scanf("%d", &n);
  static char s[N];
  scanf("%s", s);
  static vector<int> u[N];
  for (int i = 0; i < n; i++)
    u[s[i] - 'a'].push_back(i);
  int ans = 0;
  for (int i = 0; i < 26; i++)
    for (int j = 0; j < 26; j++) {
      if (i == j)
        continue;
      static int t[N + 1];
      int m = 0, l = 0, r = 0;
      while (l < (int) u[i].size() || r < (int) u[j].size())
        if (l == (int) u[i].size())
          t[++m] = -1, r++;
        else if (r == (int) u[j].size())
          t[++m] = +1, l++;
        else if (u[i][l] < u[j][r])
          t[++m] = +1, l++;
        else
          t[++m] = -1, r++;
      int p = 0, c = 0, d = 0, mn = n;
      for (int k = 1; k <= m; k++) {
        c += t[k];
        if (t[k] == -1) {
          for (int k_ = p; k_ < k; k_++)
            mn = min(mn, d += t[k_]);
          p = k;
        }
        ans = max(ans, c - mn);
      }
    }
  printf("%d\n", ans);
  return 0;
}
