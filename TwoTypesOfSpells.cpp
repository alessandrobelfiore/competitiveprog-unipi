/*  We need to find the maximum damage possible, using fire spells and 
    lightning spells. Lightning spells double the power of the the next spell used.
    We then forget or learn a new spell each step.
    We maintain a set for the highest power spells, as many as the number of lightining spells,
    and a set for the others spells. We can't have all lightining spells in the 
    highest power set.
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
using namespace std;

void solve() {

  int n_changes = 0;
  long long light_n = 0;
  long long sum = 0;

  cin >> n_changes;
  set<long long> greatest[2]; // greatest spells 0 = fire, 1 = light
  set<long long> others[2];  
  for (int i = 0; i < n_changes; i ++) {
    int type;
    long long power;
    cin >> type;
    cin >> power;
    // forget a spell and subtract its power
    if (power < 0) {
      power = abs (power);
      if (greatest[type].find(power) != greatest[type].end()) {
        greatest[type].erase(power);
        sum -= 2 * power;
			} else {
				others[type].erase(power);
				sum -= power;
      }
    // learn a spell
    }
    else {
      others[type].insert(power);
      sum += power;
    }

    // consequences of forgetting/learning a light spells
    if (greatest[1].size() > 0) {
      auto item = *greatest[1].begin();
      sum -= item;
      greatest[1].erase(item);
      others[1].insert(item);
    }
    if (greatest[0].size() > 0) {
      auto item = *greatest[0].begin();
      sum -= item;
      greatest[0].erase(item);
      others[0].insert(item);
    }

    long long doubled = greatest[0].size() + greatest[1].size();
    light_n = greatest[1].size() + others[1].size();

    long long diff = light_n - doubled;

    // while we can double more spells, we add them to the greatest set
    while (diff > 0 && (others[0].size() > 0 || others[1].size() > 1)) {
      type = 0;

      // if no fire spells, pick light
      if (others[0].size() == 0) type = 1;
      // if no lights, pick fire
      else if (others[1].size() <= 1) type = 0;
      // else choose greatest
      else {
        auto f = *others[0].rbegin();
        auto l = *others[1].rbegin();
        f > l ? type = 0 : type = 1;
      }
      auto item = *others[type].rbegin();
      others[type].erase(item);
      greatest[type].insert(item);
      sum += item;
      diff--;
    }
    cout << sum << endl;
  }
}

int main() {
  solve();
	return 0;
}