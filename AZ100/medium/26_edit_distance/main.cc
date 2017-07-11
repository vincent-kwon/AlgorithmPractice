/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 11일 08시 30분 50초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *    why first column, first row need to take care of special treat
 *   
 *    Remember !!!!!!!!!!!! why first column, row should be specially treated. Important !!!!
 *
 *    0  a  a  c 
 * 0  0  1  2  3  
 * a  1  0  1  2  
 * a  2  1  0
 * a  3  2  1
 * a  4  3  2
 * * =====================================================================================
 */

#include <iostream>

using namespace std;

string str1 = "aaaa";
string str2 = "aaa";

int array[5][4] = {0,};

int tripleMin(int r, int c) {
  //if (r == 0 && c == 0) return 0;
  //if (r == 0) return array[r][c-1];
  //if (c == 0) return array[r-1][c];

  int v1 = array[r-1][c-1];
  int v2 = array[r-1][c];
  int v3 = array[r][c-1];

  if (v1 <= v2 && v1 <= v3) return v1;
  if (v2 <= v1 && v2 <= v3) return v2;
  if (v3 <= v1 && v3 <= v2) return v3;
}

int main() {
  int row = str1.size();
  int col = str2.size();
  int r,c;
  
  // first row
  // first column
  // second row, column
  for (r = 0; r <= row; r++) array[r][0] = r;
  for (c = 0; c <= col; c++) array[0][c] = c;

  for (r = 1; r <= row; r++) {
    for (c = 1; c <= col; c++) {
      int val = tripleMin(r,c);
      if (str1[r-1] != str2[c-1]) {
        array[r][c] = val + 1;
      }
      else {
        array[r][c] = array[r-1][c-1];
      }
    }
  }
  cout << array[row][col] << endl; 
  return 0;
}
