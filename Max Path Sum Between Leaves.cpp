int recursivePathMax(Node* root, int* max) {
    if (root == NULL) return INT_MIN;
    
    // if leaf, return value
    if ((root->left == NULL) && (root->right == NULL)) return root->data;
    
    // else return max between maxPathSum left and right
    int left = recursivePathMax(root->left, max);
    int right = recursivePathMax(root->right, max);
    
    
    // current path max
    int max1 = left >= right ? left + root->data : right + root->data;

    // if it's an internal node, decide connecting leaves or not
    if ((root->left != NULL) && (root->right != NULL)) {
        int maxcurr = root->data + left + right;
        *max =  maxcurr > *max ? maxcurr : *max;
    }

    return max1;
}


int maxPathSum(Node* root) {
    int max = INT_MIN;
    if (root == NULL) return 0;
    
    // else return max between maxPathSum left and right
    recursivePathMax(root, &max);
    return max;
}