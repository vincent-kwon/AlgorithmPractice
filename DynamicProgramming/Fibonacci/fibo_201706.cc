/*
 * =====================================================================================
 *
 *       Filename:  fibo_201706.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 13일 06시 14분 37초
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

int memo[1000] =  { 0, };

int fibo(int i) {
  if (memo[i] != 0) return memo[i];

  if (i == 1 || i == 2) {
    memo[i] = 1;
    return memo[i];
  }
  
  return (memo[i] = fibo(i-1) + fibo(i-2));
}

int main() {
  int input;
  cin >> input;

  int r = fibo(input);

  cout << r << endl;
  return 0;
}
