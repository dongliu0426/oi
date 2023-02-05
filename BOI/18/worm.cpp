#include <array>
#include <iostream>
#include <cmath>
#include <random>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
  
struct hm_hash {
  const uint64_t C = (long long) (4e18 * acos(0)) | 71;
  
  uint64_t operator()(uint64_t x) const {
    return __builtin_bswap64(x * C);
  }
};
  
template<typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, hm_hash>;
 
template<typename K>
using hash_set = hash_map<K, __gnu_pbds::null_type>;
 
#define ar array
 
const int NMK = 1.25e6;
 
int n, m, k, q;
hash_map<int, int> f;
 
int query(int x, int y, int z) {
  if (x < 0 || x >= n || y < 0 || y >= m || z < 0 || z >= k)
    return 0;
  int &v = f[(x * m + y) * k + z];
  if (v > 0)
    return v;
  q--;
  cout << "? " << x + 1 << ' ' << y + 1 << ' ' << z + 1 << endl;
  cin >> v;
  return v;
}
 
void answer(int x, int y, int z) {
  cout << "! " << x + 1 << ' ' << y + 1 << ' ' << z + 1 << endl;
  exit(0);
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k >> q;
  if (m == 1 && k == 1) {
    int low = -1, hi = -1, x = 1, y = 1;
    while (low + y < n) {
      x += y;
      swap(x, y);
    }
    hi = low + y;
    while (x > 1) {
      y -= x;
      if (query(low + y, 0, 0) > query(hi - y, 0, 0))
        hi -= y;
      else
        low += y;
      swap(x, y);
    }
    answer(low + 1, 0, 0);
  } else if (k == 1) {
    int x1 = 0, x2 = n - 1, y1 = 0, y2 = m - 1;
    ar<int, 2> b = {-1, -1};
    while (x1 != x2 || y1 != y2) {
      if (x1 != x2) {
        int m = (x1 + x2) / 2;
        for (int i = y1; i <= y2; i++)
          if (query(m, i, 0) > query(b[0], b[1], 0))
            b = {m, i};
        if (b[0] < m)
          x2 = m - 1;
        else if (b[0] > m)
          x1 = m + 1;
        else if (query(m - 1, b[1], 0) > query(m, b[1], 0))
          x2 = m - 1;
        else if (query(m + 1, b[1], 0) > query(m, b[1], 0))
          x1 = m + 1;
        else
          answer(m, b[1], 0);
      }
      if (y1 != y2) {
        int m = (y1 + y2) / 2;
        for (int i = x1; i <= x2; i++)
          if (query(i, m, 0) > query(b[0], b[1], 0))
            b = {i, m};
        if (b[1] < m)
          y2 = m - 1;
        else if (b[1] > m)
          y1 = m + 1;
        else if (query(b[0], m - 1, 0) > query(b[0], m, 0))
          y2 = m - 1;
        else if (query(b[0], m + 1, 0) > query(b[0], m, 0))
          y1 = m + 1;
        else
          answer(b[0], m, 0);
      }
    }
    answer(x1, y1, 0);
  } else {
    int q_ = q;
    mt19937 rng(1234);
    int x = -1, y = -1, z = -1;
    while (q > q_ / 2) {
      int x_ = rng() % n, y_ = rng() % m, z_ = rng() % k;
      if (query(x_, y_, z_) > query(x, y, z))
        x = x_, y = y_, z = z_;
    }
    auto move = [&](int x_, int y_, int z_) -> bool {
      if (q > 0 && query(x_, y_, z_) > query(x, y, z)) {
        x = x_, y = y_, z = z_;
        return 1;
      }
      return 0;
    };
    while (q > 0)
      if (!(move(x + 1, y, z) || move(x - 1, y, z) || move(x, y + 1, z) || move(x, y - 1, z) || move(x, y, z + 1) || move(x, y, z - 1)))
        answer(x, y, z);
    answer(x, y, z);
  }
  return 0;
}