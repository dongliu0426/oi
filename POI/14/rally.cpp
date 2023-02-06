#include <iostream>
#include <list>
using namespace std;

const int N = 5e5, N_ = 1 << 19;

int t[N_ * 2], n_;

void update(int i, int x) {
  i += n_;
  while (i > 0)
    t[i] += x, i >>= 1;
}

int query() {
  int i = 1;
  while (i < n_)
    if (t[i << 1 | 1])
      i = i << 1 | 1;
    else
      i = i << 1 | 0;
  return i - n_;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  static list<int> g[N], rg[N];
  static int d[N];
  while (m--) {
    int i, j;
    scanf("%d%d", &i, &j), i--, j--;
    g[i].push_back(j), d[j]++;
    rg[j].push_back(i);
  }
  static int o[N];
  m = 0;
  for (int i = 0; i < n; i++)
    if (d[i] == 0)
      o[m++] = i;
  for (int it = 0; it < m; it++) {
    int i = o[it];
    for (int j : g[i])
      if (--d[j] == 0)
        o[m++] = j;
  }
  static int p[N], q[N];
  for (int it = 0; it < n; it++) {
    int i = o[it];
    for (int j : rg[i])
      p[i] = max(p[i], p[j] + 1);
  }
  for (int it = n - 1; it >= 0; it--) {
    int i = o[it];
    for (int j : g[i])
      q[i] = max(q[i], q[j] + 1);
  }
  n_ = 1;
  while (n_ <= n)
    n_ <<= 1;
  for (int i = 0; i < n; i++)
    update(q[i], +1);
  int ans = n + 1, ans_i = -1;
  for (int it = 0; it < n; it++) {
    int i = o[it];
    update(q[i], -1);
    for (int j : rg[i])
      update(p[j] + q[i] + 1, -1);
    int x = query();
    if (x < ans)
      ans = x, ans_i = i;
    for (int j : g[i])
      update(p[i] + q[j] + 1, +1);
    update(p[i], +1);
  }
  printf("%d %d\n", ans_i + 1, ans);
  return 0;
}