/*  We need to find the minimum vertex cover set in a n-ary tree.
    We use recursion to find out each step if is better to take the root
    of the current subtree or all of its children.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solveVC(vector<vector<int>> &matrix,
            vector<vector<int>> &supp, int index, int parent) {
  /* cout << "index: " << index << " parent: " << parent << endl; */
  for (auto x : matrix[index]) {
    if (x != parent) {
      solveVC(matrix, supp, x, index);
      supp[0][index] += supp[1][x];
      supp[1][index] += min(supp[0][x],
                            supp[1][x]);
    }
  }
  supp[1][index]++;
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
  vector<vector<int>> vc;
  vc.push_back(std::vector<int>(adj.size(), 0));
	vc.push_back(std::vector<int>(adj.size(), 0));

  // setup the matrix of adjacencies to represent the tree
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x;
    cin >> y;

    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  solveVC(adj, vc, 0, -1);

  /* for (auto x : adj) {
    for (auto y : x) {
      cout << y + 1 << " ";
    }
    cout << endl;
  } */

  int ans = min(vc[0][0], vc[1][0]);
  cout << ans << endl;
}