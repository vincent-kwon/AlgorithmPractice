/*
 * =====================================================================================
 *
 *       Filename:  late.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 10월 30일 05시 47분 54초
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

#define MAXN 6  
#define MAXC 3
#define MAXA 2
#define ENABLE_MEMOIZATION

int all = 0;
int made = 0;

float memo[MAXN+1][MAXN][MAXN][2]; 

// consecutive 
float lateCheck(const int n, const int consLate, const int absent, const int spoiled) {
  if (n == (MAXN+1)) {
#ifndef ENABLE_MEMOIZATION
    all++;
#endif
    if (spoiled) return 1;
    else return 0;
  }

#ifdef ENABLE_MEMOIZATION
  if (memo[n][consLate][absent][spoiled] != -1) {
    return memo[n][consLate][absent][spoiled];
  }
#endif

  // case for normal
  float nolate = (float)1/3 * (float)lateCheck(n+1, 0, absent, spoiled);

  // case for late
  int newLate = consLate+1;
  int newSpoiled = spoiled;
  if (newSpoiled == 0 && newLate >= MAXC) newSpoiled = 1;
  float late = (float)1/3 * (float)lateCheck(n+1, newLate, absent, newSpoiled); 
  
  // case for absent
  int newAbsent = absent + 1;
  newSpoiled = spoiled;
  if (spoiled == false && newAbsent >= MAXA) newSpoiled = 1;
  float ab = (float)1/3 * (float)lateCheck(n+1, 0, newAbsent, newSpoiled);

#ifdef LOG 
  cout << "(" << n << "," << consLate << "," << absent << "," << spoiled << ") = " << nolate+late+ab << endl;  
#endif 

  return memo[n][consLate][absent][spoiled] = nolate + late + ab;
}

int main() {
  for (int i = 0; i <= MAXN; i++)
    for (int j = 0; j < MAXN; j++)
      for (int w = 0; w < MAXN; w++)
        for (int k = 0; k < 2; k++) {
          memo[i][j][w][k] = -1;
        }

  float p = lateCheck(1, 0, 0, 0);
  cout << p <<" of total "<<all<< endl;
  return 0;
}
