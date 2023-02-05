#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include <array>
#include <iostream>
using namespace std;
 
#define ar array
 
const int N = 2e5;
 
int main() {
  int n;
  scanf("%d", &n);
  static ar<int, 2> a[N];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i][0]);
    a[i][1] = 1;
    while (a[i][0] % 2 == 0)
      a[i][0] /= 2, a[i][1] *= 2;
  }
  int i = 0;
  long long p = 0;
  int q;
  scanf("%d", &q);
  while (q--) {
    long long x;
    scanf("%lld", &x);
    x -= p;
    while (a[i][1] < x)
      x -= a[i][1], p += a[i][1], i++;
    printf("%d\n", a[i][0]);
  }
  return 0;
}