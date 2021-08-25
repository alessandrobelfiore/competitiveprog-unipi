#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;


void solve(long* arr, long k, long n) {

  // initialize a set of k positions
  set<pair<long, long>> numbers; // values are - number and index of its last occurence
  set<pair<long, long>> last_indexes; // values are - index of the last occ, number
  long index = -1;
  long start = 0;
  long current = 0;
  long max = 0;
  pair<long, long> ans;

  while (++index < n) {
    long value = arr[index];
    /* cout << "debug: read value: " << value << endl; */ 
    auto item = std::find_if(numbers.begin(), numbers.end(),
      [&value](std::pair<long, long> const & ref) {
        return ref.first == value;
        }
    );
    // number is present, upd last occ
    if (item != numbers.end()) {
      /* cout << "debug: value already present" << endl; */ 
      current++;
      auto reverse = make_pair(item->second, item->first);
      last_indexes.erase(reverse);
      last_indexes.insert(make_pair(index, value));

      numbers.erase(item);
      numbers.insert(make_pair(value, index));
    } 
    // not present
    else {
      if (numbers.size() < k) {
        /* cout << "debug: value not present" << endl; */ 
        current++;
        numbers.insert(make_pair(value, index));
        last_indexes.insert(make_pair(index, value));
      }
      // too many numbers
      else {
        /* cout << "debug: current " << current << endl; */
        if (current > max) {
          /* cout << "debug: too many numbers" << endl; */ 
          max = current;
          ans = make_pair(start, index - 1);
        }

        // eliminate the number with the least last occ
        auto criminal_scum = *(last_indexes.begin());
        /* cout << "criminal " << criminal_scum.first << " with value " << criminal_scum.second << endl; */
        auto reverse_criminal = make_pair(criminal_scum.second, criminal_scum.first);
        numbers.erase(reverse_criminal);
        last_indexes.erase(criminal_scum);
        // numbers.erase(make_pair(culprit, lastOccurence));
        numbers.insert(make_pair(value, index));
        last_indexes.insert(make_pair(index, value));
        start = (criminal_scum.first) + 1;
        // start = lastOccurence + 1;
        current = index - (start - 1);
        
        /* cout << "debug: start " << start << endl;  */
      }
    }
  }

  if (current > max) {
    ans.first = start;
    ans.second = index - 1;
  }
  cout << ans.first + 1 << " " << ans.second + 1 << endl; 
  //printf("%ld %ld", ans.first + 1, ans.second + 1);
}

int main() {
    long n, k = 0;
    cin >> n;
    cin >> k;
    long* arr = (long*) malloc(sizeof(long) * n);
    for (long i = 0; i < n; i ++) {
      long x = 0;
      scanf("%ld", &x);
      arr[i] = x;
    }
    // return longest k-good segment
    solve(arr, k, n);
	return 0;
}