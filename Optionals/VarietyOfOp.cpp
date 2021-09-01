#include <iostream>

using namespace std;

int solve (int a, int b) {
  if (a == 0 && b == 0) return 0;
  if (a == b && a != 0) return 1;
  int diff = abs(a - b);
  if (diff % 2 == 0) return 2;
  else return -1;
}

int main() {
  int n;  // number of tests
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a;
    cin >> b;
    cout << solve(a, b) << endl;
  }
}