/*  Range minimum query using segment tree and lazy propagation. 
    The array is circular so if left index < right index,  we split the query in 2.
 */

#include <iostream>
#include <climits>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>
#include <inttypes.h>

using namespace std;

int64_t MAX = LONG_MAX;

bool IsPowerOfTwo(int x) {
  return (x != 0) && ((x & (x - 1)) == 0);
}

int nextPowerOfTwo(int x) {
  int power = 1;
  while(power < x)
    power*=2;
  return power;
}

void constructST(int64_t input[], int64_t segTree[], int left, int right, int pos) {
  // base case
  if (left == right) {
    segTree[pos] = input[left];
    return;
  }

  int64_t mid = (left + right) / 2;
  constructST(input, segTree, left, mid, 2 * pos + 1); // recur to the left
  constructST(input, segTree, mid + 1, right, 2* pos + 2); // recur to the right;

  // range minimum query ST
  segTree[pos] = min(segTree[2 * pos + 1], segTree[2 * pos + 2]);
}

int64_t RMQLazy(int64_t segTree[], int64_t lazy[], int qleft, int qright, int left, int right, int pos) {

  if (left > right) {
    return MAX;
  }

  // check if there are updates pending in lazy tree
  if (lazy[pos] != 0) {
    segTree[pos] += lazy[pos];
    if (left != right) {
      lazy[2 * pos + 1] += lazy[pos];
      lazy[2 * pos + 2] += lazy[pos];
    }
    lazy[pos] = 0;
  }
  
  // total overlap
  if (qleft <= left && qright >= right) {
    return segTree[pos];
  }

  // no overlap
  if (qleft > right || qright < left) {
    return MAX;
  }

  // partial overlap
  int64_t mid = (left + right) / 2;
  return min( RMQLazy(segTree, lazy, qleft, qright, left, mid, (2 * pos) + 1),
              RMQLazy(segTree, lazy, qleft, qright, mid + 1, right, (2 * pos) + 2));
}


void updateLazy(int64_t segTree[], int64_t lazy[], int start, int stop, int64_t diff, 
            int left, int right, int pos) {
  
  if (left > right) { return; }

  // check no updates are pending
  if (lazy[pos] != 0) {
    segTree[pos] += lazy[pos];
    if (left != right) { // not a leaf, propagate
      lazy[2 * pos + 1] += lazy[pos];
      lazy[2 * pos + 2] += lazy[pos];
    }
    lazy[pos] = 0;
  }

  if (start > right || stop < left) { return; }

  // total overlap, update node, update lazy children
  if (start <= left && stop >= right) {
    segTree[pos] += diff;
    if (left != right) {
      lazy[2 * pos + 1] += diff;
      lazy[2 * pos + 2] += diff;
    }
    return;
  }

  // partial overlap, recur to both sides
  int64_t mid = (left + right) / 2;
  updateLazy(segTree, lazy, start, stop, diff, left, mid, pos * 2 + 1);
  updateLazy(segTree, lazy, start, stop, diff, mid + 1, right, pos * 2 + 2);

  segTree[pos] = min(segTree[pos * 2 + 1], segTree[pos * 2 + 2]);
  }


int main() {
  int n; // dimension of the array
  cin >> n;

  int64_t STdim = 0; // dimension of the segment tree
  if (IsPowerOfTwo(n)) STdim = 2 * n - 1;
  else STdim = 2 * nextPowerOfTwo(n) - 1;

  int64_t* segTree = (int64_t*) malloc(sizeof(int64_t) * STdim);
  int64_t* lazyTree = (int64_t*) malloc(sizeof(int64_t) * STdim);
  int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * n);
  vector<int64_t> anss;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    arr[i] = x;
  }

  // build the ST
  constructST(arr, segTree, 0, n - 1, 0);

  // initialize lazy tree
  for (int j = 0; j < STdim; j++) {
    lazyTree[j] = 0;
  }

  int64_t m; // number of queries
  cin >> m;

  for (int i = 0; i < m + 1; i++) {
    string str;
		vector <int> words;

		getline(cin, str);
		stringstream ss(str);

    int var;
		while (ss >> var)
			words.push_back(var);
		
		if (words.size() == 0)
			continue;

    // RMQ query
    if (words.size() == 2) {
      int left = words[0];
      int right = words[1];
      if (left <= right) anss.push_back(RMQLazy(segTree, lazyTree, left, right, 0, n - 1, 0));
      else {
        int64_t ans = min(RMQLazy(segTree, lazyTree, left, STdim - 1, 0, n - 1, 0), 
                      RMQLazy(segTree, lazyTree, 0, right, 0, n - 1, 0));
        anss.push_back(ans);
      }
    }

    // update query
    else if (words.size() == 3) {
      int64_t left = words[0];
      int64_t right = words[1];
      if (left <= right) updateLazy(segTree, lazyTree, left, right, words[2], 0, n - 1, 0);
      else {
        updateLazy(segTree, lazyTree, left, STdim - 1, words[2], 0, n - 1, 0);
        updateLazy(segTree, lazyTree, 0, right, words[2], 0, n - 1, 0);
      }
    }
  }

  for (auto x : anss) {
    cout << x << "\n";
  }
}