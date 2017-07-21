/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 15일 23시 27분 58초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hobum (Vincent) Kwon (mn), hobum.kwon@gmail.com
 *        Company:  Samsung Electornics
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory.h>

using namespace std;

float findWater (int i, int j, float X) {
  if (j > i) {
    cout << "Incorrect input" << endl;
    return 0;
  }

  float glass[i*(i*1)/2];

  memset(glass, 0, sizeof(glass));

  int index = 0;
  glass[index] = X;

  for (int row = 1; row <= i && X != 0.0; ++row) {
    for (int col = 1; col <= row; ++col, ++index) {
      X = glass[index]; 
      //cout << "1. index: " << index << ", glass[index]" << X << endl;
      glass[index] = (X >= 1.0f) ? 1.0 : X;
      //cout << "2. X after 1.0 checking: glass[index]" << glass[index] << endl;
      X = (X >= 1.0f) ? (X - 1) : 0.0f;
      //cout << "3. after reminder get " << X  << endl;
      glass[index+row] += X/2;
      //cout << "4.1 glass[index+row] ( " << index << "+" << row << ") = " << glass[index+row]  << endl;
      glass[index+row+1] += X/2;
      //cout << "4.2 glass[index+row+1] ( " << index << "+" << row << "+1) = " << glass[index+row+1]  << endl;
    }
  }

  return glass[i*(i-1)/2+j-1];
}

int main() {
  int i = 3, j = 1;
  float X = 3.5;
 
  cout <<"Amount of water in jth, in irow: " << findWater(i,j,X) << endl;

  cout <<"Amount of water in jth, in irow: " << findWater(i,j+1,X) << endl;

  cout <<"Amount of water in jth, in irow: " << findWater(i,j+2,X) << endl;
  
  return 0;
}

