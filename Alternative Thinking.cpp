/*  We need to find the longest alternating sequence, not contingous,
    in a binary sequence and prolong it by inverting a subsequence of bits.
    To obtain the result we just count the longest alternating sequence and
    at the same time check if we encounter couples(00 11) or triples(000 111),
    then we return the longest a. s. plus 1 we found at lest a couple or plus
    2 if we found 2 or more couples and/or a triple.
*/

#include <iostream>

using namespace std;

void solve(int l, int* arr) {
  int res = 1;
  int current = arr[0];
  int current_l = 1; // current length of the same character
  int couples = 0;
  bool triple = 0;

  for (int i = 1; i < l; i++) {
    // if encounter same char
    if (arr[i] == current) {
      if(++current_l == 2) couples++;
      if(current_l > 2) triple = true;
    }
    else {
      res++;
      current = arr[i];
      current_l = 1;
    }
  }
  if (triple || couples >= 2) res += 2;
  else if (couples > 0) res++;

  cout << res << endl;
}

int main () {
  int length;
  cin >> length;
  char* arr_string = (char*) malloc(sizeof(char) * length);
  int* arr = (int*) malloc(sizeof(int) * length);
  cin >> arr_string;
  for (int i = 0; i < length; i++) {
    arr[i] = (int) arr_string[i];
  }
  solve(length, arr);
  return 0;
}