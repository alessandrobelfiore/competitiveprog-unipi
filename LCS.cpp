/*  Longest common subsequence, solved using dynamic programming
 */

class Solution{
    public:
        int lcs(int x, int y, string s1, string s2){
        
        // your code here
            int X = x + 1;
            int Y = y + 1;
            
            int** matrix = new int*[X];
            
            for(int i = 0; i < X; i++) {
                matrix[i] = new int[Y];
            }
            
            // initialization step
            for (int i = 0;  i < X; i++) {
                matrix[i][0] = 0;
            }
            for (int i = 0;  i < Y; i++) {
                matrix[0][i] = 0;
            }
            
            // general step
            for (int i = 1; i < X; i++) {
                for (int j = 1; j < Y; j++) {
                    if (s1[i - 1] == s2[j - 1]) {
                        matrix[i][j] = matrix[i - 1][j - 1] + 1;
                    }
                    else {
                        matrix[i][j] = 
                            matrix[i - 1][j] > matrix[i][j - 1] ? matrix[i - 1][j] : matrix[i][j - 1];
                    }
                }
            }
            
            int result = matrix[x][y]; 
            return result;
    }
};
