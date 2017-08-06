/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 09일 18시 53분 46초
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

#define TOTAL_BOXES 4 
#define MAX_INT 987654321
#define MIN_INT -987654321

int array[][3] {
  {4,6,7},
  {1,2,3},
  {4,5,6},
  {10,12,32},
};

int gMaxHeight = 0;


int getStackHeight(int ith, int a, int b, int boxBit) {
  cout << "enter: " << a << "," << b << " boxbit: " << boxBit << endl;
  // put ith stack
  if (ith >= TOTAL_BOXES) return 0;
  int ret = 0;
  
  for (int i = 0; i < TOTAL_BOXES; i++) {
    int mask = 1 << i;
    int newLimit;
    int thisHeight; 
    int thisX;
    int thisY;

    if ((boxBit & mask) == 0) {
      for (int h = 0; h < 3; h++) {
        thisHeight = array[i][h];
        if (h == 0) {
          thisX = array[i][1]; 
          thisY = array[i][2];
        }
        else if (h == 1) {
          thisX = array[i][0];
          thisY = array[i][2];
        }
        else {
          thisX = array[i][0];
          thisY = array[i][1];
        } 
        if ((thisX <= a && thisY <= b) || (thisX <= a && thisY <= b)) {
           ret = max(ret, thisHeight + getStackHeight(ith+1, thisX, thisY, boxBit | mask));
        }
        else {
           cout << "can't " << thisX << "," << thisY << ", box: " << (boxBit | mask) << endl;
        }
      }
    }
  }
  return ret;
}


int getStackHeight2(int a, int b) {
  int ret = 0;
  
  for (int i = 0; i < TOTAL_BOXES; i++) {
    int newLimit;
    int thisHeight; 
    int thisX;
    int thisY;

    for (int h = 0; h < 3; h++) {
      thisHeight = array[i][h];
      if (h == 0) {
        thisX = array[i][1]; 
        thisY = array[i][2];
      }
      else if (h == 1) {
        thisX = array[i][0];
        thisY = array[i][2];
      }
      else {
        thisX = array[i][0];
        thisY = array[i][1];
      } 
      if ((thisX < a && thisY < b) || /*(thisX <=a && thisY < b) ||*/
          (thisX < b && thisY < a)) { /*|| (thisX <= b && thisY < a)) {*/
         ret = max(ret, thisHeight + getStackHeight2(thisX, thisY));
      }
      else {
         //cout << "can't " << thisX << "," << thisY << ", box: " << (boxBit | mask) << endl;
      }
    }
  }
  return ret;
}



int main() {
  int ret = getStackHeight2(MAX_INT, MAX_INT);
  cout << "max height: " << ret << endl;
  return 0;
}
