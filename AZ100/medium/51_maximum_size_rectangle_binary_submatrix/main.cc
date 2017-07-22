/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 21일 20시 37분 28초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>
#include <stack>

using namespace std;

#define ROW 4 
#define COL 4

int A[ROW][COL] = {
  {0, 1, 1, 0},
  {1, 1, 1, 1},
  {1, 1, 1, 1},
  {1, 1, 0, 0},
};

int V[ROW][COL];

int getRowMax(int R[][COL], int row) {
  stack<int> s;
  s.push(0);
  int gMax = -987654321;
  int j;

  for (j = 1; j < COL; j++) {
    int topIndex = s.top();
    int topValue = R[row][topIndex];
    int nowValue = R[row][j]; 

    while (!s.empty() &&topValue > nowValue) {
      s.pop();
      int size = topValue * (j-topIndex);
      if (size > gMax) gMax = size;
      if (!s.empty()) {
        //cout << s.size() << endl;
        topIndex = s.top();
        topValue = R[row][topIndex];
      }
    }
    s.push(j); 
  }
  
  while (!s.empty()) {
    int topIndex = s.top();
    s.pop(); 
    int topValue = R[row][topIndex];
    int size; 
    if (s.size() == 0) {
      size = j * topValue;
    }
    else {
      size = (j - topIndex) * topValue;
    }
    if (size > gMax) gMax = size;
  }
  return gMax;
}

int maxRectangle(int a[][COL]) {
  int gMax = -987654321;

  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (i == 0) V[i][j] = a[i][j];
      else {
        if (a[i][j] == 1) {
          V[i][j] = V[i-1][j] + 1;
        }
        else {
          V[i][j] = 0;
        }
      }
      //cout << V[i][j] << " ";
    }
    //cout << "" << endl;
  }

  for (int i = 0; i < ROW; i++) {
    int tmp = getRowMax(V, i);
    if (tmp > gMax) gMax = tmp; 
  }
  return gMax;
}

int main() {
  cout << maxRectangle(A) << endl;
  return 0;
}

