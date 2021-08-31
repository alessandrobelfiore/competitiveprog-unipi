/*  We need to find the next larger element of each element in the array.
    We mantain a queue in which we insert one element at a time, in order to find
    its NLE. We then read elements of the array one element to the right from the last
    element inserted in the queue and save the answer if they are greater than some 
    elements in the queue.
 */

#include <iostream>
#include <deque>
#include <vector>
#include <utility>   
using namespace std;

// use this in G4G site
class Solution {
  public:
  vector<long long> nextLargerElement(vector<long long> arr, int n){
    deque<pair <long, long>> support;   // array of elements for which we still look for NLE
    deque<pair <long, long>>::iterator it = support.begin();
    
    vector<long long> solutions(n, -1);
    vector<long long>::iterator it1 = solutions.begin();
    
    support.push_front(make_pair(arr[0], 0));
    // loop through array left to right
    for (long i = 1; i < n; i++) {
      it = support.begin();
      // loop through supp array and check if curr value is 
      // greater than some values that still need NLE
      while (it != support.end()) {
        if (arr[i] > (*it).first) {
          int index = support.front().second;
          solutions.at(index) = arr[i];
          support.pop_front();
          it++;
        } else break;
      }
      support.push_front(make_pair(arr[i], i));
    }
    return solutions;
  }
};

void printNLE(long array[], long length) {
  deque<pair <long, long>> support;
  deque<pair <long, long>>::iterator it = support.begin();
  
  vector<long> solutions(length, -1);
  vector<long>::iterator it1 = solutions.begin();

  support.push_front(make_pair(array[0], 0));
  for (long i = 1; i < length; i++) {
    it = support.begin();
    while (it != support.end()) {
      if (array[i] > (*it).first) {
        int index = support.front().second;
        //cout << index << " ";
        solutions.at(index) = array[i];
        support.pop_front();
        //cout << array[i] << " ";
        it++;
      } else break;
    }
    support.push_front(make_pair(array[i], i));
  }
  
  for (vector<long>::iterator it = solutions.begin() ; it != solutions.end(); ++it)
    cout << *it << ' ';
  cout << endl;
}

int main() {
    int n_tests = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        long length = 0;
        cin >> length;
        long* arr = (long*) malloc(sizeof(long) * length);
        for (int j = 0; j < length; j ++) {
            long x = 0;
            cin >> x;
            arr[j] = x;
        }
        printNLE(arr, length);
    }
	return 0;
}