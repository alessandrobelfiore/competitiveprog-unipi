#include <iostream>
#include <vector>
using namespace std;

void numberOfWays(int64_t arr[], int64_t size, int64_t sum) {
  int64_t total = 0;
  int64_t currentSum = 0;

  // not divisible for 3
  if (sum % 3 != 0) {
    cout << 0 << endl;
    return;
  }

  // set one whenever we can split
  int64_t* suffix = (int64_t*) malloc(sizeof(int64_t) * size);
  
  for (int64_t i = 0; i < size; i++) {
    suffix[i] = 0;
  }
  
  
  for (int64_t i=(size - 1); i >= 0; i--) {
    currentSum += arr[i];
    if (currentSum == sum / 3) {
      suffix[i] = 1;
     }
  }

  // suffix sum
  for (int64_t i=(size - 2); i >= 0; i--) {
    suffix[i] += suffix[i + 1];
  }

  currentSum = 0;
  for (int64_t i=0; i < size - 2; i++) {
    currentSum += arr[i];
    if (currentSum == sum / 3) {
      total += suffix[i + 2];
    }
  }

  cout << total;
  return;
}

int main() {
  int64_t n = 0;
  int64_t sum = 0;
  cin >> n;
  int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * n);
  for (int64_t i = 0; i < n; i ++) {
    int64_t x = 0;
    cin >> x;
    arr[i] = x;
    sum += x;
  }
  numberOfWays(arr, n, sum);
    return 0;
}