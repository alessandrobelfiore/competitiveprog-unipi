/*  We need to find the minimum vertex cover set in a n-ary tree.
    We use recursion to find out each step if is better to take the root
    of the current subtree or all of its children.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solveVC(vector<vector<int>>& matrix, vector<int>& supp, int index, int parent) {
  
  //  if we already calculated this subtree vc
  if (supp[index] != -1) return supp[index];

  // if we take the root, take 1 and recur on children
  int withRoot = 1;
  for (auto x : matrix[index]) {
    if (x != parent)
    withRoot += solveVC(matrix, supp, x, index);
  }

  // if we don't take root, take number of children and recur on grand-children
  int withoutRoot = matrix[index].size();
  if (parent != -1) withoutRoot--; // if I'm not on the root, subtract 1 for parent
  for (auto x : matrix[index]) {
    if (x != parent)
    for (auto y : matrix[x]) {
      if (y != index)
      withoutRoot += solveVC(matrix, supp, y, x);
    }
  }

  // store the calculated min vc before returning it
  int min = withRoot >= withoutRoot ? withoutRoot : withRoot;
  supp[index] = min;
  return min;
}


int main() {
  int n;
  cin >> n; // number of vertices

  if (n == 1) {
    cout << "1" << endl;
    return 0;
  }

  vector<vector<int>> adj(n); // adj matrix
  vector<int> support(n, -1); // saved previous solutions

  // setup the matrix of adjacencies to represent the tree
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x;
    cin >> y;

    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  int ans = solveVC(adj, support, 0, -1);
  cout << ans << endl;
}