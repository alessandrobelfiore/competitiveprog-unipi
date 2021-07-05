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

  int64_t sum(int i) {
    int64_t s = 0;
    i++;
    while (i != 0) {
      s += tree[i];
      i = parent(i);
    }
    return s;
  }
};

int main() {
  // get input
  int n;
  cin >> n;
  vector<int64_t> a;
  vector<int64_t> support;
  int64_t res = 0;
  
  for (int i = 0; i < n; i++) {
    int64_t x;
    cin >> x;
    a.push_back(x);
    support.push_back(x);
  }

  // sort array input and get ranks
  sort (support.begin(), support.end());
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(support.begin(), support.end(), a[i]) - support.begin();
  }

  // build suffix count
  vector<int> suffix (n, 0);
  vector<int> occs (n, 0);
  for (int i = n - 1; i >= 0; i--) {
    occs[a[i]] ++;
    suffix[i] = occs[a[i]];
  }

  vector<int> B (n + 1, 0);
  for (int i = 0; i < n; i++) {
    B[suffix[i]] ++;
  }
  // build FT on number of occurences of suffix count
  fenwick F(B);

  vector<int> occsA (n + 1, 0);
  // read array from left to right, get occurences
  for (int i = 0; i < n - 1; i++) {
    int k = occsA[a[i]];
    occsA[a[i]] ++;
    F.add(suffix[i], -1);
    int64_t tmp = F.sum(k);
    res += F.sum(k);
    cout << "adding " << tmp << endl;
  }

  cout << res << endl;
}