#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef pair<int, int> pairs;

int main() {
  int frog, mosq;
  cin >> frog;
  cin >> mosq;

  vector<pairs> ordered_frogs;

  // set keyed by right end of frog / left end
  set<pairs> frogs;
  // set keyed by position of mosq / mosq size
  multiset<pairs> mosqs;
  for (int i = 0; i < frog; i++) {
    // store frogs in pairs, end / start
    int l, r;
    cin >> l;
    cin >> r;
    ordered_frogs.push_back(make_pair(l, 0));
    auto curr_frog = make_pair(l + r, l);
    auto f = frogs.upper_bound(curr_frog);
    // insert frogs not completely cointained in others in a set
    if (f != frogs.end() && f->second > curr_frog.second) {
      frogs.insert(curr_frog);
    }
  }

  // foreach mosq find the least b greater than x (if left < x then) -> update set -> find un-eaten mosqs
  while (mosq > 0) {
    int pos, size;
    cin >> pos;
    cin >> size;
    auto curr_mosq = make_pair(pos, size);
    // find the least b greater than mosq position
    auto f = frogs.upper_bound(curr_mosq);
    // if left < mosq position then -> update set
    if (f != frogs.end() && f->second <= curr_mosq.second) {
      auto tmp = *f;
      auto new_frog = make_pair(tmp.first + curr_mosq.second, tmp.second);
      frogs.erase(*f);
      frogs.insert(new_frog);
      // erase others frogs if necessary
      
      // find un-eaten mosqs
      while (mosqs.size() != 0) {
        auto m = mosqs.upper_bound(curr_mosq);
        // if we can eat it
        if (m != mosqs.end() && new_frog.first >= m->first && new_frog.second <= m->first) {
          auto tmp = new_frog;
          new_frog = make_pair(tmp.first + m->second, tmp.second);
          mosqs.erase(*m);
          frogs.erase(tmp);
          frogs.insert(new_frog);
          // erase others frogs if necessary
        } else {
          break;
        }
      }
    // else add to un-eaten mosqs
    } else {
      mosqs.insert(curr_mosq);
    }
    mosq --;
  }
}