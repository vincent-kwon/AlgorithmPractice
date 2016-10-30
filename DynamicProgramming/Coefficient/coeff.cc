/*
 * =====================================================================================
 *
 *       Filename:  coeff.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 30일 05시 21분 55초
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

int choose(int n, int r) {

  static long long memo[MAXN][MAXN];

  if (memo[n][r] > 0) return memo[n][r];
 
  if (r == 0 || n == r) return memo[n][r] = 1;

  if (n == 0) return 0;

  return memo[n][r] = choose(n-1, r-1) + choose(n-1, r);
}

int main() {
  int n, r;

  cin >> n;
  cin >> r;

  int result = choose(n, r);

  cout << "result: " << result << endl;
  return 0;
}
