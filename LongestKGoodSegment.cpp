/*  We need to find the longest segment which contains no more than k distinct digits.
    We keep counts of the occurences of each digits, moving the right bound of the segment 
    until the segment is no good anymore, then we move the left segment by 1.
  */

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

const int N = 1000001;

void solve(long* arr, long k, long n) {

  // array size n to store number of occurences of all n
  int* occs = (int*) malloc(sizeof(int) * N);
  memset(occs, 0, sizeof(occs));

  long distinct = 0; // number of distinct occurences
  pair<long, long> ans = make_pair(-1, -1); // best bounds found so far
  int index = 0;
  // i -> left end, index -> right end
  for (long i = 0; i < n; i++) {
    // move right bound until segment in no good
    while (index < n) {
      if (++occs[arr[index]] == 1) distinct++;
      // when segment is no good interrupt
      if (distinct > k) {
        if (--occs[arr[index]] == 0) distinct--;
        break;
      }
      index++;
    }
    // check if calculated boounds are better than the current max
    if ((ans.second - ans.first) < (index - i)) ans.first = i, ans.second = index;
    // restart moving left bound by 1
    if (--occs[arr[i]] == 0) distinct--;
  }

  cout << ans.first + 1 << " " << ans.second << endl; 
}

int main() {
  long n = 0;
  long k = 0;
  cin >> n;
  cin >> k;
  long* arr = (long*) malloc(sizeof(long) * n);
  for (long i = 0; i < n; i ++) {
    long x = 0;
    scanf("%ld", &x);
    arr[i] = x;
  }
  // return longest k-good segment
  solve(arr, k, n);
	return 0;
}