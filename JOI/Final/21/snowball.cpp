#include <iostream>
using namespace std;
 
const int N = 2e5, Q = 2e5;
 
int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  static long long x[N];
  for (int i = 0; i < n; i++)
    scanf("%lld", &x[i]);
  static long long mn[Q + 1], mx[Q + 1];
  long long c = 0;
  for (int i = 0; i < q; i++) {
    long long d;
    scanf("%lld", &d);
    c += d;
    mn[i + 1] = min(mn[i], c), mx[i + 1] = max(mx[i], c);
  }
  long long l = x[0] + mn[q];
  for (int i = 0; i < n - 1; i++) {
    int low = 1, hi = q;
    while (low < hi) {
      int t = (low + hi) / 2;
      if (x[i] + mx[t] >= x[i + 1] + mn[t])
        hi = t;
      else
        low = t + 1;
    }
    long long r = mn[low] == mn[low - 1] ? x[i + 1] + mn[low] : x[i] + mx[low];
    printf("%lld\n", min(x[i] + mx[q], r) - max(l, x[i] + mn[q]));
    l = r;
  }
  printf("%lld\n", x[n - 1] + mx[q] - max(l, x[n - 1] + mn[q]));
  return 0;
}