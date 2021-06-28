#include <iostream>
#include <deque>
#include <vector>
#include <utility>   
using namespace std;

void printNLE(long array[], long length) {
    deque<pair <long, long>> support;
    deque<pair <long, long>>::iterator it = support.begin();
    
    vector<long> solutions;
    vector<long>::iterator it1 = solutions.begin();
    for (long i = 0; i < length; i++) {
        solutions.push_back(-1);
    }
    solutions.reserve(length);
    support.push_front(make_pair(array[0], 0));
    for (long i = 1; i < length; i++) {
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
    //it = support.begin();
    //while (it != support.end() && !support.empty()) {
        //int index = support.front().second;
        //cout << index << " ";
        //solutions.insert(solutions.begin() + index, -1);
        //support.pop_front();
        //cout << "-1";
    //    it++;
    //}
    
    for (vector<long>::iterator it = solutions.begin() ; it != solutions.end(); ++it)
        cout << *it << ' ';
    cout << endl;
}

int main() {
    int n_tests = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        long length = 0;
        cin >> length;
        // FIXME
        long* arr = (long*) malloc(sizeof(long) * length);
        for (int j = 0; j < length; j ++) {
            long x = 0;
            cin >> x;
            arr[j] = x;
        }
        printNLE(arr, length);
    }
	return 0;
}