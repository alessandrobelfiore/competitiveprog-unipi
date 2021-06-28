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
    if (l != 1)
        freq[l - 2] --;
  }

  // prefix sum OUT OF BOUND ? FIXME
  for (int64_t i = n - 1; i >= 0; i--) {
    freq[i - 1] += freq[i];
  }

  computeMaxSum(freq, arr, n, q);
	return 0;
}