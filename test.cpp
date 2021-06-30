#include <iostream>
#include <algorithm>

using namespace std;

int binarySearch(int arr[], int target, int end) {
      int start = 0;
  
      int ans = -1;
      while (start <= end) {
        int mid = (start + end) / 2;

        if (arr[mid] == target) return -1;
        // Move to right side if target is
        // greater.
        if (arr[mid] < target)
          start = mid + 1;

        // Move left side.
        else {
          ans = mid;
          end = mid - 1;
        }
      }
  
      return ans;
  }


int main () {
  int x;
  cin >> x;
  int* arr = (int*) malloc(sizeof(int) * x);

  for (int i = 0; i < x; i++) {
    cin >> arr[i];
  }
  int s;
  cin >> s;
  int res = binarySearch(arr, s, x);
  cout << "index: " << res << " value: " << arr[res] << endl;
  return 0;
}