/*
 * =====================================================================================
 *
 *       Filename:  invest.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 01일 20시 30분 42초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *
 *
 *    0  1  2  3   4 
 * A  0  8 10  12  15           
 * B  0  6 12  18  23       
 * C  0  2  3  25  27       
 * =====================================================================================
 */

#include <iostream>

#define MAX_COMPANY 3
#define MAX_MONEY 4 

int price[MAX_COMPANY+1][MAX_MONEY+1] = {
  {0, 0, 0,  0,   0},
  {0, 1, 10, 11, 19},
  {0, 2, 12, 19, 20},
  {0, 3,  4,  5,  7},
};

using namespace std;

int getMaxReturnTopDown(const int m, const int companyIndex, const int currentTotal) {
  int r = -1;
  if (companyIndex >= MAX_COMPANY || m <= 0) return currentTotal;
  for (int i = 0; i <= m; i++) {
    r = max(r, getMaxReturnTopDown(m-i, companyIndex+1, currentTotal + price[companyIndex][i]));
  }
  return r;
}

int getMaxReturnBottomUp() {
  int m[MAX_COMPANY+1][MAX_MONEY+1] = {0, };

  for (int c = 1; c <= MAX_COMPANY; c++) {
    for (int money = 1; money <= MAX_MONEY; money++) {
      int r = -1;
      for (int toCurrent = 0; toCurrent <= money; toCurrent++) {
        int gain = price[c][toCurrent];
        r = max(r, m[c-1][money-toCurrent] + gain);
      } 
      m[c][money] = r;
    }
  }
  return m[MAX_COMPANY][MAX_MONEY];
}

int main() {
  int r = getMaxReturnTopDown(MAX_MONEY, 1, 0);   
  int r2 = getMaxReturnBottomUp();
  cout << "r:" << r << ", r2:" << r2 << endl;
  return 0;
}
