#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

const int A = 1e6;

long long sqrt_(long long n) {
  long long v = sqrt(n) - 1;
  while ((v + 1) * (v + 1) <= n)
    v++;
  return v * v == n ? v : -1;
}

long long mul(long long a, long long b, const long long& md) {
  long long x = 0;
  while (b > 0) {
    if ((b & 1) && (x += a) >= md)
      x -= md;
    if ((a += a) >= md)
      a -= md;
    b >>= 1;
  }
  return x;
}
long long bp(long long a, long long k, const long long& md) {
  long long p = 1;
  while (k > 0) {
    if (k & 1)
      p = mul(p, a, md);
    a = mul(a, a, md), k >>= 1;
  }
  return p;
}

bool is_prime(long long n) {
  if (n < 2 || n % 6 % 4 != 1)
    return (n | 1) == 3;
  static long long mod[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  long long s = __builtin_ctzll(n  -1), d = n >> s;
  for (long long md : mod) {
    long long p = bp(md % n, d, n), i = s;
    while (p != 1 && p != n - 1 && md % n && i--)
      p = mul(p, p, n);
    if (p != n - 1 && i != s)
      return 0;
  }
  return 1;
}

namespace bigint {
  const int B = 1e9, D = 9;
 
  void trim(vector<int>& v) {
    while (!v.empty() && v.back() == 0)
      v.pop_back();
  }
  vector<int> mult(const vector<int>& u, const vector<int>& v) {
    vector<int> w(u.size() + v.size());
    for (int i = 0; i < (int) u.size(); i++)
      if (u[i] > 0)
        for (int j = 0, c = 0; j < (int) v.size() || c > 0; j++) {
          long long t = w[i + j] + 1LL * u[i] * (j < (int) v.size() ? v[j] : 0) + c;
          c = t / B, w[i + j] = t % B;
        }
    trim(w);
    return w;
  }
  int f(int x, int d) {
    return d == 0 ? x % 10 : f(x / 10, d - 1);
  }
  int digit(const vector<int>& v, int d) {
    return d / D >= (int) v.size() ? 0 : f(v[d / D], d % D);
  }
  void print(vector<int> v) {
    printf("%d", v.back()), v.pop_back();
    while (v.size() > 0)
      printf("%09d", v.back()), v.pop_back();
  }
}

int main() {
  int n;
  scanf("%d", &n);
  static int s[A + 1];
  vector<int> p;
  for (int i = 2; i <= A; i++)
    if (!s[i]) {
      p.push_back(i);
      for (int j = i; j <= A; j += i)
        s[j] = 1;
    }
  static int k[A + 1];
  vector<pair<long long, int>> c;
  for (int i = 0; i < n; i++) {
    long long a;
    scanf("%lld", &a);
    for (int q : p)
      while (a % q == 0)
        a /= q, k[q]++;
    long long b = sqrt_(a);
    if (b == -1)
      c.push_back({a, 1});
    else
      c.push_back({b, 2});
  }
  int m = c.size();
  vector<pair<long long, int>> oc;
  for (int q : p)
    if (k[q] > 0)
      oc.push_back({q, k[q]});
  auto clear = [&](long long x) {
    if (x == 1)
      return;
    long long t = 0;
    for (int i = 0; i < m; i++)
      if (c[i].first % x == 0)
        c[i].first /= x, t += c[i].second;
    oc.push_back({x, t});
  };
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++)
      if (c[i].first != c[j].first) {
        long long y = gcd(c[i].first, c[j].first), z = c[i].first / y;
        if (y != 1) {
          clear(y), clear(z);
          break;
        }
      }
    clear(c[i].first);
  }
  if (oc.empty()) {
    printf("0 0\n");
    return 0;
  }
  int k_ = 0, p_ = 0;
  for (auto [x, t] : oc) {
    bool is_p = is_prime(x);
    if (t > k_) {
      k_ = t;
      p_ = (is_p ? 1 : 2);
    } else if (t == k_)
      p_ += (is_p ? 1 : 2);
  }
  printf("%d\n", k_);
  vector<int> v = {1};
  while (p_--)
    v = bigint::mult(v, {2});
  v[0]--;
  bigint::print(v);
  printf("\n");
  return 0;
}
