#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int remap_index = 0;
int sqrtN;
int n,m;

struct query {
  int l, r;
  int k;
  int index;
};

int dfs(vector<vector<int>>& vertices, int index, int parent, 
        vector<vector<int>>& remap, vector<int>& visited, vector<int>& end) {

  /* cout << "index: " << index + 1 << endl; */
  visited[index] = 1;
  remap[0][remap_index] = index;
  remap[1][index] = remap_index;
  remap_index++;

  // if it's a leaf return its index
  if (vertices[index].size() == 1 && vertices[index][0] == parent) {
    /* cout << "leaf: " << index + 1 << endl; */
    end[index] = index;
    return index;
  }

  // if it's an internal node, recur on children, set end as dfs of the last children
  for (int i = 0; i < vertices[index].size(); i++) {
    if (vertices[index][i] != parent /* && visited[vertices[index][0]] == -1 */) {
      if (i == vertices[index].size() - 1) {
        /* cout << "last child: " << vertices[index][i] + 1 << endl; */
        end[index] = dfs(vertices, vertices[index][i], index, remap, visited, end);
      } else {
        /* cout << "child: " << vertices[index][i] + 1 << endl; */
        dfs(vertices, vertices[index][i], index, remap, visited, end);
      }
    }
  }
  return end[index];
}

bool compare(const query& a, const query& b) {
  if ((a.l / sqrtN) != (b.l / sqrtN))
    return (a.l / sqrtN) < (b.l / sqrtN);
  return a.r < b.r;
}

void add(vector<int>& occs, int color, vector<int>& kOccs) {
  occs[color] ++;
  int count = occs[color];
  /* if (count >= 0) */   // can't happen if we move right end first
  kOccs[count] ++;
  /* if (count >= kOccs.size()) kOccs.push_back(0);
  kOccs[count]++; */
}
void remove(vector<int>& occs, int color, vector<int>& kOccs) {
  int count = occs[color];  // get number of occs
  occs[color] --;           // decrement it
  kOccs[count] --;
  /* if (count >= 0) */   // can't happen if we move right end first
    /* kOccs[count]--; */
  /* if (kOccs.back() == 0) kOccs.pop_back(); */
}

void solve (int n, int m, vector<vector<int>>& remap, vector<int>& colors, int nColors,
            vector<query>& queries) {

  vector<int> anss(m, 0);

  // re-order queries
  sort (queries.begin(), queries.end(), compare);

  int cnt_r = -1;
  int cnt_l = 0;
  int ans = 0;
  int color = 0;
  vector<int> occs (nColors, 0);  // current n of colors occurences, occs[i] = x means x times color i
  vector<int> kOccs(n + 1, 0);    // current n of colors that occur at least i times
  /* kOccs[0] = nColors; */   // all colors occur 0 times
  /* vector<int> kOccs;
  kOccs.reserve(nColors);
  kOccs.push_back(nColors); */

  for (int i = 0; i < m; i++) {
    int n_query = queries[i].index;  // order of arrival of the query
    int k = queries[i].k;

    while (cnt_r < queries[i].r) {
      cnt_r ++;
      color = colors[remap[0][cnt_r]];
      add(occs, color, kOccs);
    }
    while (cnt_l < queries[i].l) {
      color = colors[remap[0][cnt_l]];
      remove(occs, color, kOccs);
      cnt_l ++;
    }
    while (cnt_l > queries[i].l) {
      cnt_l --;
      color = colors[remap[0][cnt_l]];
      add(occs, color, kOccs);
    }
    while (cnt_r > queries[i].r) {
      color = colors[remap[0][cnt_r]];
      remove(occs, color, kOccs);
      cnt_r --;
    }
    ans = k < kOccs.size() ? kOccs[k] : 0;
    anss[n_query] = ans;
  }

  for (auto x : anss) {
    printf("%d\n", x);
  }
}

int main() {
  // number of nodes, queries
  cin >> n;
  cin >> m;

  sqrtN = ceil(sqrt(n)); // dimension of the bins for mo's alg

  vector<query> queries;  // holds queries
  queries.reserve(m);
  vector<vector<int>> adj(n); // adjacency matrix
  vector<int> colors; // colors, ranked from 0 to n-1
  colors.reserve(n);
/*   vector<int> all_colors; // support array for ranking
  all_colors.reserve(n); */
  vector<int> end(n, 0);  // last node contained on the subtree
  int col;

  for (int i = 0; i < n; i++) {
    scanf("%d", &col);
    /* col--; */
    colors.push_back(col);
/*     all_colors.push_back(col); */
  }
/*   sort (all_colors.begin(), all_colors.end()); */
  int colors_distinct = 0;

  // substitute color values with their ranks FIXME not necessary
/*   for (int i = 0; i < n; i++) {
    colors[i] = lower_bound(all_colors.begin(), all_colors.end(), colors[i]) - all_colors.begin();
  } */
  colors_distinct = *max_element(colors.begin(), colors.end());
  colors_distinct++;    // max number of distinct colors

  // connect edges
  for (int i = 0; i < n - 1; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    
    adj[l - 1].push_back(r - 1);
    adj[r - 1].push_back(l - 1);
  }

  vector<vector<int>> remap;
  remap.push_back(vector<int>(n, -1));  // 1st dim is nodes in order of dfs
  remap.push_back(vector<int>(n, -1));  // 2nd dim is correspondence of original node idx to remapped
  vector<int> visited(n, -1);  // support array for dfs

  // remap tree into array via dfs
  dfs(adj, 0, -1, remap, visited, end);

  // read queries
  for (int i = 0; i < m; i++) {
    int v, k;
    scanf("%d%d", &v, &k);

    //  remap query
    v--;  // 0 based index
    query q;
    q.l = remap[1][v];
    q.r = remap[1][end[v]];
    q.k = k;
    q.index = i;
    queries.push_back(q);
  }

  solve(n, m, remap, colors, colors_distinct, queries);
}