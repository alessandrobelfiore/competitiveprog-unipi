#include <iostream>
using namespace std;

int printWater(int arr[], int start, int end) {
    int sum = 0;
    int sx = arr[start];
    int dx = arr[end];
    int reverse = 0;
    
    if (start > end) {
        reverse = 1;
    }
    if (sx > dx) {
        return printWater(arr, end, start);
        // need to reverse
    } else if (reverse == 0) {
        for (int i = start; i < end; i ++) {
            if (arr[i] <= sx) {
                sum += sx - arr[i];
            } else {
                return sum + printWater(arr, i, end);
            }
        }
    } else if (reverse == 1) {
        for (int i = start; i > end; i --) {
            if (arr[i] <= sx) {
                sum += sx - arr[i];
            } else {
                return sum + printWater(arr, i, end);
            }
        }
    }
    return sum;
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
        cout << printWater(arr, 0, length - 1) << endl;
    }
	return 0;
}