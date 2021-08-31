/*  Maintain a queue of maximal elements, if we encounter new max we erase all,
    if we encounter a value greater than the least contained we insert it and delete the
    values smaller than it(inserted before it, so they are going to exit the window before it)
 */

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// use this to test on G4G site
class Solution
{
  public:
    //Function to find maximum of each subarray of size k.
    vector <int> max_of_subarrays(int *arr, int n, int k)
    {
      vector<int> solutions;
      solutions.reserve(k);
      deque<int> windowQ;
      windowQ.push_front(0);
  
      // initial step (k comparison) 
  
      for (int i=0; i<k; i++) {
        // new max -> erase queue, insert element
        if (arr[windowQ.front()] <= arr[i]) {
          windowQ.clear();
          windowQ.push_front(i);
        } 
        // not the maximum, insert at the back and erase elements smaller 
        // to the left
        else {
          while (!windowQ.empty() && arr[windowQ.back()] <= arr[i]) {
            windowQ.pop_back();
          }
          windowQ.push_back(i);  
        }
      }
      solutions.push_back(arr[windowQ.front()]);
      
      // n-k steps 
  
      for (int i=k; i<n; i++) {
        // pop old max 
        if (windowQ.front() <= (i - k)) {
          windowQ.pop_front();
        }
        // new max -> erase queue, insert element
        if (windowQ.empty() || arr[windowQ.front()] <= arr[i]) {
          windowQ.clear();
          windowQ.push_front(i);
        } 
        // not the maximum, insert at the back and erase elements smaller 
        // to the left
        else {
          while (arr[windowQ.back()] <= arr[i]) {
            windowQ.pop_back();
          }
          windowQ.push_back(i);  
        }
        solutions.push_back(arr[windowQ.front()]);
      }
      return solutions;
    }
};

// local tests
int slidingWindowMax(int arr[], int start, int end, int k) {

    vector<int> solutions;
    solutions.reserve(k);
    deque<int> windowQ;
    windowQ.push_front(0);

    // initial step (k comparison) 

    for (int i=0; i<k; i++) {
        // new max -> erase queue, insert element
        if (arr[windowQ.front()] <= arr[i]) {
            windowQ.clear();
            windowQ.push_front(i);
        } 
        // not the maximum, insert at the back and erase elements smaller 
        // to the left
        else {
            while (!windowQ.empty() && arr[windowQ.back()] <= arr[i]) {
                windowQ.pop_back();
            }
            windowQ.push_back(i);  
        }
    }
    solutions.push_back(arr[windowQ.front()]);

    // n-k steps 

    for (int i=k; i<end; i++) {
        // pop old max 
        if (windowQ.front() <= (i - k)) {
            windowQ.pop_front();
        }
        // new max -> erase queue, insert element
        if (windowQ.empty() || arr[windowQ.front()] <= arr[i]) {
            windowQ.clear();
            windowQ.push_front(i);
        } 
        // not the maximum, insert at the back and erase elements smaller 
        // to the left
        else {
            while (arr[windowQ.back()] <= arr[i]) {
                windowQ.pop_back();
            }
            windowQ.push_back(i);  
        }
        solutions.push_back(arr[windowQ.front()]);
    }

    for (vector<int>::iterator it = solutions.begin(); it != solutions.end(); ++it)
        cout << *it << ' '; 
    cout << endl;
}

int main() {
	int n_tests = 0;
    int k = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        int length = 0;
        cin >> length;
        cin >> k;
        int* arr = (int*) malloc(sizeof(int) * length);
        for (int j = 0; j < length; j ++) {
            int x = 0;
            cin >> x;
            arr[j] = x;
        }
        slidingWindowMax(arr, 0, length - 1, k);
    }
	return 0;
}