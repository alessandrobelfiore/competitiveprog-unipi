/*  We are given n segments on a line. There are no ends of some segments that coincide. For each segment 
    we have find the number of segments it contains. We remap segments using rank, we sort them 
    by left margin, decreasingly. Then we use a segment tree to add these values and compute the prefix sum
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// segment index, (left, right)
typedef pair<int, pair<int64_t, int64_t>> segment;

// utility functions
bool IsPowerOfTwo(int x) {
  return (x != 0) && ((x & (x - 1)) == 0);
}

int nextPowerOfTwo(int x) {
  int power = 1;
  while(power < x)
    power*=2;
  return power;
}

bool compare(segment x, segment y) {
  return x.second.first > y.second.first;
}

// segment tree functions
int getSum(int segTree[], int qleft, int qright, int left, int right, int pos) {

  if (left > right) {
    return 0;
  }
  
  // total overlap
  if (qleft <= left && qright >= right) {
    return segTree[pos];
  }

  // no overlap
  if (qleft > right || qright < left) {
    return 0;
  }

  // partial overlap
  int mid = (left + right) / 2;
  return  getSum(segTree, qleft, qright, left, mid, (2 * pos) + 1) +
          getSum(segTree, qleft, qright, mid + 1, right, (2 * pos) + 2);
}

void updatePoint(int segTree[], int index, int diff, 
                int left, int right, int pos) {
  
  if (left > right) { return; }

  // index is outside the segment range
  if (index > right || index < left) { return; }

  // update node and recur on children
  segTree[pos] += diff;
  if (right != left) {
    int mid = (left + right) / 2;
    updatePoint(segTree, index, diff, left, mid, pos * 2 + 1);
    updatePoint(segTree, index, diff, mid + 1, right, pos * 2 + 2);
  }
}

int main() {
  int n;
  cin >> n;
  int dim = 2 * n;

  vector<segment> segs;
  segs.reserve(n);
  vector<int64_t> values;
  values.reserve(dim);

  int l, r;
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

  // setup segment tree
  int STdim = 0;
  if (IsPowerOfTwo(dim)) STdim = 2 * n - 1;
  STdim = 2 * nextPowerOfTwo(dim) - 1;

  int* segTree = (int*) malloc(sizeof(int) * STdim);
  for (int i = 0; i < STdim; i++) {
    segTree[i] = 0;
  }
  vector<int> ans (n, 0);
  
  // add one to the right end of the seg and return prefix sum
  // until that index (values found will be segments ended before 
  // and also started before, because of the sorting)
  for (int i = 0; i < segs.size(); i++) {
    updatePoint(segTree, segs[i].second.second, 1, 0, dim - 1, 0);
    ans[segs[i].first] = getSum(segTree, 0, segs[i].second.second, 0, dim - 1, 0) - 1;
  }

  for (int i = 0; i < n; i++) {
		cout << ans[i] << endl;
	}
  return 0;
}