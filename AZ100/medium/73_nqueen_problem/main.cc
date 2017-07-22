/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 21일 23시 06분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h> // memo: exit

#define SIZE 4

using namespace std;

int m[SIZE][SIZE] = {0, };

void printArray(int cp[][SIZE]) {
  for (int i = 0 ;  i < SIZE; i++) {
    for (int j = 0 ; j < SIZE; j++) {
      cout << cp[i][j] << " ";
    }
    cout << "" << endl;
  }
  cout << "" << endl;
}

bool check(const int row, const int col, int cp[][SIZE]) {
  for (int r = 0; r < SIZE; r++) {
     if (cp[r][col] != 0) return false;
  }

  int d = 1;
  int reached = 4;
  while (reached > 0) {
    if (row+d < SIZE && col+d < SIZE) {
      if (cp[row+d][col+d] != 0) return false;
    }
    else {
      reached--;
    }
    if (row-d >= 0 && col-d >= 0) {
      if (cp[row-d][col-d] != 0) return false;
    }
    else {
      reached--;
    }
    if (row+d < SIZE && col-d >= 0) {
      if (cp[row+d][col-d] != 0) return false;
    }
    else {
      reached--;
    }
    if (row-d >=0 && col+d < SIZE) {
      if (cp[row-d][col+d] != 0) return false;
    }
    else {
      reached--;
    }
    d++;
  }
  return true;
}

void drawLines(int cp[][SIZE], const int row, int col) {
  if (row == SIZE) {
    printArray(cp);
    exit(0);
    return;
  }
  else {
    if (check(row, col, cp)) {
      cp[row][col] = 1;
      for (int j = 0; j < SIZE; j++) {
        drawLines(cp, row+1, j);
      }
      cp[row][col] = 0;
    }
    else return;
  }
}

int main() {
  for (int j = 0; j < SIZE; j++) {
      drawLines(m, 0, j);
  }
  return 0;
}
