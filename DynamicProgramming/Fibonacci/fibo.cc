/*
 * =====================================================================================
 *
 *       Filename:  fibo.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 30일 05시 41분 01초
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

#define MAXN 200

int fibo(int n) {
  static int memo[MAXN];

  if (n == 1 || n == 2) return 1;

  if (memo[n] != 0) return memo[n];

  return memo[n] = fibo(n-2) + fibo(n-1);
}

int main() {
  int f;

  cin >> f;

  int r = fibo(f);

  cout << "r:" << r << endl;
  return 0;
}
