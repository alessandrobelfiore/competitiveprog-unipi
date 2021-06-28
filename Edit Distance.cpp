class Solution {
  public:
    int min(int a, int b, int c) {
        if (a <= b && a <= c) return a;
        else if (b <= a && b <= c) return b;
        else return c;
    }
  
    int editDistance(string s, string t) {
        // Code here
        
        int S = s.size() + 1;
        int T = t.size() + 1;
        int** matrix = new int*[S];
        for (int i = 0; i < S; i++) {
            matrix[i] = new int[T];
        }
        
        // initialization
        for (int i = 0; i < T; i++) {
            matrix[0][i] = i;
        }
        for (int j = 0; j < S; j++) {
            matrix[j][0] = j;
        }
        
        
        // general step
        for (int i = 1; i < T; i++) {
            for (int j = 1; j < S; j++) {
                int mismatch = 1;
                if (t[i - 1] == s[j - 1]) {
                    mismatch = 0;
                }
                matrix[j][i] = 
                    min(matrix[j - 1][i - 1] + mismatch, 
                        matrix[j - 1][i] + 1,
                        matrix[j][i - 1] + 1);
            }
        }
        return matrix[S - 1][T - 1]; 
    }
};