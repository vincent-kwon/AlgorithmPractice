/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 21일 06시 43분 17초
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

int win[8][3] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},
  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8},
  {0, 4, 8}, 
  {2, 4, 6}
};

bool isCWin(char *board, char c) {
  for (int i = 0; i < 8 ; i++) 
    if (board[win[i][1]] == c &&
        board[win[i][2]] == c &&
        board[win[i][0]] == c) return true;
  return false;
}
// memo: understand exact winning case (order and numbers)
bool isValid(char board[9]) {
  int oCount = 0;
  int xCount = 0;
  int otherCount = 0;
  // # of X, O diff should be equal and less than 1
  for (int i = 0 ; i < 9; i++) {
    if (board[i] == 'O') oCount++; 
    else if (board[i] == 'X')  xCount++;
    else otherCount++;
  }
  if (otherCount != 0) return false;
  // only X, O
  if (abs(xCount-oCount) > 1) return false;

  // check whether both wins (not both allowed)
  if (isCWin(board, 'O') && isCWin(board, 'X')) return false;
  else return true;
}

int main() {
  char board[] = {
    'X', 'X', 'O',
    'O', 'O', 'X',
    'X', 'O', 'X'
  };

  isValid(board)? cout << "Yes" << endl : cout << "Not valid";
  return 0;
}
