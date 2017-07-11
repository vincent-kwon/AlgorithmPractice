/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  AGGTAB, GXTXAYB = GTAB of 4
 *
 *        Version:  1.0
 *        Created:  2017년 07월 11일 17시 35분 58초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *           Note:  How to retrieve
 *                  0 row, 0 col, but str[r-1] <=== -1 
 *     A C
 *   0 0 0  
 * A 0 1 1 (if same , if different max) 
 * B 0 1 1
 * C 0 1 2 
 *
 * =====================================================================================
 */

#include <iostream>

#define ROW 6 
#define COL 7

int array[ROW+1][COL+1] = {0, };

using namespace std;

string str1 = "AGGTAB";
string str2 = "GXTXAYB";

int tryMax(int r, int c) {
  int val1 = array[r-1][c-1];
  int val2 = array[r][c-1];
  int val3 = array[r-1][c];

  if (val1 >= val2 && val1 >= val3) return val1;
  if (val2 >= val1 && val2 >= val3) return val2;
  if (val3 >= val1 && val3 >= val2) return val3;
}

int main() {
  for (int r = 1 ; r <= ROW; r++ ) {
    for (int c = 1; c <= COL; c++) {
      if (str1[r-1] == str2[c-1]) {
        array[r][c] = tryMax(r,c) + 1;
      }
      else {
        array[r][c] = tryMax(r,c);
      }
    }
  }
  cout << "Max:" << array[ROW][COL] << endl;
  int r = ROW, c = COL;
  while (r >= 0 && c >= 0) {
    int t = tryMax(r,c);
    if (array[r][c] > t) {
      cout << r << ", " << c << ":" << str1[r-1] << endl;
      r--; c--;
    }
    else {
      if (array[r-1][c-1] == t) {
        r--; c--;
      }
      else if (array[r][c-1] == t) {
        c--;
      }
      else if (array[r-1][c] == t) {
        r--;
      }
    }
  }

  return 0;
}
