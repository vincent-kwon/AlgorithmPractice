/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 22일 16시 08분 19초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */

#include <iostream>

#define SIZE 9
#define BOX_SIZE 3

using namespace std;

int grid[SIZE][SIZE] = {0,};
/*
 * 
 * 012
 * 123
 * 234
 * 345 
 * 456 (4,1) => (3,0)
 * 
 */

void getBoxStart(int i, int j, int& boxR, int& boxC) {
  boxR = i - i%BOX_SIZE;
  boxC = j - j%BOX_SIZE;
}

int main() {
  int boxX;
  int boxY;
  getBoxStart(4,1,boxX,boxY);
  cout << boxX << "," << boxY << endl;
  return 0;
}
