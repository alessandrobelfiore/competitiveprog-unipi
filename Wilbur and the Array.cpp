#include <iostream>

using namespace std;

void computeMinSteps(long long int l, long long int* arr) {
  long long int res = abs(arr[0]);
  for (long j = 1; j < l; j++) {
    res += abs(arr[j] - arr[j - 1]);
  }
  cout << res;
}

int main () {
  long length;
  cin >> length;
  long long int* arr = (long long int*) malloc(sizeof(long long int) * length);
  for (long i = 0; i < length; i++) {
    cin >> arr[i];
  }
  computeMinSteps(length, arr);
  return 0;
}