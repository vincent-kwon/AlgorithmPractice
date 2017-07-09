/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 10일 04시 51분 22초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>

using namespace std;
// 2312
// 1204
//
// 9 thousand, 91 thousand, 900 thousand,
// 1 hundred, 2 hundred
// 2x ~ 9x twenty, thirty, fourty, ........
// 10 ~ 19 : ten, eleven,....nineteen
// 0 nothing
// 1 ~ 9 : one, two, three....
string getSingle(int i) {
  if (i == 1) return "one ";
  else if (i == 2) return "two ";
  else if (i == 3) return "three ";
  else if (i == 4) return "four ";
  else return "xxx " ;
}

string getTwoOrMore(int i) {
  if (i == 2) return "twenty ";
  else if (i == 3) return "thirty ";
  else if (i == 4) return "forty ";
  else return "yyy ";
}

string getTen(int i) {
  if (i == 1) return "eleven ";
  else if (i == 2) return "twelve ";
  else if (i == 3) return "thirteen ";
  else if (i == 4) return "fourteen ";
  else return "zzzz ";
}

int main() {
  int value;
  stringstream ss;
  string s;
  cin >> value;
  ss << value;
  s = ss.str();
  //cout << s << ", " << s.size() << endl;
  char c = s[0];
  int i = (int) c;
  //cout << "char: " << c << ", int: " << i << endl;
  int length = s.size();
  int rIndex = 0;
  string result = "";

  while (rIndex < length) {
    int digitNum = length - rIndex;
    int value = (int)s[rIndex]-48;

    switch(digitNum) {
    case 4:
        result += getSingle(value);
        if (value > 1) {
          result += " thousands ";
        } 
        else if (value == 1) {
          result += " thousand ";
        }
        break;
    case 3:
        if (value > 1) {
          result += getSingle(value);
          result += " hundreds ";
        }
        else if (value == 1) {
          result += getSingle(value);
          result += "hundred";
        }
        break;
    case 2:
        if (value > 1) {
          result += getTwoOrMore(value);
        }
        else if (value == 1) {
          result += getTen((int)s[rIndex+1]-48);
          cout << result << endl;
          return 0;
          //result += getTen(value);
        }
        break;
    case 1:
        if (value > 0) result += getSingle(value);
        break;   
    }
    rIndex++;
  }
  cout << result << endl;
  return 0;
}
