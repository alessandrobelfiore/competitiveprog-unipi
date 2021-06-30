#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
    // return length of the longest bitonic subsequence
    
    int LongestBitonicSequence(vector<int>nums)
    {
      // compute LIS
      int n = nums.size();
      int* lis = new int[n];
       
      // initialization step
      lis[0] = 1;
      
      // general step
      for (int i = 1; i < n; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++) { 
          if (nums[i] > nums[j] && lis[i] < lis[j] + 1) {
            lis[i] = lis[j] + 1;
          }
        }
      }

      // compute LDS
      int* lds = new int[n];
       
      // initialization step
      lds[n - 1] = 1;
      
      // general step
      for (int i = n - 2; i >= 0; i--) {
        lds[i] = 1;
        for (int j = n - 1; j > i; j--) {
          if (nums[i] > nums[j] && lds[i] < lds[j] + 1) {
            lds[i] = lds[j] + 1;
          }
        }
      }

      // compute LBS
      int* lbs = new int[n];
      int max = -1;

      // general step
      for (int i = 0; i < n; i++) {
        lbs[i] = lis[i] + lds[i];
        if (lbs[i] > max) max = lbs[i];
      }
        
      return max - 1;
    }
};