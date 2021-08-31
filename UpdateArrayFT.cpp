/*  We need to perform a number of range updates on an array, and then
    answer a number of queries. We do this employing a Fenwick Tree.
    Since the array is initially all zeroes we can simply return the
    prefix sum until the index requested.
 */

#include <iostream>
#include <vector>
//#include "fenwick.hpp"

using namespace std;

struct fenwick {
  vector<int> tree;

  fenwick(int n) : tree(n + 1) {}

  fenwick(int* arr, int n) 
    : tree(n + 1) {
    // build fenwick tree
    for (int k = 0; k < n; ++k) tree[k+1] = arr[k];
    for (int k = 1; k+(k&-k) < n; ++k) tree[k+(k&-k)] += tree[k];
  }

  int parent(int i) {
    return i - (i& -i);
  }

  int next(int i) {
    return i + (i& -i);
  }

  void add(int i, int v) {
    i++;
    while (i < tree.size()) {
      tree[i] += v;
      i = next(i);
    }
  }

  int sum(int i) {
    int s = 0;
    i++;
    while (i != 0) {
      s += tree[i];
      i = parent(i);
    }
    return s;
  }
};

int main() {
  int n_test;
  cin >> n_test;

  for (int i = 0; i < n_test; i++) {
    int n, u;
    cin >> n; // number of elements,
    cin >> u; // number of updates

    struct fenwick f = fenwick(n);

    int l, r, v;
    for (int j = 0; j < u; j++) {
      scanf("%d%d%d", &l, &r, &v);
      f.add(l, v);
      f.add(r + 1, (-1) * v);
    }
    int q;
    cin >> q;
    int x;
    for (int k = 0; k < q; k++) {
      scanf("%d", &x);
      cout << f.sum(x) << endl;
    }
  }
  return 0;
}