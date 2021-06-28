#include <iostream>
#include <algorithm>
#include <utility>
#include <deque>
#include <vector>
using namespace std;

void printDamage(deque<pair<long, int>> spells, int fire_n, int light_n) {

  if (spells.size() == 0) { cout << 0 << endl; return; }
  
  int light_chosen_n = 0;
  long long damage = 0;

  if (light_n != 0) {

    // sort
    std::sort(spells.begin(), spells.end());
    std::reverse(spells.begin(), spells.end());

    std::vector<long> chosen_spells(light_n);

    // we need to double the light_n highest power
    for (int i=0; i < light_n; i++) {
      auto item = spells.front();
      spells.pop_front();
      chosen_spells.push_back(get<0> (item));
      if (get<1> (item) == 1) light_chosen_n++;
    }
    // if they are all light -> choose the next highest fire instead, if possible

    if (light_chosen_n == light_n) {
      if (spells.size() >= 1) {
        // remove lowest light, add highest fire
        pair<long, int> temp = make_pair(chosen_spells[chosen_spells.size() - 1], 1);
        auto item = spells.front();
        spells.pop_front();
        chosen_spells[chosen_spells.size() - 1] = get<0> (item);
        spells.push_front(temp);
      }
      else {
        // all light spells, remove lowest
        pair<long, int> temp = make_pair(chosen_spells[chosen_spells.size() - 1], 1);
        chosen_spells[chosen_spells.size() - 1] = 0;
        spells.push_front(temp);
      }
    }
    for (auto x : chosen_spells) {
      damage = damage + 2 * x;
    }
  }

  for (auto x : spells) {
    damage =  damage + get<0> (x);
  }

  cout << damage << endl;
  return;
}

int main() {
    int n_changes = 0;
    int fire_n = 0;
    int light_n = 0;
    cin >> n_changes;
    // FIXME change in set
    deque<pair<long, int>> spells;
    for (int i = 0; i < n_changes; i ++) {
      long power;
      int type;
      cin >> type;
      cin >> power;
      // forget a spell
      if (power < 0) {
        power = abs (power);
        if (type == 0) fire_n--;
        else light_n--;
        auto p = std::find_if (spells.begin(), spells.end(), 
          [&power, type](const std::pair<long, int> element){ return get<0>(element) == power && get<1>(element) == type;} );
        spells.erase(p);
      // learn a spell
      }
      else {
        pair<long, int> new_spell = make_pair(power, type);
        spells.push_back(new_spell);
        if (type == 0) fire_n++;
        else light_n++;
      }
      printDamage(spells, fire_n, light_n);
    }
	return 0;
}