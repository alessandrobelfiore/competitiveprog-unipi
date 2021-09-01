/*  Using mergesort, each time we pick from the right array
    during a merge, we add to the number of inversions the 
    number of elements still to be merged in the left array
 */

#include <vector>
#include <iostream>
#include <climits>

using namespace std;

int MAX = INT_MAX;
int64_t inv = 0;

vector<int> merge(vector<int> a, vector<int> b) {
  int size = a.size() + b.size();
  vector<int> merged;
  merged.reserve(size);
  a.push_back(MAX);
  b.push_back(MAX);

  int i = 0;
  int j = 0;

  for (int k = 0; k < size; k++) {
    if (a[i] <= b[j]) {
      merged.push_back(a[i]);
      i++;
    } else {
      merged.push_back(b[j]);
      j++;
      // add to inversions all elemts still on left side
      inv += (a.size() - 1) - i;
    }
  }
  return merged;
}

vector<int> mergeSort(vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;
    auto ans = merge(mergeSort(arr, left, mid), mergeSort(arr, mid + 1, right));
    return ans;
  }
  else {
    vector<int> a;
    a.push_back(arr[left]);
    return a;
  }
}

int main() {
  int n;
  cin >> n;
  
  vector<int> vect;
  vector<int64_t> anss;
  anss.reserve(n);
  for (int i = 0; i < n; i++) {
    int dim;
    cin >> dim;
    vect.reserve(dim);

    for (int j = 0; j < dim; j++) {
      int x;
      scanf("%d", &x);
      vect.push_back(x);
    }
    mergeSort(vect, 0, vect.size() - 1);
    anss.push_back(inv);
    vect.clear();
    inv = 0;
  }

  for (auto x : anss) {
    cout << x << endl;
  }
}