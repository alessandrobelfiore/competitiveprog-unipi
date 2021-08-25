/*  We just need to compute a prefix sum of the characters equal in the string,
    and for each query return the difference between the value of the right end 
    and the left one.
 */

#include <iostream>
#include <string>
using namespace std;

int* computePrefixSum(string s) {
  int n = s.size();
  int* sums = (int* ) malloc(sizeof(int) * n);
  sums[0] = 0;
  for (int i=1; i<n; i++) {
    if (s[i] == s[i - 1]) {
      sums[i] = sums[i - 1] + 1;
    }
    else sums[i] = sums[i - 1];
  }
  return sums;
}

int main() {
  string s;
  cin >> s;
  int m = 0;
  cin >> m;
  int* sums;
  sums = computePrefixSum(s);
  for (int i = 0; i < m; i ++) {
    int l, r = 0;
    cin >> l;
    cin >> r;
    cout << sums[r - 1] - sums[l - 1] << endl;
  }
	return 0;
}