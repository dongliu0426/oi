#include <iostream>
using namespace std;

const int N = 1e6;

int main() {
  int n;
  scanf("%d", &n);
  static int a[N];
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  int q;
  scanf("%d", &q);
  while (q--) {
    int k;
    scanf("%d", &k);
    static int dq[N], f[N];
    int l = 0, r = 0;
    f[0] = 0, dq[r++] = 0;
    for (int i = 1; i < n; i++) {
      if (i - dq[l] > k)
        l++;
      f[i] = f[dq[l]] + (a[dq[l]] <= a[i]);
      while (l != r && (f[dq[r - 1]] > f[i] || (f[dq[r - 1]] == f[i] && a[dq[r - 1]] <= a[i])))
        r--;
      dq[r++] = i;
    }
    printf("%d\n", f[n - 1]);
  }
  return 0;
}