#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <algorithm>
#include <array>
#include <iostream>
using namespace std;
 
#define ar array
 
const int N = 500, INF = 1e9;
const long long INF_LL = 1e18;
 
int main() {
  int n, k;
  scanf("%d", &n);
  scanf("%d", &k);
  static ar<int, 2> a[N];
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a[i][1], &a[i][0]);
    if (a[i][0] == -1)
      a[i][0] = INF;
  }
  sort(a, a + n);
  static long long sm[N + 1][N + 1];
  for (int i = n - 1; i >= 0; i--)
    for (int j = 1; j <= n - i; j++)
      sm[i][j] = min(a[i][1] + sm[i + 1][j - 1], j != n - i ? sm[i + 1][j] : INF_LL);
  double ans = sm[0][k];
  for (int t = 1; t <= k; t++) {
    static double f[N + 1];
    for (int i = 1; i <= t; i++)
      f[i] = INF_LL;
    f[0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = t; j >= 0; j--)
        f[j] = min(f[j] + (double) a[i][1] / (t + 1), j == 0 ? INF_LL : f[j - 1] + (double) a[i][0] / j);
      if (i >= t - 1 && k - i > 0)
        ans = min(ans, f[t] + (double) sm[i + 1][k - i - 1] / (t + 1));
    }
  }
  printf("%.4lf\n", ans);
  return 0;
}