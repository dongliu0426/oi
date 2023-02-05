#include <iostream>
#include <vector>
using namespace std;

const int N = 3e5;

vector<int> g[N];

int dfs(int p, int i, int k) {
  int x = 0;
  for (int j : g[i])
    if (p != j)
      x += 1 + max(0, dfs(i, j, k));
  return x - k;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int h = 0; h < n - 1; h++) {
    int i, j;
    scanf("%d%d", &i, &j), i--, j--;
    g[i].push_back(j), g[j].push_back(i);
  }
  int low = 0, hi = n;
  while (low < hi) {
    int t = (low + hi) / 2;
    if (dfs(-1, 0, t) <= 0)
      hi = t;
    else
      low = t + 1;
  }
  printf("%d\n", low);
  return 0;
}
