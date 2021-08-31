/*  We need to find the maximum path sum between two leaves.

    We calculate it recursively, returning the value if it's a leaf, 
    finding the maximum subtree and deciding, if it's an internal node,
    if connecting the leaves of the subtrees or just communicate the max subtree.
*/

#include <climits>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
  int data;
  struct Node* left;
  struct Node* right;
  
  Node(int x){
    data = x;
    left = right = NULL;
  }
};

class Solution {
public:
  int maxPathSum(Node* root) {
    int max = INT_MIN;
    if (root == NULL) return 0;
  
    // else return max between maxPathSum left and right
    recursivePathMax(root, &max);
    return max;
  }
  
  int recursivePathMax(Node* root, int* max) {
    if (root == NULL) return INT_MIN;
    
    // if leaf, return value
    if ((root->left == NULL) && (root->right == NULL)) return root->data;
    
    // else return max between maxPathSum left and right
    int left = recursivePathMax(root->left, max);
    int right = recursivePathMax(root->right, max);
    
    // current path max
    int max1 = left >= right ? (left + root->data) : (right + root->data);
  
    // if it's an internal node, decide connecting leaves or not
    if ((root->left != NULL) && (root->right != NULL)) {
      int maxcurr = root->data + left + right;
      *max = maxcurr > *max ? maxcurr : *max;
    }
  
    return max1;
  }
};