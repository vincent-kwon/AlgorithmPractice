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

int getSum(int r1, int c1, int r2, int c2) {
  cout << "getSuM: " << r1 << c1 << r2 << c2 << endl;
  int rec_ss = 0;
  int rec_row = 0;
  int rec_col = 0;
  int rec_big = 0;

  if (r1 > 0 && c1 > 0) {
    rec_ss = s[r1-1][c1-1];
  } 
  else if (r1 > 0) {
    rec_row = s[r1-1][c2-1];
  }  
  else if (c1 > 0) {
    rec_col = s[r2-1][c1-1];
  }

  rec_big = s[r2-1][c2-1];

  cout << rec_ss <<","<<rec_row<<","<<rec_col<<","<< rec_big << endl;
  int r =  rec_big - rec_row - rec_col + rec_ss;
  cout <<"getsumR: " << r << endl;
  return r;
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
  // row only division
  for (int i = 1; i <= gRow-2; i++) {
    for (int j = i+1; j <= gRow-1; j++) {
      int rec1 = getSum(0,0,i,gCol);//;
      int rec2 = getSum(i,0,j,gCol); //;
      int rec3 = getSum(j,0,gRow,gCol);//;
      int total = rec1 * rec2 * rec3;
      cout << "total:" << total << "," << rec1 << "," << rec2 << "," << rec3 << endl;
      ret = max(ret, total);
    }
  }
  cout << "row only " << ret << endl;

  // col only division
  for (int i = 1; i <= gCol-2; i++) {
    for (int j = i+1; j <= gCol-1; j++) {
      int rec1 = getSum(0,0,gRow,i);//;
      int rec2 = getSum(0,i,gRow,j); //;
      int rec3 = getSum(0,j,gRow,gCol);//;
      int total = rec1 * rec2 * rec3;
      cout << "total:" << total << "," << rec1 << "," << rec2 << "," << rec3 << endl;
      ret = max(ret, total);
    }
  }

  // row-col division
  for (int i = 1; i <= gRow-1; i++) {
    for (int j = 1; j <= gCol-1; j++) {
      // extend horizontal
      int rec1 = getSum(0,0,i,j);//;
      int rec2 = getSum(0,j,i,gCol); //;
      int rec3 = getSum(i,0,gRow,gCol);//;
      int total = rec1 * rec2 * rec3;
      cout << "T:" << total << "," << rec1 << "," << rec2 << "," << rec3 << endl;
 
      ret = max(ret, total);
      // extend vertical
      rec1 = getSum(0,0,i,j);//;
      rec2 = getSum(i,0,gRow,j); //;
      rec3 = getSum(0,j,gRow,gCol);//;
      total = rec1 * rec2 * rec3;
      cout << "T:" << total << "," << rec1 << "," << rec2 << "," << rec3 << endl;
      ret = max(ret, total);
    }
  }
  
  cout << "ret=" << ret << endl;
  return 0;
}
