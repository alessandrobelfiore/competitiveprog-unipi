#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
typedef tuple<int, int, int> triple;

struct node  { 
  int data; 
  vector<node*> childs;
}; node;

struct node* newNode(int data) { 
  // declare and allocate new node  
  struct node* node = new struct node(); 
   
  node->data = data;    // Assign data to this node
   
  return(node); 
}


void solve(int n, vector<node*> nodes, int m, vector<triple> queries) {
  vector<int> ans (m, 0);

  
}

int main() {
  // number of nodes, queries
  int n,m;
  cin >> n;
  cin >> m;

  vector<node*> nodes;
  vector<triple> queries;
  int data;

  for (int i = 0; i < n; i++) {
    cin >> data;
    nodes.push_back(newNode(data));
  }

  // connect edges
  for (int i = 0; i < n - 1; i++) {
    int l, r;
    cin >> l;
    cin >> r;
    nodes[l - 1]->childs.push_back(nodes[r - 1]);
  }

  // read queries
  for (int i = 0; i < m; i++) {
    int v, k;
    cin >> v;
    cin >> k;
    queries.push_back(make_tuple(v - 1, k, i));
  }

  solve(n, nodes, m, queries);
}