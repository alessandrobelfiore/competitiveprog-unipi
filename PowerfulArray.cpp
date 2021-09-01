/* Mo's alg */

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <tuple>

using namespace std;
typedef pair<int, int> pairs;
typedef tuple<int, int, int> triple;

int sqrtN;

// sort left end between buckets of sqrt(N), or if they belong to same buckets
// sort by right end
bool comp (triple i, triple j) {
  if ((get<0>(i) / sqrtN) != (get<0>(j) / sqrtN))
    return (get<0>(i) / sqrtN) < (get<0>(j) / sqrtN);
  return (get<1>(i)) < (get<1>(j));
}

int add(vector<int>& occs, int val) {
  occs[val] ++;
  if (occs[val] == 1) return val;
  else if (occs[val] > 0) return (occs[val] * 2 - 1) * val;
  return 0;
}

int remove(vector<int>& occs, int val) {
  occs[val] --;
  if (occs[val] == 0) return val;
  else if (occs[val] > 0) return (occs[val] * 2 + 1) * val;
  return 0;
}

void solve(int n, int arr[], int q, vector<triple> queries) {
  int max = 10000000;
  vector<long long> anss (q, 0);
  sort (queries.begin(), queries.end(), comp);    // sort in buckets
  
  int cnt_r = -1;
  int cnt_l = 0;
  long long ans = 0;
  vector<int> occs (max, 0);  //  occurences
  for (int i = 0; i < q; i++) {
    int n_query = get<2>(queries[i]);
    while (cnt_l < get<0>(queries[i])) {
      ans -= remove(occs, arr[cnt_l]);
      cnt_l ++;
    }
    while (cnt_l > get<0>(queries[i])) {
      cnt_l --;
      ans += add(occs, arr[cnt_l]);
    }
    while (cnt_r < get<1>(queries[i])) {
      cnt_r ++;
      ans += add(occs, arr[cnt_r]);
    }
    while (cnt_r > get<1>(queries[i])) {
      ans -= remove(occs, arr[cnt_r]);
      cnt_r --;
    }
    anss[n_query] = ans;
  }

  for (int i = 0; i < anss.size(); i++) {
    cout << anss[i] << endl;
  }
}

int main() {
  // array length, queries number
  int n, q;
  cin >> n;
  cin >> q;
  int* arr = (int*) malloc(sizeof(int) * n);
  vector<triple> queries (q);
  sqrtN = ceil(sqrt(n)); // bucket size

  for (int i = 0; i < n; i ++) {
    cin >> arr[i];
  }

  for (int j = 0; j < q; j ++) {
    int l, r;
    cin >> l;
    cin >> r;
    queries[j] = make_tuple(l - 1, r - 1, j);
  }
  
  solve(n, arr, q, queries);
}