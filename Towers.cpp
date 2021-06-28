#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int towers(int arr[], int start, int end) {

    std::vector<int> bars;
    
    for (int i = 0; i <= end; i ++) {
        bars.push_back(arr[i]);
    }
    std::sort (bars.begin(), bars.end());

    int count = 0, max = 0, current = -1, occurences = 0;

    for (auto x : bars) {
        if (x != current) {
            count ++;
            current = x;
            occurences = 1;
        } else {
            occurences ++;
        }
        max = std::max(max, occurences);
    }

    cout << max << " " << count;
    return 0;
}


int main() {
    int length = 0;
    cin >> length;
    int* arr = (int*) malloc(sizeof(int) * length);
    for (int j = 0; j < length; j ++) {
        int x = 0;
        cin >> x;
        arr[j] = x;
    }
    towers(arr, 0, length - 1);
	return 0;
}