#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
 
#include "art.h"
#include <algorithm>
#include <vector>
using namespace std;
 
void solve(int n) {
  vector<int> p(n);
  for (int i = 0; i < n; i++)
    p[i] = i + 1;
  vector<int> k(n);
  for (int i = 0; i < n; i++) {
    k[i] = publish(p);
    rotate(p.begin(), p.begin() + 1, p.end());
  }
  for (int i = 0; i < n; i++)
    p[(k[i] - k[(i + 1) % n] + n - 1) / 2] = i + 1;
  answer(p);
}