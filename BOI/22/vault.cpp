#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <iostream>
using namespace std;
 
const int N = 300, B = N * (N + 1);
const long long INF = 1e18;
 
namespace dq {
  pair<long long, int> d[B * 2 + 1];
  int u, v, l, r;
 
  void clear() {
    u = v = l = r = 0;
  }
  int size() {
    return v - u;
  }
  void push(long long x) {
    while (r - l > 0 && d[r - 1].first <= x)
      r--;
    d[r++] = {x, v++};
  }
  void pop() {
    if (d[l].second == u++)
      l++;
  }
  long long query() {
    return d[l].first;
  }
}
 
void process(long long *f, int b, int i, int c, int t) {
  if (i > 0) {
    for (int md = 0; md < i; md++) {
      dq::clear();
      for (int j = md; j <= b * 2; j += i) {
        dq::push(f[j] == -INF ? -INF : f[j] - j / i * t);
        if (dq::size() > c + 1)
          dq::pop();
        f[j] = dq::query() == -INF ? -INF : dq::query() + j / i * t;
      }
    }
  } else if (i < 0) {
    i = -i;
    for (int md = 0; md < i; md++) {
      dq::clear();
      for (int j = (b * 2 - md) / i * i + md; j >= 0; j -= i) {
        dq::push(f[j] == -INF ? -INF : f[j] + j / i * t);
        if (dq::size() > c + 1)
          dq::pop();
        f[j] = dq::query() == -INF ? -INF : dq::query() - j / i * t;
      }
    }
  } else if (t > 0) {
    for (int j = 0; j <= b * 2; j++)
      if (f[j] != -INF)
        f[j] += c * t;
  }
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  long long m;
  cin >> n >> m;
  static long long k[N * 2 + 1], u[N * 2 + 1];
  long long m_ = 0;
  for (int i = -n; i <= +n; i++) {
    cin >> k[n + i];
    u[n + i] = k[n + i], m_ += i * k[n + i];
  }
  if (m_ < m) {
    for (int i = n; i > 0 && m_ < m; i--) {
      long long t = min(u[n - i], (m - m_ + i - 1) / i);
      m_ += t * i, u[n - i] -= t;
    }
    if (m_ < m) {
      cout << "impossible\n";
      return 0;
    }
  } else if (m_ > m) {
    for (int i = n; i > 0 && m_ > m; i--) {
      long long t = min(u[n + i], (m_ - m + i - 1) / i);
      m_ -= t * i, u[n + i] -= t;
    }
    if (m_ > m) {
      cout << "impossible\n";
      return 0;
    }
  }
  int b = n * (n + 1);
  static long long f[B * 2 + 1];
  for (int i = -b; i <= +b; i++)
    f[b + i] = -INF;
  f[b + 0] = 0;
  for (int i = -n; i <= +n; i++) {
    process(f, b, -i, min(u[n + i], (long long) n + 1), -1);
    process(f, b, +i, min(k[n + i] - u[n + i], (long long) n + 1), +1);
  }
  if (f[b + m - m_] == -INF) {
    cout << "impossible\n";
    return 0;
  }
  long long ans = f[b + m - m_];
  for (int i = -n; i <= +n; i++)
    ans += u[n + i];
  cout << ans << '\n';
  return 0;
}