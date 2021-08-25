/*  We need to count the number of pairs, i < j and A[i] > A[j], 
    called inversions. 

 */

#include <iostream>
#include <vector>
#include <algorithm>

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

  fenwick(vector<int> v) 
    : tree(v.size() + 1) {
    for (int k = 0; k < v.size(); ++k) tree[k+1] = v[k];
    for (int k = 1; k+(k&-k) < tree.size(); ++k) tree[k+(k&-k)] += tree[k];
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

  vector<int64_t> ans (n_test, 0);
  for (int index = 0; index < n_test; index++) {
    vector<int64_t> a;
    vector<int64_t> support;
    int n;
    cin >> n;
    for (int j = 0; j < n; j++) {
      int64_t x;
      cin >> x;
      a.push_back(x);
      support.push_back(x);
    }
    // build rank
    sort (support.begin(), support.end());

    // substitute a with their ranks
    for (int i = 0; i < n; i++) {
      a[i] = lower_bound(support.begin(), support.end(), a[i]) - support.begin();
    }

    // solve
    fenwick F(a.size() + 1);

    for (int i = 0; i < a.size(); i++) {
      int idx = a.size() - a[i] - 1;
      F.add(idx, 1);
      ans[index] += F.sum(idx - 1);
    }
  }
  for (int i = 0; i < n_test; i++) {
    cout << ans[i] << endl;
  }
  return 0;
}