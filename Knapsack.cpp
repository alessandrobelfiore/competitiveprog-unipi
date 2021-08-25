/* Classical knapsack problem, we solve it using dynamic programming 
 */

#include <iostream>

using namespace std;

class Solution{
public:
  int knapsack(int N, int S, int sizes[], int values[])
  {

    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
      matrix[i] = new int[S + 1];
    }      
    
    // initialization
    for (int i = 0; i < N; i++) {
      matrix[i][0] = 0;
    }

    int first_size = sizes[0];
    int first_value =  values[0];
    for (int j = 1; j < S + 1; j++) {
      matrix[0][j] = 
        first_size <= j ? first_value : 0;
    }
    
    // general step
    for (int i = 1; i < N; i ++) {
      for (int j = 1; j < S + 1; j++) {
        if (sizes[i] > j) {
          matrix[i][j] = matrix[i - 1][j];
        } else {
          matrix[i][j] = 
            matrix[i - 1][j] > matrix[i - 1][j - sizes[i]] + values[i] ?
            matrix[i - 1][j] : matrix[i - 1][j - sizes[i]] + values[i];
        }
      }
    }
    return matrix[N - 1][S];
  }
};

int main() {
  int S, N;
  cin >> S;
  cin >> N;
  int* sizes = new int[N];
  int* values = new int[N];

  for (int i = 0; i < N; i ++) {
    cin >> sizes[i];
    cin >> values[i];
  }

  Solution obj;
  cout << obj.knapsack(N, S, sizes, values);
  return 0;
}