/*  Given an array of N integers arr[] where each element represents the max number 
    of steps that can be made forward from that element. Find the minimum number of 
    jumps to reach the end of the array (starting from the first element). If an 
    element is 0, then you cannot move through that element.

    We solve it using dynamic programming, adding 1 for the number of jumps used 
    and finding the solution in the bottom right corner of the matrix
 */

int minJumps(int arr[], int n){
  // Your code here
  int N = n + 1;
  int** matrix = new int*[N];

  for(int i = 0; i < N; i++) {
    matrix[i] = new int[N];
  }     

  // initialization step
  for (int i = 0;  i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = -1;
    }
  }
  matrix[1][1] = 0;
  int max = (1 + arr[0]) < n ? (1 + arr[0]) : n;
  for (int i = 2; i <= max; i++) {
    matrix[1][i] = 1;
  }
  
  int prev_max = max;
  // general step
  for (int i = 2; i < N; i++) {
    int current_max = (i + arr[i - 1]) < n ?  (i + arr[i - 1]) : n;
    int max = current_max > prev_max ? current_max : prev_max;
      
    for (int j = i; j <= max; j++) {
      //cout << matrix[i - 1][j] << endl;
      //cout << matrix[i][j - 1] << endl;
      if (matrix[i - 1][j] != -1) {
        matrix[i][j] = matrix[i - 1][j];
      } else if (matrix[i][j - 1] == -1) {
        return -1;
      } else {
        matrix[i][j] = matrix[i][i] + 1;
      }
    }
    prev_max = max;
  }
  return matrix[n][n];
}