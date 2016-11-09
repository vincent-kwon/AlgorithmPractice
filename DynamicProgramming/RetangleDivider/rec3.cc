/*
 * =====================================================================================
 *
 *       Filename:  rec_divider.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 06일 04시 25분 55초
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

int gRow, gCol;

#define VC_MIN -98764321
#define MAX_SIZE 100

int m[MAX_SIZE][MAX_SIZE];
int s[MAX_SIZE][MAX_SIZE] = { 0, };
int memo[MAX_SIZE][MAX_SIZE][MAX_SIZE+1][MAX_SIZE+1] = {0,};

int getSum(int r1, int c1, int r2, int c2) {
  int rec_ss = 0;
  int rec_row = 0;
  int rec_col = 0;
  int rec_big = 0;

  int &r = memo[r1][c1][r2][c2];
 
  if (r != 0)  {
    return r;
  }

  if (r1 > 0 && c1 > 0) {
    rec_ss = s[r1-1][c1-1];
    rec_row = s[r1-1][c2-1];
    rec_col = s[r2-1][c1-1];
  } 
  else if (r1 > 0 && c1 == 0) {
    rec_row = s[r1-1][c2-1];
  }  
  else if (c1 > 0 && r1 == 0) {
    rec_col = s[r2-1][c1-1];
  }

  rec_big = s[r2-1][c2-1];

  r = rec_big - rec_row - rec_col + rec_ss;
  return r;
}

int getMin2(int r1, int c1, int r2, int c2) {
  int ret = VC_MIN;
  // row only division
  for (int i = r1+1; i < r2; i++) {
    int rec1 = getSum(r1,c1,i,c2);//;
    int rec2 = getSum(i,c1,r2,c2); //;
    int total = rec1 * rec2;
    ret = max(ret, total);
  }

  // col only division
  for (int i = c1+1; i < c2; i++) {
    int rec1 = getSum(r1,c1,r2,i);//;
    int rec2 = getSum(r1,i,r2,c2); //;
    int total = rec1 * rec2;
    ret = max(ret, total);
  }
  return ret;
}


int main() {
  cin >> gRow;
  cin >> gCol;

  for (int i = 0; i < gRow; i++) {
    int row_sum = 0;
    for (int j = 0; j < gCol; j++) {
      cin >> m[i][j]; 
      row_sum += m[i][j];
      s[i][j] = row_sum; 
      if (i > 0) s[i][j] += s[i-1][j];    
    }
  }

  int ret = VC_MIN;

  for (int i = 1; i <= gRow-1; i++) {
    for (int j = 1; j <= gCol-1; j++) {
      int rec1 = getSum(0,0,i,j);//;
      int rec2 = getSum(0,j,i,gCol); //;
      int rec3 = getSum(i,0,gRow,gCol);//;
      int total = rec1 * rec2 * rec3;
 
      ret = max(ret, total);
      rec1 = getSum(0,0,i,j);//;
      rec2 = getSum(i,0,gRow,j); //;
      rec3 = getSum(0,j,gRow,gCol);//;
      total = rec1 * rec2 * rec3;
      ret = max(ret, total);
    }
  }

  for (int i = 1; i <= gRow-1; i++) {
    int rec1 = getSum(0,0,i,gCol);
    int rec23 = getMin2(i,0,gRow,gCol);
    int total = rec1 * rec23;
    ret = max(ret, total);
  }  
  
  for (int i = 1; i <= gCol-1; i++) {
    int rec1 = getSum(0,0,gRow,i);
    int rec23 = getMin2(0,i,gRow,gCol);
    int total = rec1 * rec23;
    ret = max(ret, total);
  }  
  cout << "ret=" << ret << endl;
  return 0;
}
