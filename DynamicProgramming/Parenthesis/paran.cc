/*
 * =====================================================================================
 *
 *       Filename:  paran.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 09일 10시 29분 39초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
    
   () () () 
   () (())
   (())()
   ((()))

 *
 * =====================================================================================
 */

#include <iostream>
#define INVALID -1
using namespace std;

int map[100];

int getParentCount(int num) {
  int& count = map[num];

  if (count != INVALID) return count;

  count = 0;

  if (num == 0) return count = 1;
  
  if (num == 1) return count = 1;

  // () ()()
  // () (())
  // (())()
  // (()())
  // ((()))

  for (int left = 0; left < num; left++) {
    cout << num << ":" << left << "," << num - 1 - left << endl;
    count += getParentCount(left) * getParentCount(num - 1 - left);
  }
  return count;
}

int main() {
  int i;
  cin >> i;
  for (int j = 0; j <= i ; j++) map[j] = INVALID;
  int r = getParentCount(i);
  cout << "r: " << r << endl;
  return 0;
}
