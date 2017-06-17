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
#include <stdio.h>

#define MAX_COMPANY 20
#define MAX_MONEY 300
#define INITBASE -1

int price[MAX_COMPANY+1][MAX_MONEY+1] = {
  {0, 0, 0,  0,   0},
  {0, 1, 10, 11, 19},
  {0, 2, 12, 19, 20},
  {0, 3,  4,  5,  7},
};

int dp[MAX_COMPANY+1][MAX_MONEY+1] = {0,};

using namespace std;

int totalPrice, totalCompany;

int getMaxProfit(const int m, const int c, const int companyIndex) {
  
  if (companyIndex == c) return price[companyIndex][m];

  if (m == 0) return 0;

  int &ret = dp[companyIndex][m];

  if (ret != INITBASE) return ret;
  
  for (int i = 0; i <= m; i++) {
    int profit = price[companyIndex][i] + getMaxProfit(m - i, c, companyIndex + 1);
    ret = max(ret, profit);
  }
  return ret;
}

int getMaxReturnBottomUp(const int max_money, const int max_company) {
  int m[MAX_COMPANY+1][MAX_MONEY+1] = {0, };

  for (int c = 1; c <= max_company; c++) {
    for (int money = 1; money <= max_money; money++) {
      int r = -1;
      for (int toCurrent = 0; toCurrent <= money; toCurrent++) {
        int gain = price[c][toCurrent];
        r = max(r, m[c-1][money-toCurrent] + gain);
      } 
      m[c][money] = r;
    }
  }
  return m[max_company][max_money];
}

int main() {
  freopen("01-1_input.txt", "r", stdin);

  int test;
  cin >> test;

  while (test-- > 0) {
    cin >> totalPrice;
    cin >> totalCompany;

    for (int c = 0; c <= MAX_COMPANY; c++) {
      for (int i = 0; i <= MAX_MONEY; i++) {
        dp[c][i] = INITBASE;
      }
    }

    for (int i = 1; i <= totalPrice; i++) {
      int tmpPrice;
      cin >> tmpPrice;
      for (int c = 1; c <= totalCompany; c++) {
        cin >> price[c][i];
      }
    }

    int r = getMaxProfit(totalPrice, totalCompany, 1);   
    int r2 = getMaxReturnBottomUp(totalPrice, totalCompany);
    cout << "r:" << r << ", r2:" << r2 << endl;
  }
  return 0;
  
}
