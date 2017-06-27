/*
 * =====================================================================================
 *
 *       Filename:  longestPalindromNative.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 27일 04시 54분 30초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

string str = "BBABCBCAB";

int longPalindrom(int startIndex, int endIndex) {
  if (startIndex == endIndex) return 1;
  if (startIndex > endIndex) return 0;
  if (str[startIndex] == str[endIndex]) {
    return 2 + longPalindrom(startIndex+1, endIndex-1);
  }
  else {
    return max(longPalindrom(startIndex+1, endIndex), longPalindrom(startIndex, endIndex-1));
  }
}


string longPalindromStr(int startIndex, int endIndex) {
  string cs1(1,str[startIndex]);
  string cs2(1,str[endIndex]); 
  if (startIndex == endIndex) return cs1;
  if (startIndex > endIndex) return "";
  if (str[startIndex] == str[endIndex]) {
    return cs1 + longPalindromStr(startIndex+1, endIndex-1) + cs2;
  }
  else {
    string s1 = longPalindromStr(startIndex+1, endIndex);
    string s2 = longPalindromStr(startIndex, endIndex-1);
    if (s1.size() > s2.size()) return s1; 
    else return s2;
  }
}

int main() {
  cout << longPalindrom(0, str.size()-1) << endl;
  cout << longPalindromStr(0, str.size()-1) << endl;
  return 0;
}
