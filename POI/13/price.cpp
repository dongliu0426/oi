#include <iostream>
#include <queue>
#include <vector>
#include <list>
using namespace std;

const int N = 1e5;

int main() {
  int n, m, s, a, b;
  scanf("%d%d%d%d%d", &n, &m, &s, &a, &b), s--;
  static vector<int> g[N];
  static list<int> l[N];
  while (m--) {
    int i, j;
    scanf("%d%d", &i, &j), i--, j--;
    g[i].push_back(j), g[j].push_back(i);
    l[i].push_back(j), l[j].push_back(i);
  }
  static int f[N], d[N];
  for (int i = 0; i < n; i++)
    d[i] = -1;
  queue<int> q;
  d[s] = 0, q.push(s);
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    for (int j : g[i])
      if (d[j] == -1)
        d[j] = d[i] + 1, q.push(j);
  }
  for (int i = 0; i < n; i++)
    f[i] = min(d[i] * a, d[i] / 2 * b + d[i] % 2 * a), d[i] = -1;
  static bool t[N];
  d[s] = 0, q.push(s);
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    for (int j : g[i])
      t[j] = 1;
    for (int j : g[i]) {
      list<int>::iterator it = l[j].begin();
      while (it != l[j].end()) {
        if (t[*it])
          ++it;
        else {
          if (d[*it] == -1)
            d[*it] = d[i] + 1, q.push(*it);
          it = l[j].erase(it);
        }
      }
    }
    for (int j : g[i])
      t[j] = 0;
  }
  for (int i = 0; i < n; i++)
    if (d[i] != -1)
      f[i] = min(f[i], d[i] * b);
  for (int i = 0; i < n; i++)
    printf("%d\n", f[i]);
  return 0;
}
