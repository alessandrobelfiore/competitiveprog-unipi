#include <iostream>
#include <vector>

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