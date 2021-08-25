/*  We need to find the minimum vertex cover set in a n-ary tree.
    We use recursion to find out each step if is better to take the root
    of the current subtree or all of its children.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solveVC(vector<vector<int>>* matrix, vector<int>* supp, int index) {
  
  //  if we already calculated this subtree vc
  if (supp->at(index) != -1) return supp->at(index);

  // if it has not children
  if (matrix->at(index).size() == 0) {
    /* cout << index + 1 << " empty" << endl; */
    supp->at(index) = 0;
    return 0;
  }

  // if we take the root
  int withRoot = 1;
  for (auto x : matrix->at(index)) {
    withRoot += solveVC(matrix, supp, x);
  }

  // if we take all children of the root instead
  int withoutRoot = matrix->at(index).size();
  for (auto x : matrix->at(index)) {
    for (auto y : matrix->at(x)) {
      withoutRoot += solveVC(matrix, supp, y);
    }
  }

  // store the calculated min vc before returning it
  int min = withRoot >= withoutRoot ? withoutRoot : withRoot;
  supp->at(index) = min;
  return min;
}


int main() {
  int n;
  cin >> n; // number of vertices

  if (n == 1) {
    cout << "1" << endl;
    return 0;
  }

  vector<vector<int>> adj(n);
  // saved previous solutions
  vector<int> support(n, -1);
  // introduced to permit trees with parent with higher index than children
  vector<int> used(n, -1);

  // setup the matrix of adjacencies to represent the tree
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x;
    cin >> y;
    int min, max = 0;
    
    if (x < y) {
      min = x;
      max = y;
    } else {
      min = y;
      max = x;
    }

    if (used[min - 1] != -1 || i == 0) {
      adj[min - 1].push_back(max - 1);
      used[max - 1] = 1;
    }
    else {
      adj[max - 1].push_back(min - 1);
      used[min - 1] = 1;
    }
  }

  int root;

  // find the actual root?
  for (int j = 0; j < used.size(); j++) {
    if (used[j] == -1) root = j;
  }

  /* for (auto x : adj) {
    for (auto y : x) {
      cout << y + 1 << " ";
    }
    cout << endl;
  } */

  /* cout << root << endl; */
  int ans = solveVC(&adj, &support, root);
  cout << ans << endl;
}