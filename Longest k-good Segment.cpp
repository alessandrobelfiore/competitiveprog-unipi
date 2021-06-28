#include <iostream>
#include <algorithm>
#include <set> 
using namespace std;

void longestKGood(int arr[], int k, int n) {

  //FIXME count from 1!
  pair<int, int> currentBounds = make_pair(0,0);
  pair<int, int> maxBounds = make_pair(0, 0);
  int current_max, max_length, i = -1;
  int distinct = 0;

  // temporary structure: set (index, last occur)
  auto cmp = [](pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
  };
  set<pair<int, int>, decltype(cmp)> tree(cmp);

  while(++i < n) {
    // lookup arr[i] in tree
    int value = arr[i];
    auto item = std::find_if(tree.begin(), tree.end(), 
      [&value](std::pair<int, int> const & ref) {
        return ref.first == value;
        }
    );
    if (item != tree.end())
    // already present
    { 
      currentBounds.second = i;
      current_max++;
      // update last occurence
      tree.erase(item);
      tree.insert(make_pair(arr[i], i));
    }
    // not present
    else 
    // add in tree
      {
      // still good
      if (distinct <= k) {
        distinct++;
        currentBounds.second = i;
        current_max++;
        tree.insert(make_pair(arr[i], i));
      }
      // not good anymore
      else {
        // save bounds if they are max until now
        if (current_max >= max_length) {
          maxBounds = currentBounds;
        }
        currentBounds.second = i;

        // find least last occurrence of a value
        int lastOccurence = INT_MAX;
        int culprit = 0;
        for (auto x : tree) {
          if (x.second < lastOccurence)  {
            lastOccurence = x.second;
            culprit = x.first;
          }
        }
        tree.erase(make_pair(culprit, lastOccurence));
        currentBounds.first = lastOccurence + 1;
        current_max = currentBounds.second - currentBounds.first;
      }
    }
  }
  cout << maxBounds.first + 1 << " " << maxBounds.second + 1 << endl;
}




int main() {
    int n, k = 0;
    cin >> n;
    cin >> k;
    int* arr = (int*) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i ++) {
      int x = 0;
      cin >> x;
      arr[i] = x;
    }
    // return longest k-good segment
    longestKGood(arr, k, n);
	return 0;
}