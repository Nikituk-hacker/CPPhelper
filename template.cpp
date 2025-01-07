// #pragma GCC optimize("Ofast,unroll-loops")
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// #pragma GCC target("avx,avx2,fma")

#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)

const auto ready = []() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cout << std::fixed << std::setprecision(12);
  return 1;
};

const auto TEST = []() { freopen("in.txt", "r", stdin); };

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template <typename C>
void reuniq(C& c) {
  c.erase(unique(all(c)), end(c));
}

template <typename C, typename X>
int lowpos(const C& c, X x) {
  return int(lower_bound(all(c), x) - begin(c));
}

template <typename C, typename X>
int uppos(const C& c, X x) {
  return int(upper_bound(all(c), x) - begin(c));
}

template <typename X, typename Y>
X& remin(X& x, const Y& y) {
  return x = (y < x) ? y : x;
}

template <typename X, typename Y>
X& remax(X& x, const Y& y) {
  return x = (x < y) ? y : x;
}

signed main() {
  
}
