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

bool comp (triple i, triple j) {
  if ((get<0>(i) / sqrtN) != (get<0>(j) / sqrtN))
    return (get<0>(i) / sqrtN) < (get<0>(j) / sqrtN);
  return (get<1>(i)) < (get<1>(j));
}

void solve(int n, int arr[], int q, vector<triple> queries) {
  int max = 10000000;
  vector<long long> anss (q, 0);
  sort (queries.begin(), queries.end(), comp);
  
  int cnt_r = -1;
  int cnt_l = 0;
  long long ans = 0;
  vector<int> occs (max, 0);
  for (int i = 0; i < q; i++) {
    int n_query = get<2>(queries[i]);
    while (cnt_l < get<0>(queries[i])) {
      occs[arr[cnt_l]] --;
      if (occs[arr[cnt_l]] == 0) ans -= arr[cnt_l];
      else if (occs[arr[cnt_l]] > 0) ans -= (occs[arr[cnt_l]] * 2 + 1) * arr[cnt_l];
      cnt_l ++;
    }
    while (cnt_l > get<0>(queries[i])) {
      cnt_l --;
      occs[arr[cnt_l]] ++;
      if (occs[arr[cnt_l]] == 1) ans += arr[cnt_l];
      else if (occs[arr[cnt_l]] > 0) ans += (occs[arr[cnt_l]] * 2 - 1) * arr[cnt_l];
    }
    while (cnt_r < get<1>(queries[i])) {
      cnt_r ++;
      occs[arr[cnt_r]] ++;
      if (occs[arr[cnt_r]] == 1) {ans += arr[cnt_r];}
      else if (occs[arr[cnt_r]] > 0) ans += (occs[arr[cnt_r]] * 2 - 1) * arr[cnt_r];
    }
    while (cnt_r > get<1>(queries[i])) {
      occs[arr[cnt_r]] --;
      if (occs[arr[cnt_r]] == 0) {ans -= arr[cnt_r];}
      else if (occs[arr[cnt_r]] > 0) ans -= (occs[arr[cnt_r]] * 2 + 1) * arr[cnt_r];
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
  sqrtN = ceil(sqrt(n));

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