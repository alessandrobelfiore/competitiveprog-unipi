/* OLD EXERCISES */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;


bool isEven(int number) {
    return number % 2 == 0 || number == 0;
}

long largestEvenNumber(string input) {

    vector<char> digits(input.begin(), input.end());
    
    // sort in descending order
    sort (digits.begin(), digits.end(), greater<int>());
    
    auto it = digits.rbegin();
    while (it != digits.rend() && !isEven(*it)) {
        ++it;
    }

    // if we ended on rend, number is ok
    // else we swap
    // FIXME
    auto e = digits.end();
    e --;
    
    if (it != digits.rend()) {
        swap (*e, *it);
    }
    
    //FIXME just insert at the tail, do not sort again
    sort (digits.begin(), e, greater<int>());
    
    // desired output
    for (auto x : digits) {
        cout << x;
    }
    cout << endl;
    return 0;
}

int main() {
	int n_tests = 0;
    cin >> n_tests;
    for (int i = 0; i < n_tests; i ++) {
        string s;
        cin >> s;
        largestEvenNumber(s);
    }
	return 0;
}