#include <algorithm>
// faster implementation
class Solution {
    public:
    // binary search that returns -1 if target is found, the closest greater number o.w.
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

    // return length of longest strictly increasing subsequence
    int longestSubsequence(int n, int a[])
    {
          
      int* arr = new int[n]();
      
      // initialization step
      arr[0] = a[0];
      int max = arr[0];
      int max_index = 0;
      
      // general step
      for (int i = 1; i < n; i++) {
        if (a[i] > max) {
          max = a[i];
          max_index++;
          arr[max_index] = max;
        } else {
          int index = binarySearch(arr, a[i], max_index);
          if (index != -1) {
            arr[index] = a[i];
            if (index == max_index) {
              max = arr[index];
            }
          }
        }
      }
      
      return max_index + 1;
    }
};