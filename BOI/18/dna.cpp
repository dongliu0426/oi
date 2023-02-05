#include <iostream>
using namespace std;
 
const int N = 2e5;
 
namespace ds {
  int c[N], g[N], z;
 
  void add(int x) {
    if (g[x] > 0)
      z -= ++c[x] == g[x];
  }
  void rem(int x) {
    if (g[x] > 0)
      z += c[x]-- == g[x];
  }
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, k, m;
  cin >> n >> k >> m;
  static int a[N];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int h = 0; h < m; h++) {
    int i;
    cin >> i;
    cin >> ds::g[i];
  }
  ds::z = m;
  int x = n + 1;
  for (int i = 0, j = 0; i < n; i++) {
    while (j < n && ds::z > 0)
      ds::add(a[j++]);
    if (ds::z == 0)
      x = min(x, j - i);
    ds::rem(a[i]);
  }
  if (x == n + 1)
    cout << "impossible\n";
  else
    cout << x << '\n';
  return 0;
}