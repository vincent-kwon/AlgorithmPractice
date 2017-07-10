/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017년 07월 10일 10시 10분 30초
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

/*
 * 3 4 2 1 7 9 12
 *
 * How to do it?
 *
 * 3
 *
 * 4
 * 1: 3, 2: 4
 *
 * 2
 * 1: 2, 2: 4
 *
 * 1: 1, 2: 4
 *
 * 1: 1, 2: 4, 3: 7
 *                  4: 9
 *                        5: 12
 *
 * 3)   4)   7)  9)            
 *
 *
 */
#define NUM 9

int array[NUM] = {3, 5, 2, 1, 4, 9, 12, 8, 20};
int bound[NUM];
int previous[NUM];

int increasing_subsequence_nlogn() {
  // init  
  for (int i = 0; i < NUM; i++) {
    bound[i] = -1;  
    previous[i] = -1;
  }
  
  int s = 0;
  int b = 0;

  bound[0] = 0; // index, not value

  for (int i = 1; i < NUM; i++) {
    if (array[i] < array[bound[s]]) {
      bound[s] = i;
      previous[s] = -1;
    } 
    else if (array[i] > array[bound[b]]) {
      int indexPrevious = bound[b];
      b++;
      bound[b] = i;
      previous[i] = indexPrevious; 
    }
    else {
      for (int j = s+1; j < b; j++) {
        if (array[i] < array[bound[j]]) {
          bound[j] = i; 
          previous[j] = bound[j-1];
        }
      }
    }  
  }
  cout << "LIS: " << (b+1) << endl;

  
  int index = bound[b];

  while (true) {
    cout << array[index] << endl;    
    index = previous[index];
    if (index == -1) break;
  }
  return 0;
}


int main() {
  increasing_subsequence_nlogn();
  return 0;
}
