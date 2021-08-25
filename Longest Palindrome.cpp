/*   We need to find the longest palindrome. We simply use dynamic programming
    with the string and the reserve of itself.
 */

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    else if (b >= a && b >= c) return b;
    else return c;
}

int longestPalinSubseq(string S) {
    // Code here
    
    string reverse;
    for(int n = S.length() - 1; n >= 0; n--){
        reverse.push_back(S[n]);
    }

    int size = S.length() + 1;
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    
    // initialization
    for (int i = 0; i < size; i++) {
        matrix[i][0] = 0;
    }
    for (int j = 0; j < size; j++) {
        matrix[0][j] = 0;
    }
    
    
    // general step
    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            int match = 0;
            if (S[i - 1] == reverse[j - 1]) {
              match = 1;
            }
            matrix[i][j] = 
                max(matrix[i - 1][j - 1] + match, 
                    matrix[i - 1][j],
                    matrix[i][j - 1]);
        }
    }
    return matrix[size - 1][size - 1]; 
}