#include <iostream>
using namespace std;

const int N = 2e5, D = 18, N_ = N * (D + 1) + 1;

int lc[N_], rc[N_], t[N_], cnt;

int build(int l, int r, int x) {
  int k = ++cnt;
  t[k] = 1;
  if (l < r) {
    int m = (l + r) / 2;
    if (x <= m)
      lc[k] = build(l, m, x);
    else
      rc[k] = build(m + 1, r, x);
  }
  return k;
}

long long t1, t2;

int join(int k1, int k2, int l, int r) {
  if (!k1 | !k2)
    return k1 ^ k2;
  t1 += 1LL * t[rc[k1]] * t[lc[k2]];
  t2 += 1LL * t[lc[k1]] * t[rc[k2]];
  int m = (l + r) / 2;
  lc[k1] = join(lc[k1], lc[k2], l, m);
  rc[k1] = join(rc[k1], rc[k2], m + 1, r);
  t[k1] += t[k2];
  return k1;
}

int n;
long long sm;

int dfs() {
  int x;
  scanf("%d", &x), x--;
  if (x >= 0)
    return build(0, n - 1, x);
  else {
    int k1 = dfs(), k2 = dfs();
    t1 = t2 = 0;
    int k = join(k1, k2, 0, n - 1);
    sm += min(t1, t2);
    return k;
  }
}

int main() {
  scanf("%d", &n);
  dfs();
  printf("%lld\n", sm);
  return 0;
}
