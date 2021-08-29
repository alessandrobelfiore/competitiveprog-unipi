#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int sqrtN;
int n,m;
int MAX = 1000001;
int idx = -1;

vector<int> flat; // flatted array of colors 
vector<int> tin;  // starts of the subtree of i
vector<int> tout; // end of the subtree of i

struct query {
  int l, r;
  int k;
  int index;
};

void dfs (int n, int p, vector<vector<int>>& tree, vector<int>& colors) {
  tin[n] = ++idx;   // the start of the subtree is the current index
  flat[idx] = colors[n];

  for (auto it : tree[n]) {
    if (it != p) {
      dfs (it, n, tree, colors);  // recur on each child
    }
  }
  tout[n] = idx; // the end of the subtree is the index of the last child
}

bool compare(const query& a, const query& b) {
  if ((a.l / sqrtN) != (b.l / sqrtN))
    return (a.l / sqrtN) < (b.l / sqrtN);
  return a.r < b.r;
}

void add(vector<int>& occs, int color, vector<int>& kOccs) {
  occs[color] ++;
  int count = occs[color];
  kOccs[count] ++;
}

void remove(vector<int>& occs, int color, vector<int>& kOccs) {
  int count = occs[color];  // get number of occs
  occs[color] --;           // decrement it
  kOccs[count] --;
}

void solve (int n, int m, vector<int>& colors, int nColors, vector<query>& queries) {
  vector<int> anss(m, 0);

  // re-order queries
  sort (queries.begin(), queries.end(), compare);

  int cnt_r = -1;
  int cnt_l = 0;
  int ans = 0;
  int color = 0;
  vector<int> occs (nColors, 0);  // current n of colors occurences, occs[i] = x means x times color i
  vector<int> kOccs (MAX, 0);    // current n of colors that occur at least i times

  for (int i = 0; i < m; i++) {
    int n_query = queries[i].index;  // order of arrival of the query
    int k = queries[i].k;

    while (cnt_r < queries[i].r) {
      cnt_r ++;
      color = flat[cnt_r];
      add(occs, color, kOccs);
    }
    while (cnt_l < queries[i].l) {
      color = flat[cnt_l];
      remove(occs, color, kOccs);
      cnt_l ++;
    }
    while (cnt_l > queries[i].l) {
      cnt_l --;
      color = flat[cnt_l];
      add(occs, color, kOccs);
    }
    while (cnt_r > queries[i].r) {
      color = flat[cnt_r];
      remove(occs, color, kOccs);
      cnt_r --;
    }
    anss[n_query] = kOccs[k];
  }

  for (auto x : anss) {
    printf("%d\n", x);
  }
}

int main() {
  // number of nodes, queries
  cin >> n;
  cin >> m;

  tin.resize(n);
  tout.resize(n);
  flat.resize(n);

  sqrtN = ceil(sqrt(n)); // dimension of the bins for mo's alg

  vector<query> queries;  // holds queries
  queries.reserve(m);
  vector<vector<int>> adj(n); // adjacency matrix
  vector<int> colors;
  colors.reserve(n);
  
  int col;
  for (int i = 0; i < n; i++) {
    scanf("%d", &col);
    colors.push_back(col);
  }

  int colors_distinct = *max_element(colors.begin(), colors.end());
  colors_distinct++;    // max number of distinct colors

  // connect edges
  for (int i = 0; i < n - 1; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    adj[l - 1].push_back(r - 1);
    adj[r - 1].push_back(l - 1);
  }

  // remap tree into array via dfs
  dfs(0, -1, adj, colors);

  // read queries
  for (int i = 0; i < m; i++) {
    int v, k;
    scanf("%d%d", &v, &k);

    //  remap query
    v--;  // 0 based index
    query q;
    q.l = tin[v];
    q.r = tout[v];
    q.k = k;
    q.index = i;
    queries.push_back(q);
  }

  solve(n, m, colors, colors_distinct, queries);
}