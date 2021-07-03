#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// segment index, (left, right)
typedef pair<int, pair<int, int>> segment;

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

bool compare(segment x, segment y) {
  return x.second.first > y.second.first;
}

int main() {
  int n;
  cin >> n;

  vector<segment> segs;
  vector<int64_t> values;

  int64_t l, r;
  for (int i = 0; i < n; i++) {
    // get all segments
    cin >> l;
    cin >> r;
    segs.push_back(make_pair(i, make_pair(l, r)));
    values.push_back(l);
    values.push_back(r);
  }

  // build rank
  sort (values.begin(), values.end());

  // substitute values with their ranks
  for (int i = 0; i < n; i++) {
    segs[i].second.first = lower_bound(values.begin(), values.end(), segs[i].second.first) - values.begin();
    segs[i].second.second = lower_bound(values.begin(), values.end(), segs[i].second.second) - values.begin();
  }
 
  // sort segments by left margin, decrementally
  sort (segs.begin(), segs.end(), compare);

  // solve
  fenwick F(values.size());
  vector<int> ans (n, 0);

  for (int i = 0; i < segs.size(); i++) {
    F.add(segs[i].second.second, 1);
    ans[segs[i].first] = F.sum(segs[i].second.second) - 1;
  }

  for (int i = 0; i < n; i++) {
		cout << ans[i] << endl;
	}
  return 0;
}