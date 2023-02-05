#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <array>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
 
#define ar array
 
const int N = 1e5, N_ = 1 << 17, L = 17;
 
ar<int, 2> operator+(const ar<int, 2>& u, const ar<int, 2>& v) {
  return {min(u[0], v[0]), max(u[1], v[1])};
}
 
int n_;
 
void build(ar<int, 2> *t, ar<int, 2> *p, int n) {
  for (int i = 0; i < n_; i++)
    t[n_ + i] = i < n ? p[i] : ar{0, 0};
  for (int i = n_ - 1; i > 0; i--)
    t[i] = t[i << 1 | 0] + t[i << 1 | 1];
}
 
ar<int, 2> query(ar<int, 2> *t, int l, int r) {
  ar<int, 2> x = {N, 0};
  for (l += n_, r += n_; l <= r; l >>= 1, r >>= 1) {
    if ((l & 1) == 1)
      x = x + t[l++];
    if ((r & 1) == 0)
      x = x + t[r--];
  }
  return x;
}
 
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int m;
  scanf("%d", &m);
  static vector<pair<int, int>> el[N + 1], er[N + 1];
  while (m--) {
    int i, j;
    scanf("%d%d", &i, &j), i--, j--;
    if (i < j) {
      er[i].push_back({j, +1});
      er[min(i + k, j)].push_back({j, -1});
    } else {
      el[max(i - k, j) + 1].push_back({j, +1});
      el[i + 1].push_back({j, -1});
    }
  }
  multiset<int> ls, rs;
  static ar<int, 2> p[N];
  for (int i = 0; i < n; i++) {
    for (auto [x, t] : el[i])
      if (t == +1)
        ls.insert(x);
      else
        ls.erase(ls.find(x));
    for (auto [x, t] : er[i])
      if (t == +1)
        rs.insert(x);
      else
        rs.erase(rs.find(x));
    p[i][0] = ls.empty() ? i : *ls.begin();
    p[i][1] = rs.empty() ? i : *rs.rbegin();
  }
  n_ = 1;
  while (n_ < n)
    n_ <<= 1;
  static ar<int, 2> tb[L][N_ * 2];
  build(tb[0], p, n);
  for (int l = 1; l < L; l++) {
    for (int i = 0; i < n; i++)
      p[i] = query(tb[l - 1], p[i][0], p[i][1]);
    build(tb[l], p, n);
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int i, j;
    scanf("%d%d", &i, &j), i--, j--;
    if (i == j) {
      printf("0\n");
      continue;
    }
    int x = 1;
    ar<int, 2> p = {i, i};
    for (int l = L - 1; l >= 0; l--) {
      ar<int, 2> q = query(tb[l], p[0], p[1]);
      if (q[0] > j || q[1] < j)
        p = q, x += 1 << l;
    }
    printf("%d\n", x == (1 << L) ? -1 : x);
  }
  return 0;
}