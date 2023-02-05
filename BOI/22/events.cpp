#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <array>
#include <algorithm>
#include <iostream>
using namespace std;
 
const int N = 1e5, N_ = 1 << 18, L = 17;
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, q;
  cin >> n >> q;
  static int l[N], r[N], c[N * 2];
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
    c[i << 1 | 0] = l[i], c[i << 1 | 1] = r[i];
  }
  sort(c, c + n * 2);
  int m = unique(c, c + n * 2) - c;
  static array<int, 2> t[N_ * 2];
  int n_;
  n_ = 1;
  while (n_ < m)
    n_ <<= 1;
  for (int i = 1; i < n_ * 2; i++)
    t[i] = {N_, -1};
  for (int i = 0; i < n; i++) {
    l[i] = lower_bound(c, c + m, l[i]) - c;
    r[i] = lower_bound(c, c + m, r[i]) - c;
    int p = n_ + r[i];
    while (p > 0)
      t[p] = min(t[p], {l[i], i}), p >>= 1;
  }
  static int p[L][N];
  for (int i = 0; i < n; i++) {
    array<int, 2> x = {N_, -1};
    for (int l_ = l[i] + n_, r_ = r[i] + n_; l_ <= r_; l_ >>= 1, r_ >>= 1) {
      if ((l_ & 1) == 1)
        x = min(x, t[l_++]);
      if ((r_ & 1) == 0)
        x = min(x, t[r_--]);
    }
    p[0][i] = x[1];
  }
  for (int lg = 1; lg < L; lg++)
    for (int i = 0; i < n; i++)
      p[lg][i] = p[lg - 1][p[lg - 1][i]];
  while (q--) {
    int i, j;
    cin >> i >> j, i--, j--;
    if (r[j] < r[i]) {
      cout << "impossible\n";
      continue;
    }
    if (i == j) {
      cout << 0 << '\n';
      continue;
    }
    if (l[j] <= r[i] && r[i] <= r[j]) {
      cout << 1 << '\n';
      continue;
    }
    int k = 0;
    for (int lg = L - 1; lg >= 0; lg--)
      if (l[p[lg][j]] > r[i])
        k += 1 << lg, j = p[lg][j];
    if (k > n) {
      cout << "impossible\n";
      continue;
    }
    cout << k + 2 << '\n';
  }
  return 0;
}