/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 12일 08시 14분 36초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 *  Better way to do is using queue
 *
 *  if Petro - disance becomes negative, dequeue it then it changes starting point (Great algorithm)
 * =====================================================================================
 */

#include <iostream>

using namespace std;

typedef struct _Petrol {
  int amount;
  int nextDistance;
} Petrol;

int getCircleStart(Petrol* array, int start) {
  int accum = 0; 
  int ret = -1; 
  for (int i = 0; i < 4; i++) {
    if (start == 4) start = 0;
    
    accum += array[start].amount; 
    if (accum >= array[start].nextDistance) {
      accum -= array[start].nextDistance; 
      start++;
    }
    else {
      return ret;
    }
  }
  return accum;
}

int main() {
  Petrol array[] = {
    {4,6}, {6,5}, {7,3}, {4,5}
  };
 
  for (int i = 0; i < 4; i++) {
    int ret = getCircleStart(array,i);
    if (ret != -1) {
       cout << "circle: " << i << endl;
    }
  }
  return 0;
}
