/*
 * =====================================================================================
 *
 *       Filename:  lcs_simple.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 27일 05시 27분 07초
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


int array[10] = { 0, 3, 4, 5, 1, 2, 7, 6, 9, 8 }; 
int memo[10] = { 0, };

int lcs(int start) {
  int tmp;
  int max = 1;

  if (memo[start] != 0) return memo[start]; 

  for (int i = start + 1 ; i < 10; i++) {
    if (array[start] < array[i]) {
      tmp = 1 + lcs(i);
      if (tmp > max) max = tmp;
    }     
  }

  
  return memo[start] = max;
}

int main() {
  int i;
  i = lcs(0);
  cout << i - 1 << endl;
  return 0;
}
