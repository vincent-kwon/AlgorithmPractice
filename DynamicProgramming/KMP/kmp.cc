/*
 * =====================================================================================
 *
 *       Filename:  kmp.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 10일 01시 10분 50초
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

#define TARGET 6

string target = "abcaby";

string source = "abxabcabcaby";

int p[TARGET+1];

int getMatchIndex(string target, int mChar) {
  int jump = 0;
  for (int suffixSize = 1; suffixSize < mChar; suffixSize++) {
    string s1 = target.substr(0,suffixSize);
    string s2 = target.substr(mChar-suffixSize, suffixSize);
    if (s1 == s2) jump = suffixSize;
  }
  return jump;
}

int getKMP(string source, string target) {
  int i = 0; 
  int last = source.size() - target.size();
  int ret = -1;
  int startIndex = 0;
  while ((i - 2) <= last) {
    int matched = 0;
    for (int t = startIndex; t < target.size(); t++) {
      if (source[i+matched] == target[t]) {
        matched++;
        if (t == (target.size()-1)) return (i-startIndex);
      } else break;
    }
    if (matched > 0) {
      i = i + matched;
      startIndex = p[matched];
      //cout << source[i] << ",next : " << i << ", startIndex " << startIndex << ", matched " << matched << endl;
    } else {
      i = i + 1;
    }
  }
    
  return ret;
}

int main() {
  for (int i = 0; i < TARGET; i++) {
    p[i] = getMatchIndex(target, i);
  }
  int ret = getKMP(source,target);
  cout << "r: " << ret << endl;
  return 0;
}
