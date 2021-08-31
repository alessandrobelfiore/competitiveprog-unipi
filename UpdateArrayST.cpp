/*  We need to perform a number of range updates on an array, and then
    answer a number of queries. We do this employing a Segment Tree.
    Since the array is initially all zeroes we can simply return the
    prefix sum until the index requested.
 */

#include <iostream>
#include <vector>

using namespace std;

bool IsPowerOfTwo(int x) {
  return (x != 0) && ((x & (x - 1)) == 0);
}

int nextPowerOfTwo(int x) {
  int power = 1;
  while(power < x)
    power*=2;
  return power;
}

int64_t getSum(int64_t segTree[], int qleft, int qright, int left, int right, int pos) {

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
  int64_t mid = (left + right) / 2;
  return  getSum(segTree, qleft, qright, left, mid, (2 * pos) + 1) +
          getSum(segTree, qleft, qright, mid + 1, right, (2 * pos) + 2);
}

void updatePoint(int64_t segTree[], int index, int64_t diff, 
                int left, int right, int pos) {
  
  if (left > right) { return; }

  // index is outside the segment range
  if (index > right || index < left) { return; }

  // update node and recur on children
  segTree[pos] += diff;
  if (right != left) {
    int64_t mid = (left + right) / 2;
    updatePoint(segTree, index, diff, left, mid, pos * 2 + 1);
    updatePoint(segTree, index, diff, mid + 1, right, pos * 2 + 2);
  }
}

int main() {
  int n_test;
  cin >> n_test;

  for (int i = 0; i < n_test; i++) {
    int n, u;
    cin >> n; // number of elements,
    cin >> u; // number of updates

    int64_t STdim = 0; // dimension of the segment tree
    if (IsPowerOfTwo(n)) STdim = 2 * n - 1;
    else STdim = 2 * nextPowerOfTwo(n) - 1;

    int64_t* segTree = (int64_t*) malloc(sizeof(int64_t) * STdim);

    int l, r, v;
    for (int j = 0; j < u; j++) {
      scanf("%d%d%d", &l, &r, &v);
      updatePoint(segTree, l, v, 0, n - 1, 0);
      updatePoint(segTree, r + 1, (-1) * v, 0, n - 1, 0);
    }
    int q;
    cin >> q;
    int x;
    for (int k = 0; k < q; k++) {
      scanf("%d", &x);
      cout << getSum(segTree, 0, x, 0, n - 1, 0) << endl;
    }
  }
  return 0;
}