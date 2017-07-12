/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 12일 17시 55분 05초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *        meekkssgbgqsm => b
 *
 *        repeated
 *
 *        inDll
 *
 *        b -> q 
 *
 *        if alphabe[char] is possible
 *
 *        if dll[char] in dll
 *        
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

int repeated[256] = {0, };
int inDll[256] {0, };

using namespace std;
void process(list<int> &l, string s) {
  for (int i = 0; i < s.size(); i++) {
    int target = s[i]-'a';
    if (repeated[target] == true) {
      continue;
    }
    else {
      if (inDll[target] == true) {
        list<int>::iterator itor = find(l.begin(), l.end(), target);
        if (itor != l.end()) l.erase(itor);
        repeated[target] = true;
      }
      else {
        inDll[target] = true;
        l.push_back(target);
      }
    }
  }  
  for (int i : l) cout << ((char)(i+'a')) << endl;
}

int main() {
  string s = "meekkssgbgqsm";
  list<int> l;

  process(l, s);

  return 0; 
}


