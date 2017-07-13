/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 13일 15시 42분 58초
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

#define COL 5
#define ROW 4 

int M[][COL] = {
  { 0, 0, 1, 1, 0 },
  { 1, 0, 1, 1, 0 },
  { 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1 },
};

int visited[][COL] = { 0, };
int gSize = -987654321;
int DFS(int row, int col, int size) {
  visited[row][col] = 1;
  int tmpSize = size + 1; // this size

  if (col + 1 < COL && M[row][col+1] == 1 && visited[row][col+1] == 0) {
    tmpSize = DFS(row, col+1, tmpSize);
  }

  if (row + 1 < ROW && M[row+1][col] == 1 && visited[row+1][col] == 0) {
    tmpSize = DFS(row+1, col, tmpSize);
  }
 
  if (row - 1 >= 0 && M[row-1][col] == 1 && visited[row-1][col] == 0) {
    tmpSize = DFS(row-1, col, tmpSize);
  }

  if (col - 1 >= 0 && M[row][col-1] == 1 && visited[row][col-1] == 0) {
    tmpSize = DFS(row, col-1, tmpSize);
  }

  if (col + 1 < COL && 
      row + 1 < ROW &&
      M[row+1][col+1] == 1 &&
      visited[row+1][col+1] == 0) {
    tmpSize = DFS(row+1, col+1, tmpSize);
  }

  if (col + 1 < COL  && 
      row - 1 >= 0 &&
      M[row-1][col+1] == 1 &&
      visited[row-1][col+1] == 0) {
    tmpSize = DFS(row-1, col+1, tmpSize);
  }
 
  if (col - 1 >= 0 && 
      row + 1 < ROW &&
      M[row+1][col-1] == 1 &&
      visited[row+1][col-1] == 0) {
    tmpSize = DFS(row+1, col-1, tmpSize);
  }

  if (col - 1 >= 0 && 
      row - 1 >= 0 &&
      M[row-1][col-1] == 1 &&
      visited[row-1][col-1] == 0) {
    tmpSize = DFS(row-1, col-1, tmpSize);
  }
  return tmpSize;
}
int countIsland(int count) {
  for (int i = 0 ; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (visited[i][j] == 0) {
        if (M[i][j] == 1) {
          // visit adjacent
          int size = DFS(i, j, 0); 
          cout << "Island size: " << size << endl;
          if (size > gSize) gSize = size;
          count++;
          cout << "Now count " << count << endl;
        }
      }
    }
  }
  return gSize;
}

int main() {
  int ret = countIsland(0);
  cout << "Biggest size: " << ret << endl;
  return 0;
}
