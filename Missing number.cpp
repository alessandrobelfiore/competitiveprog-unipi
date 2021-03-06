/*  We need to find the missing number in a array of all 1-N elements minus one.
    We simply calculate the sum of all the numbers in the array and find the difference
    between it and the expected sum of all N elements.
 */

#include <iostream>
#include <vector>
using namespace std;

// use this to test on G4G site
class Solution{
  public:
    int MissingNumber(vector<int>& array, int n) {
        long long sum = 0;
        long long expected_sum = (n * (n + 1)) / 2;
        for (int i = 0; i < n - 1; i++) {
            sum = sum + array[i];
        }
        return (expected_sum - sum);
    }
};

// local test code
void printMissing(int arr[], int length) {
    int sum = 0;
    int expected_sum = (length * (length + 1)) / 2;
    for (int i = 0; i < length - 1; i++) {
        sum = sum + arr[i];
    }
    cout << (expected_sum - sum) << endl;
}

int main() {
	int n_tests = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        int length = 0;
        cin >> length;
        int* arr = (int*) malloc(sizeof(int) * length);
        for (int j = 0; j < length - 1; j ++) {
            int x = 0;
            cin >> x;
            arr[j] = x;
        }
        printMissing(arr, length);
    }
	return 0;
}