#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
using namespace std;

void printDamage(set<pair<long, int>, greater<pair<long, int>>> spells, int light_n) {

  if (spells.size() == 0) { cout << 0 << endl; return; }
  
  int light_chosen_n = 0; // n of light spells we have chosen to double
  long long damage = 0;

  if (light_n != 0) {

    std::vector<long> chosen_spells;

    // we need to double the light_n highest powers
    for (int i = 0; i < light_n; i++) {
      auto item = spells.begin();
      spells.erase(item);
      chosen_spells.push_back(get<0> (*item));
      if (get<1> (*item) == 1) light_chosen_n++;
      /* cout << "DEBUG: spell to double: " << get<0> (*item) << endl; */
    }

    // if they are all light -> choose the next highest fire instead, if possible
    if (light_chosen_n == light_n) {
      if (spells.size() >= 1) {
        // remove lowest light, add highest fire
        pair<long, int> temp = make_pair(chosen_spells[chosen_spells.size() - 1], 1);
        auto item = spells.begin();
        spells.erase(item);
        chosen_spells[chosen_spells.size() - 1] = get<0> (*item);
        spells.insert(temp);
        /* cout << "DEBUG: adding highest fire spell" << endl; */
      }
      else {
        // all light spells, remove lowest
        pair<long, int> temp = make_pair(chosen_spells[chosen_spells.size() - 1], 1);
        chosen_spells[chosen_spells.size() - 1] = 0;
        spells.insert(temp);
        /* cout << "DEBUG: all light spells" << endl; */
      }
    }
    for (auto x : chosen_spells) {
      damage = damage + 2 * x;
      /* cout << "DEBUG: " << x << endl; */
      /* cout << "DEBUG: chosen_spells dim: " << chosen_spells.size() << endl; */
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
    int light_n = 0;
    cin >> n_changes;
    set<pair<long, int>, greater<pair<long, int>>> spells;
    for (int i = 0; i < n_changes; i ++) {
      int type;
      long power;
      cin >> type;
      cin >> power;
      // forget a spell
      if (power < 0) {
        power = abs (power);
        if (type == 1) light_n--;
        spells.erase(make_pair(power, type));
      // learn a spell
      }
      else {
        pair<long, int> new_spell = make_pair(power, type);
        spells.insert(new_spell);
        if (type == 1) light_n++;
      }
      printDamage(spells, light_n);
    }
	return 0;
}