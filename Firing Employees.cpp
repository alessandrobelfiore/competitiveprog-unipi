#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int firingEmployees (long array[], long length) {
    // creating positions matrix
    vector<vector<int>> positions;
    for (int i = 0; i < length; i++) {
        positions[array[i]].push_back(i + 1);
    }

    // utility stack
    stack<int> s;
    s.push(positions[0].front());  // Mr Alfred 's rank
    
    vector<int> seniors (length + 1, 0);

    // computing seniors vector
    for (int i = 0; i < length; i++) {

    }


    
}


int main() {
	int n_tests = 0;
    cin >> n_tests;
    // FIXME
    for (int i = 0; i < n_tests; i ++) {
        string s;
        cin >> s;
        //firingEmployees(s);
    }
	return 0;
}