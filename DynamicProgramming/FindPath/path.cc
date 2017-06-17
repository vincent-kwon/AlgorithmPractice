/*
 * =====================================================================================
 *
 *       Filename:  path.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016년 11월 20일 21시 27분 38초
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

int sum[100][100];

int getAll(int sRow, int sCol, int eRow, int eCol) {  
  for (int i = 0; i <= eCol; i++) sum[0][i] = 1;
  for (int i = 0; i <= eRow; i++) sum[i][0] = 1;
  for (int i = 1; i <= eRow; i++) {
    for (int j = 1; j <= eCol; j++) {
      sum[i][j] = sum[i-1][j] + sum[i][j-1];
    }
  }
  return sum[eRow][eCol];
}


int main() {
  int row, col;
  cin >> row;
  cin >> col;
  int ret = getAll(0,0,row,col);
  cout << "ret=" << ret << endl;
  return 0;
}
