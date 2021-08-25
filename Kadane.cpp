/*  We need to find the contiguous sub-array(containing at least one number) which has 
    the maximum sum and return its sum. We simply sum each number and update the
    max found, or restart the sum if we get below zero.
 */

#include <iostream>
using namespace std;

void printKadane2(int arr[], size_t length) {
    int sum = 0;
    int m = arr[0];
    for (size_t i = 0; i < length; ++i) {
        if (sum > 0)
            sum = sum + arr[i];
        else 
            sum = arr[i];
        m = max(sum, m);
    }
    cout << m << endl;
}

int main() {
	int n_tests = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        int length = 0;
        cin >> length;
        int* arr = (int*) malloc(sizeof(int) * length);
        for (int j = 0; j < length; j ++) {
            int x = 0;
            cin >> x;
            arr[j] = x;
        }
        printKadane2(arr, length);
    }
	return 0;
}