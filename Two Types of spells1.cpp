#include <iostream>
#include <algorithm>
#include <utility>
#include <deque>
using namespace std;

void printDamage(deque<pair<long, int>> spells, int fire_n) {

  if (spells.size() == 0) {cout << 0 << endl; return;}

  long long damage = 0;
  int was_l = 0;
  int fire_used = 0;
  // use sorted data struct
  std::sort(spells.begin(), spells.end());
  std::reverse(spells.begin(), spells.end());

  // use first weakest spell
  auto item = spells.back();

  // check if last fire spell, skip if possible
  if (get<1> (item) == 0 && fire_used == (fire_n - 1) && spells.size() > 1) {
    item = spells[spells.size() - 2];
    spells.erase(spells.end() - 2);
  }

  else {
    spells.pop_back();
  }
  damage += get<0> (item);

  long long count = spells.size();

  if (get<1> (item) == 1) {
    was_l = 1;
  }
  else {
    fire_used++;
  }
  // for any spell left, use the highest if was_l, lowest o.w.
  for (long long i = 0; i < count; i++) {
    if (was_l) {
      item = spells.front();
      if (get<1> (item) == 0 && fire_used == (fire_n - 1) && spells.size() > 1) {
        item = spells[1];
        spells.erase(spells.begin() + 1);
      }
      else {
        spells.pop_front();
      }
      damage = damage + (2 * get<0> (item));
    } else {
      item = spells.back();
      if (get<1> (item) == 0 && fire_used == (fire_n - 1) && spells.size() > 1) {
        item = spells[spells.size() - 2];
        spells.erase(spells.end() - 2);
      }
      else {
        spells.pop_back();
      }
      damage = damage + get<0> (item);
    }
    if (get<1> (item) == 1) was_l = 1;
    else {
      was_l = 0;
      fire_used++;
    }
  }

  cout << damage << endl;
  return;
}

int main() {
    int n_changes = 0;
    int fire_n = 0;
    cin >> n_changes;
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
        auto p = std::find_if (spells.begin(), spells.end(), 
          [&power, type](const std::pair<long, int> element) { 
            return get<0>(element) == power && get<1>(element) == type;
            } );
        if (p == spells.end()) cout << "TRUE";
        spells.erase(p);
      // learn a spell
      }
      else {
        pair<long, int> new_spell = make_pair(power, type);
        spells.push_back(new_spell);
        if (type == 0) fire_n++;
      }
      printDamage(spells, fire_n);
    }
	return 0;
}