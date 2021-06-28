#include <iostream>
#include <vector>
using namespace std;

void printLeaders(int array[], int length) {
    vector<int> leaders;
    int max = array[length - 1];
    leaders.push_back(max);
    for (int i = length - 2; i >= 0; i --) {
        if (array[i] >= max) {
            max = array[i];
            leaders.push_back(max);
        }
    }
    reverse(leaders.begin(), leaders.end());
    for (const int& i : leaders) {
        std::cout << i << " ";
    }
    std::cout << '\n';
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
        printLeaders(arr, length);
    }
	return 0;
}