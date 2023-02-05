#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
 
const int N = 1e5, A = 15;
 
int p2(const int& i) {
  return 1 << i;
}
 
long long l[A][N], r[A][N];
vector<int> p[A];
int n;
 
long long c2(int k) {
  return 1LL * k * (k - 1) / 2;
}
 
long long cost(int i, int j, int k) {
  long long x = c2(k) + c2(p[j].size() - k);
  for (int u = 0; u < A; u++)
    if (i & p2(u)) {
      if (k > 0)
        x += 2 * l[u][p[j][k - 1]];
      if (k < (int) p[j].size())
        x += 2 * r[u][p[j][k]];
    }
  return x;
}
 
void print(long long x) {
  if (x % 2 == 0)
    cout << x / 2 << '\n';
  else
    cout << x / 2 << ".5" << '\n';
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  string s;
  cin >> s;
  n = s.size();
  for (int i = 0; i < n; i++)
    p[s[i] - 'A'].push_back(i);
  for (int i = 0; i < A; i++) {
    static int k[N];
    for (int j = 0; j < n; j++)
      k[j] = (s[j] - 'A' == i ? 1 : 0) + (j > 0 ? k[j - 1] : 0);
    for (int j = 0; j < A; j++) {
      int last = -1;
      for (int u : p[j])
        l[i][u] = k[u] + (last != -1 ? l[i][last] : 0), last = u;
      last = -1;
      reverse(p[j].begin(), p[j].end());
      for (int u : p[j])
        r[i][u] = (k[n - 1] - k[u]) + (last != -1 ? r[i][last] : 0), last = u;
      reverse(p[j].begin(), p[j].end());
    }
  }
  static long long f[1 << A];
  f[0] = 0;
  for (int i = 1; i < 1 << A; i++) {
    f[i] = 1e18;
    for (int j = 0; j < A; j++)
      if (i & p2(j)) {
        if (p[j].size() == 0) {
          f[i] = min(f[i], f[i ^ p2(j)]);
          continue;
        }
        int low = 0, hi = p[j].size();
        while (low < hi) {
          int m = (low + hi) / 2;
          if (cost(i ^ p2(j), j, m) < cost(i ^ p2(j), j, m + 1))
            hi = m;
          else
            low = m + 1;
        }
        f[i] = min(f[i], f[i ^ p2(j)] + cost(i ^ p2(j), j, low));
      }
  }
  print(f[(1 << A) - 1]);
  return 0;
}