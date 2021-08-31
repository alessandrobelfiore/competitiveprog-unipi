/*    We use 2 arrays to save the maximum height of the towers on the left and on the right of the index.
      The solution is difference between the minimum of these 2 values and the value at the current index
 */

#include <iostream>
using namespace std;

// use this to test on G4G site
class Solution{

  // Function to find the trapped water between the blocks.
  public:
  int trappingWater(int arr[], int n){
    int* sxBound = (int*) malloc(sizeof(int) * n);
    int* dxBound = (int*) malloc(sizeof(int) * n);
    int sum = 0;

    int sxMax = arr[0];
    sxBound[0] = sxMax;
    for (int i = 1; i < n; i++) {
      if (arr[i] >= sxMax) sxMax = arr[i];
      sxBound[i] = sxMax;
    }

    int dxMax = arr[n - 1];
    dxBound[n - 1] = dxMax;
    for (int i = n - 2; i >= 0; i--) {
      if (arr[i] >= dxMax) dxMax = arr[i];
      dxBound[i] = dxMax;
      int min = sxBound[i] < dxBound[i] ? sxBound[i] : dxBound[i];
      sum += (min - arr[i]);
    }

    return sum;
  }
};