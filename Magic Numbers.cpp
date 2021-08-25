/*  We need to distinguish if the number we receive is a magic number given that
    a magic number is a number formed by concatenation of numbers 1, 14 and 144.
    We simply read the digits left to right, remembering if we encountered 1 or 2 
    occurences of 4.
 */

#include <iostream>
#include <string>
using namespace std;

int isMagic(string num) {
  int length = num.length();
  int situation = 0;
  if (num[0] != '1') return -1;
  // situation maps:
  //  0 -> last number seen is 1
  //  1 -> first occurence of 4
  //  2 -> second occurence of 4
  for (int i = 1; i < length; i++) {
    switch (situation)
    {
    case 0:
      if (num[i] == '1') situation = 0;
      else if (num[i] == '4') situation = 1;
      else return -1; 
      break;
    case 1:
      if (num[i] == '1') situation = 0;
      else if (num[i] == '4') situation = 2;
      else return -1;
      break;
    case 2:
      if (num[i] == '1') situation = 0;
      else return -1;
      break;
    default:
      return -1;
      break;
    }
  }
  return 1;
}

int main () {
  string number;
  cin >> number;
  string result = isMagic(number) == 1 ? "YES" : "NO";
  cout << result;
  return 0;
}