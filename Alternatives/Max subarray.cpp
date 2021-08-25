#include <iostream>
#include <deque>
#include <vector>
#include <utility>   
using namespace std;

void printNLE(int array[], int length) {
    deque<pair <int, int>> support;
    deque<pair <int, int>>::iterator it = support.begin();
    
    vector<int> solutions;
    vector<int>::iterator it1 = solutions.begin();
    for (int i = 0; i < length; i++) {
        solutions.push_back(-1);
    }
    solutions.reserve(length);
    support.push_front(make_pair(array[0], 0));
    for (int i = 1; i < length; i++) {
        it = support.begin();
        while (it != support.end()) {
            if (array[i] > (*it).first) {
                int index = support.front().second;
                //cout << index << " ";
                solutions.at(index) = array[i];
                support.pop_front();
                //cout << array[i] << " ";
                it++;
            } else break;
        }
        support.push_front(make_pair(array[i], i));
    }
    
    for (vector<int>::iterator it = solutions.begin() ; it != solutions.end(); ++it)
        cout << *it << ' ';
    cout << endl;
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
        printNLE(arr, length);
    }
	return 0;
}