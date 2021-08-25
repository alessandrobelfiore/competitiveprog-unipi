/*  We have an array and a number of queries. For each query l, r we have to return the sum of the elements
    from l to r but we have to reorder the array first, in order to obtain the max result possible.
    We compute the frequencies of the indices based on the number of queries that contain them,
    and we build the prefix sum of the frequencies. Then we order the array and the frequencies in the same
    order, so we can pick the max number the max number of frequencies. 
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void computeMaxSum(int64_t arr[], int64_t freq[], int64_t n, int64_t q) {

  int64_t sum = 0;
  vector<int64_t> vect(arr, arr + n);
  vector<int64_t> freqV(freq, freq + n);

  // sort frequencies
  std::sort(freqV.begin(), freqV.end()); 

  // sort array
  std::sort(vect.begin(), vect.end());

  for (int64_t i = 0; i < n; i++) {
    sum += freqV[i] * vect[i];
  }

  cout << sum << endl;
}


int main() {
  int64_t n, q = 0;
  cin >> n;
  cin >> q;
  int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * n);
  int64_t* freq = (int64_t*) malloc(sizeof(int64_t) * n);

  for (int64_t i = 0; i < n; i++) {
    int64_t x = 0;
    cin >> x;
    arr[i] = x;
    freq[i] = 0;
  }

  for (int64_t i = 0; i < q; i++) {
    int64_t l, r = 0;
    cin >> l;
    cin >> r;
    freq[r - 1] ++;
    if (l != 1) freq[l - 2] --;
  }

  // prefix sum 
  for (int64_t i = n - 1; i >= 0; i--) {
    freq[i - 1] += freq[i];
  }

  computeMaxSum(freq, arr, n, q);
	return 0;
}