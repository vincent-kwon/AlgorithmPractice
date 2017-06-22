/*
 * =====================================================================================
 *
 *       Filename:  detect_overlap.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 06월 19일 07시 11분 11초
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

typedef struct _rect {
  int x1;
  int y1;
  int x2;
  int y2;
} Rect;

int main() {
  Rect rect[2];
  rect[0].x1 = 0;
  rect[0].y1 = 0;
  rect[0].x2 = 10;
  rect[0].y2 = 10;
  
  rect[1].x1 = 9;
  rect[1].y1 = 0;
  rect[1].x2 = 15;
  rect[1].y2 = 15;
  
  // check first's rigth < second's left
  // 1. if first < second, can be, if true, never overlap
  // 2. if second < first, cant' be, always false
  if (rect[0].x2 <= rect[1].x1 || rect[1].x2 <= rect[0].x1) {
    cout << "No" << endl;
    return false;
  }

  if (rect[0].y2 <= rect[1].y1 || rect[1].y2 <= rect[0].y1) {
    cout << "No" << endl;
    return false;
  }
  cout << "Yes " << endl;
  return 0;
}
