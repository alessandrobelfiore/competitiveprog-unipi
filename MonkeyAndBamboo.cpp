#include <iostream>

using namespace std;

int solve(int n, int arr[]) {

  if (n == 1) return arr[0];

  int force = 0;
  int dst = 0;
  for (int i = n - 1; i > 0; i--) {
    dst = abs(arr[i] - arr[i - 1]);
    if (dst > force) force = dst;
    else if (dst == force) force ++;
  }
  dst = abs(arr[0] - 0);
  if (dst > force) force = dst;
  else if (dst == force) force ++;
  return force;
}

int main () {
  int n_tests;
  cin >> n_tests;
  int* res = (int*) malloc(sizeof(int) * n_tests);

  for (int i = 0; i < n_tests; i++) {
    int n;
    cin >> n;
    int* arr = (int*) malloc(sizeof(int) * n);
    for (int j = 0; j < n; j++) {
      cin >> arr[j];
    }
    res[i] = solve(n, arr);
  }

  for (int i = 0; i < n_tests; i++) {
    cout << "Case " << i + 1 << ": " << res[i] << endl;
  }
}