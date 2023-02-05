#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <array>
#include <iostream>
using namespace std;
 
const int N = 3e5;
const long long INF = 1e18;
 
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  static int a[N], b[N];
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
    a[i] = max(a[i], b[i]);
  }
  long long low = 0, hi = INF;
  while (low < hi) {
    long long t = (low + hi) / 2 + 1, c = 0;
    for (int i = 0; i < n; i++) {
      long long x = (t + a[i] - 1) / a[i];
      if (x <= m)
        c += m - x;
      else
        c = max(-INF, c - (t - 1LL * m * a[i] + b[i] - 1) / b[i]);
    }
    if (c >= 0)
      low = t;
    else
      hi = t - 1;
  }
  printf("%lld\n", low);
  return 0;
}