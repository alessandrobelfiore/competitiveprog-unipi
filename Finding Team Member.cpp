/*  We need to find the strongest pairings between a number of indices, given the power 
    of every couple of indices. We just sort the values and select them greedily,
    eliminating the couples we cannot choose anymore after each step.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

int findingTM(vector<tuple<long, int, int>> vect, int n) {

  int* solutions = (int*) malloc(sizeof(int) * 2 * n + 1);
  int i, j = 0;

  // sort
  std::sort (vect.begin(), vect.end());
  std::reverse(vect.begin(), vect.end());

  int index = 0;
  // until there are no non-null elements in the vector pick greedily
  while (index < vect.size()) {
    if (get<0> (vect[index]) != 0) {
      i = get<2> (vect.at(index));
      j = get<1> (vect.at(index));
      solutions[i] = j;
      solutions[j] = i;
      get<0> (vect[0]) = 0;

      // eliminate picked members
      for (int z = 1; z < vect.size(); z++) {
        if (get<0> (vect[z]) != 0 && 
            (get<1> (vect.at(z)) == j || 
            get<1> (vect.at(z)) == i || 
            get<2> (vect.at(z)) == i || 
            get<2> (vect.at(z)) == j)) {
          get<0> (vect[z]) = 0;
        }
      }
    }
    index++;
  }

  for (int k = 1; k < (2 * n) + 1; k++) {
    cout << solutions[k] << " ";
  }
  return 0;
}

int main() {
  int n = 0;
  cin >> n;
  std::vector<tuple<long, int, int>> pairings;
  pairings.reserve(2 * n);
  for (int j = 2; j <= 2 * n; j ++) {
    for (int i = 1; i < j; i ++) {
      long x = 0;
      cin >> x;
      tuple <long, int, int> t  = make_tuple(x, j, i);
      pairings.push_back(t);
    }
  }
  findingTM(pairings, n);
	return 0;
}