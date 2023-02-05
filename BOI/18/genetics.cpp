#include <iostream>
#include <random>
using namespace std;
 
typedef unsigned int ui;
 
const int N = 4100;
 
int g(char c) {
  return c == 'A' ? 0 : c == 'C' ? 1 : c == 'G' ? 2 : 3;
}
 
mt19937 rng(1234);
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  static string s[N];
  static ui h[N], f[N][4];
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    h[i] = rng();
    for (int j = 0; j < m; j++)
      f[j][g(s[i][j])] += h[i];
  }
  ui sum = 0;
  for (int i = 0; i < n; i++)
    sum += h[i];
  for (int i = 0; i < n; i++) {
    ui x = 0;
    for (int j = 0; j < m; j++)
      x += f[j][g(s[i][j])];
    if ((m - k) * (sum - h[i]) == x - m * h[i]) {
      cout << i + 1 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
  return 0;
}