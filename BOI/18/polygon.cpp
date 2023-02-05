#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
 
#define ar array
 
const int N = 1e5;
 
vector<int> g[N], cc;
bool on[N];
int o[N], v[N];
 
void dfs(int i) {
  int j = o[i];
  if (v[j] == 0) {
    v[j] = 1;
    dfs(j);
  } else if (v[j] == 1)
    cc.push_back(j);
  v[i] = 2;
}
 
ar<int, 2> dp(int i) {
  int t01 = 0, tm = 0;
  for (int j : g[i])
    if (!on[j]) {
      ar<int, 2> a = dp(j);
      t01 += max(a[0], a[1]), tm = max(tm, 1 + a[0] - max(a[0], a[1]));
    }
  return {t01, t01 + tm};
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  cin >> n;
  static ar<string, 2> e[N];
  static string c[N];
  for (int i = 0; i < n; i++)
    cin >> e[i][0] >> e[i][1], c[i] = e[i][0];
  if (n % 2) {
    cout << -1 << '\n';
    return 0;
  }
  sort(c, c + n);
  for (int h = 0; h < n; h++) {
    int u = lower_bound(c, c + n, e[h][0]) - c;
    int v = lower_bound(c, c + n, e[h][1]) - c;
    o[u] = v;
    g[v].push_back(u);
  }
  for (int i = 0; i < n; i++)
    if (!v[i]) {
      v[i] = 1;
      dfs(i);
    }
  int p0 = 0, p1 = 0;
  for (int i : cc) {
    int u = i;
    vector<ar<int, 2>> f;
    do {
      on[u] = 1;
      u = o[u];
    } while (u != i);
    u = i;
    do {
      f.push_back(dp(u));
      u = o[u];
    } while (u != i);
    if (f.size() == 1)
      p1 += max(f[0][0], f[0][1]);
    else if (f.size() == 2)
      p0 += 1, p1 += f[0][0] + f[1][0];
    else {
      int x = 0;
      for (int it = 0; it < 2; it++) {
        ar<int, 2> t = f[0];
        for (int i = 1; i < (int) f.size(); i++)
          t = {max(t[0], t[1]) + f[i][0], max(t[0] + f[i][0] + 1, max(t[0], t[1]) + f[i][1])};
        x = max(x, max(t[0], t[1]));
        rotate(f.begin(), f.begin() + 1, f.end());
      }
      p1 += x;
    }
  }
  int p2 = n / 2 - p0 - p1;
  cout << p1 + p2 * 2 << '\n';
  return 0;
}