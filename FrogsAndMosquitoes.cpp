/*  We map each frog onto a triple <position + length of tongue, position, order of arrival>, we
    insert each frog in a set, erasing a frog if it is completely contained in another one.
    We then process each mosquitoes in order of arrival, checking for the least frog that can reach it,
    so the leftmost. Each time a mosquitoes is eaten we update the values in the answer vector and in
    the frogs set, erasing other frogs if we arrive to contain them. If we can't eat the mosquitoes we insert
    it in a set and check later.
 */ 


#include <iostream>
#include <set>
#include <vector>
#include <tuple>

using namespace std;
typedef pair<long, long> pairs;

const long N = 1000000;

int main() {
  int frog, mosq;
  cin >> frog;
  cin >> mosq;

  // frogs indexed by arrival, values are n of mosq eaten, tongue size
  vector<pairs> ordered_frogs;

  // set keyed by right end of frog / left end, order of arrival
  set<tuple<long, long, int>> frogs;

  // set keyed by position of mosq / mosq size
  multiset<pairs> mosqs;
  for (int i = 0; i < frog; i++) {
    long l, t;
    cin >> l;
    cin >> t;
    ordered_frogs.push_back(make_pair(0, t));
    auto curr_frog = make_tuple(l + t, l, i);
    auto f = frogs.upper_bound(curr_frog);

    // insert frogs if not completely cointained in others in a set
    if (f == frogs.end()) {
      frogs.insert(curr_frog);
    }
    else if (f != frogs.end() && (get<1> (*f) > get<1> (curr_frog))) {
      frogs.insert(curr_frog);
    }
  }

  // foreach mosq find the least b greater than x (if left < x then) -> update set -> find un-eaten mosqs
  while (mosq > 0) {
    long pos, size;
    cin >> pos;
    cin >> size;
    auto curr_mosq = make_pair(pos, size);
    // find the leftmost frog >= than mosq position
    auto f = frogs.upper_bound(make_tuple(pos, -1, -1));

    // if there's a frog that can reach it
    if (f != frogs.end() && get<1>(*f) <= pos) {
      /* cout << "GNAM!" << endl; */
      auto tmp = *f;
      auto new_frog = make_tuple(get<0>(tmp) + size, get<1>(tmp), get<2>(tmp));
      frogs.erase(f);
      frogs.insert(new_frog);
      ordered_frogs[get<2>(tmp)].first++;
      ordered_frogs[get<2>(tmp)].second += size;
      auto iter = frogs.lower_bound(new_frog);

      while (frogs.size() > 1) {
        iter = frogs.lower_bound(new_frog);
        if (iter == frogs.begin()) break;
        iter --;
        auto eliminee = *iter;
        if (get<1>(eliminee) > get<1>(new_frog)) {
          /* cout << "ELIMINATED frog with pos: " << get<1>(eliminee) << endl; */
          frogs.erase(eliminee);
        } else { break; }
      }
      
      // find un-eaten mosqs
      while (mosqs.size() != 0) {
        auto m = mosqs.upper_bound(curr_mosq);
        // if we can eat it
        if (m != mosqs.end() && get<0>(new_frog) >= m->first) {
          /* cout << "GNAM!" << endl; */
          auto tmp = new_frog;
          auto mosq_eaten = *m;
          new_frog = make_tuple(get<0>(tmp) + mosq_eaten.second, get<1>(tmp), get<2>(tmp));
          mosqs.erase(m);
          frogs.erase(tmp);
          frogs.insert(new_frog);
          ordered_frogs[get<2>(tmp)].first++;
          ordered_frogs[get<2>(tmp)].second += mosq_eaten.second;
        } else {
          // erase others frogs if necessary
          auto iter2 = frogs.lower_bound(new_frog);
          while (frogs.size() > 1) {
            iter2 = frogs.lower_bound(new_frog);
            if (iter2 == frogs.begin()) break; 
            iter2 --;
            auto eliminee = *iter2;
            if (get<1>(eliminee) > get<1>(new_frog)) {
              /* cout << "ELIMINATED frog with pos: " << get<1>(eliminee) << endl; */
              frogs.erase(eliminee);
            } else { break; }
          }
          break;
        }
      }
    // else add to un-eaten mosqs
    } else {
      mosqs.insert(curr_mosq);
    }
    mosq --;
  }

  for (auto x : ordered_frogs) {
    cout << x.first << " " << x.second << endl;
  }
}