#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <climits>
#include <cstring>
#include <tuple>

using namespace std;
typedef pair<long, long> pairs;

const long N = 90000000;
//const long N = 1000000000;

const long MAX = LONG_MAX;

int main() {
  int frog, mosq;
  cin >> frog;
  cin >> mosq;

  // frogs indexed by position, values are n of mosq eaten, tongue size
  vector<pairs> ordered_frogs(1000, make_pair(0, 0));

  // set of correspondances - order of arrival, frog position
  set<pairs> corr;

  /* int* frogs = (int*) malloc(sizeof(int) * N);
  memset(frogs, MAX, sizeof(frogs)); */
  vector<long> frogs(N, MAX);

  // set keyed by position of mosq / mosq size
  multiset<pairs> mosqs;
  for (int i = 0; i < frog; i++) {
    long l, t; // left position, tongue length
    cin >> l;
    cin >> t;
    ordered_frogs[l].second = t;
    corr.insert(make_pair(i, l));
    for (long k = l; k <= l + t; k++) {
      if (frogs[k] > l) frogs[k] = l;
      /* cout << "frogs " << k << " " << frogs[k] << endl; */
    }
    /* cout << "inserting frog at: " << l << endl; */
  }

  // foreach mosq
  while (mosq > 0) {
    long pos, size;
    cin >> pos;
    cin >> size;
    auto curr_mosq = make_pair(pos, size);
    /* cout << "frogs[pos]: " << frogs[pos] << endl; */

    // if no frog can reach it, add it to set
    if (frogs[pos] == MAX) {
      mosqs.insert(curr_mosq);
      /* cout << "can't eat mosq at pos: " << pos << endl; */
    }

    // some frog can eat it
    else {
      ordered_frogs[frogs[pos]].first++;
      ordered_frogs[frogs[pos]].second += size;
      long index = pos;
      /* cout << "eating mosq at pos: " << pos << endl; */
      while (size > 0) {
        index ++;
        if (frogs[index] != frogs[pos]) {
          size--;
          frogs[index] = frogs[pos];
        }
      }
      // check if we can eat un-eaten frogs
      while (mosqs.size() > 0) {
        /* cout << "check for uneaten mosqs" << endl; */
        auto next_mosq = mosqs.upper_bound(curr_mosq);
        /* cout << "what" << endl;
        cout << " found uneaten mosq at pos: " << next_mosq->first << endl;
        cout << "frogs[next_mosq->first] " << frogs[next_mosq->first] << endl;
        cout << "next_mosq->first " << next_mosq->first << endl; */
        if (next_mosq != mosqs.end() && frogs[next_mosq->first] != MAX) {
          pos = next_mosq->first;
          /* cout << " found uneaten mosq at pos: " << pos << endl; */
          size = next_mosq->second;
          index = pos;
          ordered_frogs[frogs[pos]].first++;
          ordered_frogs[frogs[pos]].second += size;
          while (size > 0) {
            index ++;
            if (frogs[index] != frogs[pos]) {
              size--;
              frogs[index] = frogs[pos];
            }
          }
          mosqs.erase(next_mosq);
        }
        else {break;}
      }
    }
    mosq --;
  }

  for (auto x : corr) {
    auto l = x.second;
    cout << ordered_frogs[l].first << " " << ordered_frogs[l].second << endl;
  }
}