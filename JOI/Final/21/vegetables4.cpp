#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <iostream>
using namespace std;
 
const int N = 2e5;
 
int main() {
  int n;
  scanf("%d", &n);
  static int a[N];
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  static long long l[N], r[N];
  for (int i = 0, x = 0; i < n; x = a[i++])
    l[i] = max(0, x - a[i] + 1) + (i > 0 ? l[i - 1] : 0);
  for (int i = n - 1, x = 0; i >= 0; x = a[i--])
    r[i] = max(0, x - a[i] + 1) + (i < n - 1 ? r[i + 1] : 0);
  long long x = 1e18;
  for (int i = 0; i < n; i++)
    x = min(x, max(l[i], r[i]));
  printf("%lld\n", x);
  return 0;
}