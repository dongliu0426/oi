#include <iostream>
#include <vector>
using namespace std;
 
#define ll long long
 
inline int p2(const int& b) {
  return 1 << b;
}
 
const int N = 3e5, K = 5;
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  static int c[N];
  for (int i = 0; i < n; i++)
    cin >> c[i], c[i]--;
  static vector<int> g[N];
  static ll f[1 << K][N];
  for (int h = 0; h < m; h++) {
    int i, j;
    cin >> i >> j, i--, j--;
    if (c[i] != c[j]) {
      g[i].push_back(j), g[j].push_back(i);
      f[p2(c[i]) | p2(c[j])][i] += 1, f[p2(c[i]) | p2(c[j])][j] += 1;
    }
  }
  ll ans = 0;
  for (int b = 0; b < 1 << k; b++)
    for (int i = 0; i < n; i++)
      if (f[b][i]) {
        ans += f[b][i];
        for (int j : g[i])
          if (!(b & p2(c[j])))
            f[b | p2(c[j])][j] += f[b][i];
      }
  cout << ans << '\n';
  return 0;
}