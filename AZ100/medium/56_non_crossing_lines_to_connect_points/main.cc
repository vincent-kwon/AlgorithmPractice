/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 24일 07시 17분 27초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 * revisit
 * =====================================================================================
 */

#include <iostream>

using namespace std;

unsigned long int catalanDP(unsigned int n) {
  unsigned long int catalan[n+1];
  catalan[0] = catalan[1] = 1;

  for (int i = 2; i <= n; i++) {
    catalan[i] = 0;
    for (int j = 0; j < i; j++) {
      catalan[i] += catalan[j] * catalan[i-j-1];
      cout << "i=" << i << ", j=" << j << ", catalan=" << catalan[i] << endl;
    }
  }
  return catalan[n];
}

unsigned long int countWays(unsigned long int n) {
  if (n & 1) {
    cout << "Invalid:" << endl;
    return 0;
  }
  return catalanDP(n/2);
}

int main() {
  cout << countWays(10) << " " ;
  return 0;
}
