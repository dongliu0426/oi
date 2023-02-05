#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;
 
const int N = 2e5;
 
int e[N];
 
int find(int i) {
  return e[i] < 0 ? i : e[i] = find(e[i]);
}
 
void link(int i, int j) {
  i = find(i), j = find(j);
  if (e[i] > e[j])
    swap(i, j);
  e[i] += e[j], e[j] = i;
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m;
  cin >> n >> m;
  static int s[N];
  for (int i = 0; i < n; i++)
    cin >> s[i];
  vector<array<int, 3>> ed(m);
  for (auto &[v, i, j] : ed) {
    cin >> i >> j, i--, j--;
    v = max(s[i], s[j]);
  }
  sort(ed.begin(), ed.end());
  static vector<int> win[N];
  static long long sm[N];
  for (int i = 0; i < n; i++)
    e[i] = -1, sm[i] = s[i], win[i].push_back(i);
  for (auto [w, i, j] : ed) {
    int u = find(i), v = find(j);
    if (u == v)
      continue;
    link(i, j);
    int t = find(i);
    if (sm[u] < s[j])
      swap(win[t], win[v]);
    else if (sm[v] < s[i])
      swap(win[t], win[u]);
    else {
      if (win[v].size() > win[u].size())
        swap(win[u], win[v]);
      for (int i : win[v])
        win[u].push_back(i);
      swap(win[t], win[u]);
    }
    sm[t] = sm[u] + sm[v];
  }
  static bool w[N];
  for (int i : win[find(0)])
    w[i] = 1;
  for (int i = 0; i < n; i++)
    cout << w[i];
  cout << '\n';
  return 0;
}