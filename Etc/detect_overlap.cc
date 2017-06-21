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

int main() {
  int one[4][2] = {
    0,0,
    10,0,
    0,10,
    10,10
   };

  int two[4][2] = {
    10,0,
    15,0,
    10,15,
    15,15,
  };

  bool result = true;
  bool x_overlap = false;
  bool y_overlap = false;

  //if (one[0][0] < two [0][0]) 

  // 1. identical (easy)
  if (one[0][0] == two[0][0] &&
      one[0][1] == two[0][1] &&
      one[1][0] == two[1][0] &&
      one[1][1] == two[1][1]) {
      return true;
  } 
 
  int **left;
  int **right;
  int **top;
  int **bottom;

  bool width_lap = false;
  bool height_lap = false;

  // test width overlap
  if (one[0][0] <= two[0][0]) {
    if (one[1][0] > two[0][0]) width_lap = true;
    else width_lap = false;   
  }
  else {
    if (two[1][0] > one[0][0]) width_lap = true;
    else width_lap = false;   
  }
  if (one[0][1] <= two[0][1]) {
    if (one[2][1] > two[2][1]) height_lap = true;
    else height_lap = false;   
  }
  else {
    if (two[2][1] < one[2][1]) height_lap = true;
    else height_lap = false;   
  }

  if (width_lap == true && height_lap == true)  result = true;
  else result = false;

  cout << "Overlap: " << result << endl;
  return 0;
}
