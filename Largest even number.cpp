#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


bool isEven(int number) {
    return number % 2 == 0 || number == 0;
}

long largestEvenNumber(long long input) {

    cout << input << endl;
    int minEven = 11;
    // maybe support function TODO
    vector<int> digits;

    // split into digits, retaining the minimun even 
    while (input != 0) {
        int newDig = input % 10;
        if (isEven(newDig) && newDig <= minEven) {
            // we have to re-insert the digit into the vector
            if (minEven != 11) {
                digits.insert(digits.begin(), minEven);
            }
            minEven = newDig;
        } else {
            digits.insert(digits.begin(), newDig);
        }
        input /= 10;
    }

    // sort in descending order
    sort (digits.begin(), digits.end(), greater<int>());
    
    // at least one even digit
    if (minEven != 11) {
        digits.push_back(minEven);
    } 
    
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
        long long input;
        cin >> input;
        largestEvenNumber(input);
    }
	return 0;
}