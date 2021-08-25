/*   

 */

class Solution{
public:
  int equalPartition(int N, int arr[])
  {
    // calculate sum and divide by 2 if possible
    int sum = 0;
    for (int i = 0; i < N; i ++) {
      sum += arr[i];
    }
    if (sum % 2 != 0) return 0;
    sum = sum / 2;
    
    int** matrix = new int*[N + 1];

    for (int i = 0; i < N + 1; i++) {
      matrix[i] = new int[sum + 1];
    }      
    
    // initialization
    for (int j = 0; j < sum + 1; j ++) {
      matrix[0][j] = 0;
    }
    
    
    // general step
    for (int i = 1; i < N + 1; i ++) {
      for (int j = 1; j < sum + 1; j++) {
        if (arr[i - 1] > j) {
          matrix[i][j] = matrix[i - 1][j];
        } 
        else if (arr[i - 1] == j) matrix[i][j] = 1;
        else {
          matrix[i][j] =  
            matrix[i - 1][j - arr[i - 1]] > matrix[i - 1][j] ?
            matrix[i - 1][j - arr[i - 1]] : matrix[i - 1][j] ;
        }
      }
    }
    return matrix[N][sum];
  }
};