#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int solve(vector<int>& arr, int odd, int even, int dim) {
  if (abs(odd - even) > 1) return -1;
  if (dim == 1) return 0;

  int ans = 0;
  int solveEven = 0; int solveOdd = 0;
  int oddIndex = 0; int evenIndex = 1;  // next index where we need an odd/even value

  // check both starting with odd or even
  if (odd == even) {
    for (int i = 0; i < dim; i++) {
      if (arr[i] == 1) {
        solveEven += abs(evenIndex - i);
        solveOdd += abs(oddIndex - i);
        evenIndex += 2;
        oddIndex += 2;
      }
    }
    ans = solveEven < solveOdd ? solveEven : solveOdd;
    // start with odd
  } else if (odd > even) {
    for (int i = 0; i < dim; i++) {
      if (arr[i] == 1) {
        solveOdd += abs(oddIndex - i);
        oddIndex += 2;
      }
    }
    ans = solveOdd;
    // start with even
  } else {
    for (int i = 0; i < dim; i++) {
      if (arr[i] == 0) {
        solveOdd += abs(oddIndex - i);
        oddIndex += 2;
      }
    }
    ans = solveOdd;
  }
  return ans;
}


int main() {
  int n;
  cin >> n;
  int dim = 0;
  vector<int> arr;
  int odd = 0;
  int even = 0;

  for (int i = 0; i < n; i++) {
    cin >> dim;
    arr.clear();
    arr.reserve(dim);
    odd = 0;
    even = 0;
    for (int j = 0; j < dim; j++) {
      int x;
      cin >> x;
      if (x % 2 == 0) {
        even++;
        arr.push_back(0);
      }
      else {
        odd++;
        arr.push_back(1);
      }
    }
    cout << solve(arr, odd, even, dim) << endl;
  }
}