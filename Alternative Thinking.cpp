#include <iostream>

using namespace std;

void solve(int l, int* arr) {
  int res = 1;
  int current = arr[0];
  int current_l = 1;
  int prec_l = 0;
  int flag = 0;
  for (int i = 1; i < l; i++) {
    if (arr[i] == current) {
      current_l ++;
    }
    else {
      res++;
      current = arr[i];
      prec_l = current_l;
      current_l = 1;
    }
    if (current_l >= 2 && prec_l >= 2) flag = 1;
    if (current_l >= 3) flag = 1;
  }
  if (flag == 1) res += 2;
  else if (l >= 2) {
    if (arr[0] == arr[1] || arr[l - 1] == arr[l - 2]) res ++;
  }
  cout << res << endl;
}

int main () {
  int arr[100000] {};
  int length;
  cin >> length;
  /* int* arr = (int*) malloc(sizeof(int) * length); */
  for (int i = 0; i < length; i++) {
    cin >> arr[i];
  }
  solve(length, arr);
  return 0;
}