/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 07시 20분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

// expected

#include <iostream>
#include <map>

using namespace std;

int c[3] = {'a','b','c'};
int n[3] = {0,};

int getCounts(map<char,int> m, int index, string rStr, int count[]) {
  // this ends when m becomes zero
  if (index == 3) {
    for (int i = 0; i < 3; i++) {
      if (count[i] == 0) {
        return 0;
      }
      cout << count[i] << " " ;
    }
    cout << rStr << endl;
    return 1;
  }
  else {
    int sum = 0; 
    if (m[c[index]] > 0) {
      m[c[index]] -= 1;
      // without
      cout << (char)c[index] << ":" << " map[index] : " << m[c[index]] << ", receivedStr"  << rStr << ", " << count[0] << ":" << count[1] <<":" << count[2] << endl;
      sum += getCounts(m, index, rStr, count);
      // with      
      rStr += c[index];
      count[index]++;
      sum += getCounts(m, index, rStr, count);
      return sum;
    }
    else if (m[c[index]] == 0) {
      return getCounts(m, index + 1, rStr, count);
    }
    else {
      return -1;
    }
  }
}

void test(int index, int count[]) {
  if (index==2) return;
  cout <<"before: " << index << ", " << count[0] <<endl;
  count[0]++;
  test(index+1, count);
  cout <<"after: " << index << ", " << count[0] <<endl;
};
int main() {
  int c[3] = {'a','b','c'};
  int n[3] = {0,};
  int count[3] = {0, 0, 0};
  string str = "abc";
  map<char, int> m;

  test(0, count);
#if 0
  for (int i = 0; i < str.size(); i++) {
    if (m.count(str[i]) == 0) {
      m[str[i]] = 1;
    }
    else {
      m[str[i]] += 1;
    }
    cout << m[str[i]] << endl;
  }
  string rStr = "";
  int ret = getCounts(m, 0, rStr, count);
#endif
  return 0;
} 
